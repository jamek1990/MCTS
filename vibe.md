Wygląda na to, że narzędzia komputerowe mają teraz problem z uruchomieniem. Podaję całą strategię bezpośrednio — możesz skopiować ją do pliku `.md` w swoim repozytorium:

---

# 🐍 Strategia Wdrożenia AI-Assisted Python Development

> **Cel:** Ustandaryzować pracę zespołu z GitHub Copilot / VibeCode przy tworzeniu rozwiązań w Pythonie — od idei do działającego, testowalnego kodu.

---

## 1. Filozofia i zasady ogólne

### 1.1 AI jako pair programmer, nie automat
- AI **proponuje**, człowiek **weryfikuje i zatwierdza**
- Każdy fragment kodu wygenerowany przez AI musi być zrozumiany przez autora przed commitem
- Nie wklejamy kodu, którego nie umiemy wytłumaczyć code reviewerowi

### 1.2 Vertical Slicing (programowanie pionowe)
Budujemy rozwiązanie w **pionowych warstwach** — każdy slice to kompletna, uruchamialna i testowalna jednostka funkcjonalności, nie pozioma warstwa techniczna.

```
❌ Poziomo:              ✅ Pionowo (slice):
├── models/             ├── slice_1_user_register/
├── services/           │   ├── model.py
├── routes/             │   ├── service.py
└── tests/              │   ├── route.py
                        │   └── test_slice1.py
                        └── slice_2_user_login/
```

**Zasada slicingu:**
1. Jeden slice = jedna historia użytkownika z PRD
2. Slice musi być uruchamialny i testowalny samodzielnie
3. Slice jest domknięty przed przejściem do kolejnego

---

## 2. Workflow — od PRD do kodu

### Etap 0 — PRD

Każde rozwiązanie zaczyna się od pliku `.prd.md`:

```markdown
## Cel
Krótki opis co i po co.

## User Stories
- [ ] US-01: Jako [kto], chcę [co], żeby [po co]

## Wymagania funkcjonalne
- FR-01: ...

## Wymagania niefunkcjonalne
- Wydajność / Bezpieczeństwo: ...

## Out of scope
- Czego NIE robimy w tej iteracji

## Definicja gotowości (DoD)
- [ ] Testy jednostkowe przechodzą
- [ ] Kod przeszedł review
- [ ] Dokumentacja zaktualizowana
```

### Etap 1 — Dekompozycja na Slices (`SLICES.md`)

```markdown
## Slice 1: Rejestracja użytkownika
- Input: dane formularza
- Output: zapisany user, token JWT
- Testy: test_register_success, test_register_duplicate_email
- Status: [ ] TODO / [ ] IN PROGRESS / [x] DONE
```

### Etap 2 — Prompt startowy dla AI

Wklejaj go na początku każdej sesji z Copilotem / VibeCode:

```
[CONTEXT]
Projekt: <nazwa>
Stack: Python 3.12, FastAPI, SQLAlchemy 2.0, Pydantic v2, pytest
Aktualny slice: <US-01 - Rejestracja użytkownika>

[CODING RULES — obowiązują przez całą sesję]
- Używaj type hints wszędzie
- Funkcje max 20 linii, jedna odpowiedzialność (SRP)
- Nazwy funkcji: snake_case, czasownik + rzeczownik (get_user, create_order)
- Nazwy klas: PascalCase, rzeczownik (UserService, OrderRepository)
- Stałe: UPPER_SNAKE_CASE
- Brak magic numbers — używaj named constants lub Enum
- Każda publiczna funkcja ma docstring (Google style)
- Brak globalnego state — dependency injection
- Błędy przez custom exceptions, nie przez return None
- Nie używaj mutable default arguments

[TASK]
Napisz <opis slica>, zgodnie z regułami powyżej.
Zacznij od schemas → logika domenowa → testy → infrastruktura → endpoint.
```

### Etap 3 — Kolejność generowania kodu

```
1. Schematy danych (Pydantic / dataclasses)
2. Interfejsy / protokoły (typing.Protocol)
3. Logika domenowa (czyste funkcje, bez frameworka)
4. Testy jednostkowe logiki domenowej  ← testy muszą być zielone przed kolejnym krokiem
5. Warstwa infrastruktury (DB, HTTP clients)
6. Testy integracyjne
7. Endpoint / entry point
8. Smoke test (manualna weryfikacja)
```

---

