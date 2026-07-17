**Gotowe.** Poniżej znajdziesz **pełny, praktyczny przykład**, który pokazuje obie metody jednocześnie:

1. **Klasyczne narzędzia SQL** (`@tool` z zapytaniami Spark/SQL)
2. **Opis słowny** dla Genie (TalkToData) – aby agent mógł używać naturalnego języka

### Zaktualizowany plik `skills/transaction_analyzer.py`

```python
from langchain_core.tools import tool
from pyspark.sql import SparkSession
from typing import Dict, Any

spark = SparkSession.getActiveSession()

# ==================== KLASYCZNE TOOLS (SQL) ====================

@tool
def analyze_transaction_trends(account_id: str, days: int = 90) -> Dict[str, Any]:
    """Szczegółowa analiza trendów wpływów i wypływów."""
    query = f"""
    WITH monthly AS (
        SELECT 
            DATE_TRUNC('month', transaction_date) as month,
            SUM(CASE WHEN amount > 0 THEN amount ELSE 0 END) as inflows,
            SUM(CASE WHEN amount < 0 THEN -amount ELSE 0 END) as outflows,
            COUNT(DISTINCT counterparty_name) as unique_counterparties,
            SUM(CASE WHEN is_cash = true AND amount > 0 THEN amount ELSE 0 END) as cash_in
        FROM silver.transactions
        WHERE account_id = '{account_id}'
          AND transaction_date >= CURRENT_DATE() - INTERVAL {days} DAYS
        GROUP BY month
    )
    SELECT * FROM monthly ORDER BY month DESC
    """
    df = spark.sql(query).toPandas()
    return {
        "data": df.to_dict(orient="records"),
        "summary": f"Analiza dla {account_id} za {days} dni"
    }


@tool
def detect_large_cash_deposits(account_id: str, threshold: float = 50000) -> Dict[str, Any]:
    """Wykrywanie dużych wpłat gotówkowych powyżej progu."""
    query = f"""
    SELECT 
        transaction_date,
        amount,
        counterparty_name,
        description
    FROM silver.transactions
    WHERE account_id = '{account_id}'
      AND is_cash = true 
      AND amount >= {threshold}
    ORDER BY amount DESC
    LIMIT 20
    """
    df = spark.sql(query).toPandas()
    return df.to_dict(orient="records")


# ==================== SKILL DLA GENIE (TALK TO DATA) ====================

@tool
def genie_transaction_analysis(natural_language_query: str, account_id: str = None) -> Dict[str, Any]:
    """
    Pozwala agentowi zadać dowolne pytanie w języku naturalnym do Genie (TalkToData).
    Najlepsze do otwartych pytań analitycznych.
    
    Przykłady dobrych pytań:
    - "Pokaż trendy miesięczne wpływów i wypływów dla konta {account_id}"
    - "Kto jest największym kontrahentem w ostatnim kwartale?"
    - "Czy były wpłaty gotówkowe powyżej 50 tys. zł w tym miesiącu?"
    - "Porównaj strukturę wpływów z poprzednim rokiem"
    """
    from databricks.sdk import WorkspaceClient
    w = WorkspaceClient()
    
    # Opcjonalnie wzbogacamy pytanie o account_id
    if account_id:
        full_query = f"{natural_language_query} dla konta {account_id}"
    else:
        full_query = natural_language_query

    try:
        response = w.genie.execute_query(
            query=full_query,
            catalog="silver",
            schema="transactions"
        )
        
        return {
            "status": "success",
            "answer": response.result if hasattr(response, 'result') else str(response),
            "sql": getattr(response, 'sql', 'nieznane'),
            "rows_returned": len(response.data) if hasattr(response, 'data') else 0
        }
    except Exception as e:
        return {"status": "error", "message": str(e)}
```

### Jak używać obu podejść w Supervisorze

```python
# supervisor.py
from skills.transaction_analyzer import (
    analyze_transaction_trends,
    detect_large_cash_deposits,
    genie_transaction_analysis
)

tools = [
    analyze_transaction_trends,
    detect_large_cash_deposits,
    genie_transaction_analysis,   # <--- skill słowny
    # ... inne skille
]

supervisor_prompt = """Jesteś ekspertem analitycznym w banku.

Masz dostęp do następujących skilli:

1. analyze_transaction_trends – precyzyjna analiza trendów (użyj gdy potrzebujesz strukturyzowanych danych)
2. detect_large_cash_deposits – wykrywanie dużych wpłat gotówkowych
3. genie_transaction_analysis – najpotężniejszy skill. Używaj go do dowolnych pytań w języku naturalnym,
   szczególnie gdy użytkownik pyta o coś skomplikowanego lub nie masz dedykowanego tool'a.

Zawsze wybieraj najbardziej odpowiedni skill. 
Gdy nie jesteś pewien – użyj genie_transaction_analysis."""
```

### Przykład użycia (main.py)

```python
response1 = run_agent("Przeanalizuj trendy dla konta ACC987654 za ostatnie 180 dni")
response2 = run_agent("Pokaż największych kontrahentów i sumy wpłat w ostatnim kwartale dla ACC987654")
response3 = run_agent("Czy były jakieś podejrzane duże wpłaty gotówkowe powyżej 100 tys. zł?")
```

---

**Zalety tego podejścia:**

- Masz **precyzyjne, powtarzalne narzędzia SQL** (dobre do raportów)
- Masz **Genie skill** – agent może zadawać dowolne pytania słowne (duża elastyczność)
- Łatwo dodawać nowe skille (nowy plik → import → dodanie do listy)

Chcesz, żebym przygotował **cały folder** z plikami (`supervisor.py`, `main.py`, `router.py` itp.) w jednym bloku, gotowy do skopiowania? Mogę też dodać wersję z Agent Bricks zamiast czystego LangGraph.