## 3. Reguły kodowania (Python Clean Code)

### 3.1 Nazywanie

| Element | Konwencja | Przykład |
|---|---|---|
| Funkcja/metoda | `snake_case`, czasownik | `get_user_by_id()`, `send_email()` |
| Klasa | `PascalCase`, rzeczownik | `UserRepository`, `PaymentService` |
| Zmienna | `snake_case`, opisowa | `user_count`, `is_active` |
| Stała | `UPPER_SNAKE_CASE` | `MAX_RETRIES = 3` |
| Moduł/plik | `snake_case` | `user_service.py` |
| Boolean | prefix `is_`, `has_`, `can_` | `is_valid`, `has_permission` |
| Kolekcja | liczba mnoga | `users`, `order_items` |

### 3.2 Funkcje

```python
# ✅ Dobrze
def calculate_order_total(items: list[OrderItem], discount: Decimal = Decimal("0")) -> Decimal:
    """Oblicza całkowitą wartość zamówienia po rabacie.

    Args:
        items: Lista pozycji zamówienia.
        discount: Rabat jako wartość dziesiętna (0.1 = 10%).

    Returns:
        Całkowita kwota po rabacie.
    """
    subtotal = sum(item.price * item.quantity for item in items)
    return subtotal * (1 - discount)

# ❌ Źle
def calc(x, d=0):
    s = 0
    for i in x:
        s += i.price * i.quantity
    return s - s * d
```

### 3.3 Obsługa błędów

```python
# ✅ Custom exceptions
class UserNotFoundError(Exception):
    def __init__(self, user_id: UUID) -> None:
        super().__init__(f"User {user_id} not found")
        self.user_id = user_id

class DuplicateEmailError(Exception): ...

# W serwisie
async def register(self, data: RegisterUserDTO) -> User:
    if await self._repo.exists_by_email(data.email):
        raise DuplicateEmailError(data.email)
    ...

# ❌ Nie rób tak
async def register(self, data):
    if not user:
        return None  # kto wie co to znaczy?
```

### 3.4 Klasy i SRP

```python
class UserRepository:
    """Wyłącznie operacje DB dla User."""
    def __init__(self, session: AsyncSession) -> None:
        self._session = session

class UserService:
    """Logika domenowa — bez znajomości bazy."""
    def __init__(self, repository: UserRepositoryProtocol) -> None:
        self._repo = repository
```

### 3.5 Type hints i Pydantic

```python
from typing import Protocol
from pydantic import BaseModel, Field
from uuid import UUID

class CreateUserRequest(BaseModel):
    email: str = Field(..., pattern=r"^[^@]+@[^@]+\.[^@]+$")
    username: str = Field(..., min_length=3, max_length=50)
    password: str = Field(..., min_length=8)

class UserRepositoryProtocol(Protocol):
    async def get_by_id(self, user_id: UUID) -> User | None: ...
    async def save(self, user: User) -> User: ...
```

---

## 4. Struktura projektu

```
project/
├── .prd.md
├── SLICES.md
├── pyproject.toml
├── src/
│   └── app_name/
│       ├── domain/           # Czysta logika, zero frameworków
│       │   ├── models.py
│       │   ├── services.py
│       │   └── exceptions.py
│       ├── infrastructure/   # DB, HTTP clients
│       │   ├── database.py
│       │   └── repositories.py
│       ├── api/              # FastAPI routers
│       │   ├── routes.py
│       │   └── schemas.py
│       └── config.py
└── tests/
    ├── unit/
    ├── integration/
    └── conftest.py
```

---

## 5. Reguły testowania

**Zasady:** Testy piszemy przed lub razem z kodem. Testy jednostkowe bez bazy/sieci — mockuj wszystko zewnętrzne. Pokrycie min. 80% dla `domain/`.

**Naming:**
```python
# Schemat: test_[co]_[warunek]_[wynik]
def test_register_user_with_existing_email_raises_duplicate_error(): ...
def test_calculate_order_total_with_discount_returns_reduced_price(): ...
```

**Struktura AAA:**
```python
def test_calculate_discount():
    # Arrange
    items = [OrderItem(price=Decimal("100"), quantity=2)]
    discount = Decimal("0.1")
    # Act
    result = calculate_order_total(items, discount)
    # Assert
    assert result == Decimal("180")
```

---

## 6. Prompt Templates

### Nowy slice
```
Implementuję slice: [NAZWA]
Stack: Python 3.12, FastAPI, SQLAlchemy 2.0, Pydantic v2

Wymagania: [FRAGMENT PRD]

Wygeneruj w kolejności:
1. Pydantic DTO (input/output)
2. Domain model (dataclass)
3. Repository Protocol
4. Service z logiką domenową
5. Testy jednostkowe (pytest, bez bazy)

Zasady: snake_case funkcje, PascalCase klasy, type hints wszędzie,
docstrings Google style, custom exceptions zamiast return None, max 20 linii/funkcja.
```

### Code review AI
```
Sprawdź poniższy kod Python pod kątem:
1. Czystości kodu (SRP, nazewnictwo, długość funkcji)
2. Bezpieczeństwa (SQL injection, hardcoded secrets)
3. Wydajności (N+1 queries)
4. Brakujących type hints i testów dla edge cases
Podaj konkretne sugestie z przykładami kodu.
[WKLEJ KOD]
```

### Generowanie testów
```
Napisz testy pytest dla poniższego kodu.
Wzorzec AAA. Nazwy: test_[co]_[warunek]_[wynik].
Uwzględnij happy path, edge cases, błędy.
Mockuj zależności przez pytest-mock.
[WKLEJ KOD]
```

### Refactoring
```
Zrefaktoruj poniższy kod zachowując funkcjonalność.
Zastosuj: SRP, małe nazwane funkcje, brak magic numbers, type hints, docstrings.
[WKLEJ KOD]
```

---

## 7. Checklist przed PR

```markdown
### Code Quality
- [ ] Kod rozumiemy i możemy wytłumaczyć
- [ ] Brak magic numbers / hardcoded strings
- [ ] Funkcje mają max ~20 linii
- [ ] Type hints na wszystkich publicznych interfejsach
- [ ] Docstrings na publicznych funkcjach/klasach

### Testy
- [ ] pytest przechodzi lokalnie
- [ ] Nowy kod ma testy (unit + integration gdzie potrzeba)
- [ ] Edge cases pokryte

### Slice
- [ ] Slice kompletny (end-to-end działa)
- [ ] SLICES.md zaktualizowany
- [ ] Brak TODO/FIXME bez powiązanego issue

### AI Code
- [ ] Wygenerowany kod zrozumiany przez autora
- [ ] Brak nadmiarowego kodu od AI
- [ ] Konwencje zachowane
```

---

## 8. Narzędzia i konfiguracja

**`pyproject.toml`:**
```toml
[tool.ruff]
line-length = 100
select = ["E", "F", "I", "N", "UP", "ANN", "B", "SIM"]

[tool.mypy]
strict = true
python_version = "3.12"

[tool.pytest.ini_options]
asyncio_mode = "auto"
testpaths = ["tests"]

[tool.coverage.report]
fail_under = 80
omit = ["*/infrastructure/*"]
```

**`.pre-commit-config.yaml`:**
```yaml
repos:
  - repo: https://github.com/astral-sh/ruff-pre-commit
    rev: v0.4.0
    hooks:
      - id: ruff
        args: [--fix]
      - id: ruff-format
  - repo: https://github.com/pre-commit/mirrors-mypy
    rev: v1.9.0
    hooks:
      - id: mypy
```

---

## 9. Quickstart

```
1. Napisz .prd.md
2. Stwórz SLICES.md z listą user stories
3. Dla każdego slica:
   a. Wklej prompt startowy do Copilot / VibeCode
   b. Generuj: schema → domain → testy → infra → API
   c. pytest → wszystko zielone?
   d. Oznacz slice DONE w SLICES.md
4. PR → checklist → review → merge
```

> **Pamiętaj:** AI przyspiesza pisanie kodu, ale nie zastępuje myślenia o architekturze. PRD i slice'y to robota zespołu — AI wypełnia implementację.

---

Dokument zawiera wszystko, czego potrzebuje zespół. Kilka rzeczy, które warto dopasować do waszego kontekstu:

- **Stack** — zamieniłem na FastAPI + SQLAlchemy jako przykład, dostosuj do tego czego faktycznie używacie
- **Prompt startowy** (sekcja 2) możecie wrzucić do pliku `.github/copilot-instructions.md` — Copilot automatycznie go wczytuje dla całego repo
- **SLICES.md** dobrze sprawdza się jako plik w głównym folderze projektu, widoczny dla całego zespołu bez wchodzenia do Jiry
