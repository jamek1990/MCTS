Oto **hiperszczegółowa kategoryzacja transakcji** dla prowadzenia firmy, z podziałem na poziomy szczegółowości, idealna do zaawansowanej analizy finansowej, controllingu i precyzyjnych dashboardów.

## 🏛 **PEŁNA HIERARCHICZNA STRUKTURA KATEGORYZACJI**

### **Poziom 0: STRUMIEŃ PIENIĘŻNY (Cash Flow)**
*   **INFLOW** (Wpływy)
*   **OUTFLOW** (Wypływy)

### **Poziom 1: KATEGORIA GŁÓWNA**
*   **1.0 PRZYCHODY OPERACYJNE**
*   **2.0 KOSZTY OPERACYJNE**
*   **3.0 FINANSOWE**
*   **4.0 INWESTYCYJNE**
*   **5.0 PODATKOWE**
*   **6.0 WYNAGRODZENIA & ZUS**
*   **9.0 INNE/SPECJALNE**

---

## 📑 **SZCZEGÓŁOWA TABELA TAGÓW Z KODAMI**

| Kod | Kategoria (Poziom 1) | Podkategoria (Poziom 2) | Szczegóły (Poziom 3) | Przykładowe Tagi (**do automatycznego przypisania**) | Charakter |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **1.1** | **PRZYCHODY OPERACYJNE** | **Sprzedaż produktów** | Główny asortyment | `PRZYCHÓD_produkt_A`, `PRZYCHÓD_produkt_B`, `PRZYCHÓD_detal` | Zmienny |
| **1.2** | | **Sprzedaż usług** | Usługi podstawowe | `PRZYCHÓD_usługa_serwis`, `PRZYCHÓD_usługa_abonament`, `PRZYCHÓD_projekt` | Zmienny |
| **1.3** | | **Sprzedaż eksport** | Rynek UE | `PRZYCHÓD_eksport_EU`, `PRZYCHÓD_eksport_SEPA_DE`, `PRZYCHÓD_eksport_UK` | Zmienny |
| | | | Rynek poza UE | `PRZYCHÓD_eksport_USA`, `PRZYCHÓD_eksport_CH`, `PRZYCHÓD_eksport_SWIFT` | Zmienny |
| **1.4** | | **Dzierżawa / Licencje** | Dochody pasywne | `PRZYCHÓD_dzierżawa_maszyn`, `PRZYCHÓD_opłata_licencyjna`, `PRZYCHÓD_franczyza` | Stały/Zmienny |
| **2.1** | **KOSZTY OPERACYJNE** | **Zaopatrzenie bezpośrednie** | **Surowce główne** | `KOSZT_surowiec_stal`, `KOSZT_surowiec_tworzywo`, `KOSZT_surowiec_chemikalia` | Zmienny |
| | | | **Materiały pomocnicze** | `KOSZT_materiał_opakowanie`, `KOSZT_materiał_biurowy`, `KOSZT_części_zamienne` | Zmienny |
| | | | **Energia produkcyjna** | `KOSZT_prąd_produkcja`, `KOSZT_gaz_produkcja`, `KOSZT_woda_produkcja` | Półstały |
| **2.2** | | **Usługi obce** | **Podwykonawstwo** | `KOSZT_podwykonawstwo`, `KOSZT_usługa_freelancer`, `KOSZT_transport_zewnętrzny` | Zmienny |
| | | | **Serwis i utrzymanie** | `KOSZT_serwis_maszyn`, `KOSZT_przegląd_budynku`, `KOSZT_ochrona_obiektu` | Stały |
| | | | **Marketing i sprzedaż** | `KOSZT_reklama_google`, `KOSZT_targi`, `KOSZT_agencyjne`, `KOSZT_CRM` | Zmienny |
| | | | **Doradztwo i prawo** | `KOSZT_kancelaria`, `KOSZT_doradca_podatkowy`, `KOSZT_audyt` | Zmienny |
| **2.3** | | **Koszty biurowe** | **Media biurowe** | `KOSZT_prąd_biuro`, `KOSZT_internet`, `KOSZT_telefon` | Stały |
| | | | **Administracja** | `KOSZT_poczta`, `KOSZT_ubezpieczenie_biura`, `KOSZT_rodo` | Stały |
| **3.1** | **FINANSOWE** | **Koszty kredytów** | **Rata kapitałowa** | `KOSZT_kredyt_kapitał`, `KOSZT_leasing_kapitał` | Stały |
| | | | **Odsetki** | `KOSZT_odsetki_kredyt`, `KOSZT_odsetki_leasing`, `KOSZT_odsetki_karta` | Stały |
| | | | **Prowizje bankowe** | `KOSZT_prowizja_przelew`, `KOSZT_prowizja_fx`, `KOSZT_abonament_bankowy` | Stały/Zmienny |
| **3.2** | | **Przychody finansowe** | **Lokaty / Inwestycje** | `PRZYCHÓD_odsetki_lokata`, `PRZYCHÓD_dywidenda` | Zmienny |
| **4.1** | **INWESTYCYJNE** | **Środki trwałe** | **Maszyny i urządzenia** | `INWEST_maszyna_produkcyjna`, `INWEST_sprzęt_IT`, `INWEST_pojazd` | Jednorazowy |
| | | | **Nieruchomości** | `INWEST_zakup_biura`, `INWEST_budowa_hali` | Jednorazowy |
| | | | **Wartości niematerialne** | `INWEST_oprogramowanie`, `INWEST_znak_towarowy`, `INWEST_licencja` | Jednorazowy |
| **4.2** | | **Remonty i modernizacje** | **Przebudowy** | `INWEST_remont_główny`, `INWEST_termomodernizacja` | Jednorazowy |
| **5.1** | **PODATKOWE** | **Podatki bezpośrednie** | **CIT / PIT** | `PODATEK_CIT_zaliczka`, `PODATEK_CIT_roczny`, `PODATEK_PIT` | Stały (cykliczny) |
| **5.2** | | **Podatki pośrednie** | **VAT** | `PODATEK_VAT_sprzedaż`, `PODATEK_VAT_zakup` | Zmienny |
| | | | **Akcyza** | `PODATEK_akcyza` | Zmienny |
| **6.1** | **WYNAGRODZENIA** | **Płace netto** | **Wynagrodzenia zasadnicze** | `WYPŁATA_pensja`, `WYPŁATA_premia`, `WYPŁATA_urlop` | Stały |
| **6.2** | | **Składki ZUS** | **Składka pracodawcy** | `ZUS_emerytalna`, `ZUS_rentowa`, `ZUS_wypadkowa`, `ZUS_FP`, `ZUS_zdrowotna` | Stały |
| **6.3** | | **Benefity** | **Pakiety dodatkowe** | `KOSZT_benefit_ubezpieczenie`, `KOSZT_benefit_sport`, `KOSZT_benefit_posiłki` | Stały |
| **9.1** | **INNE** | **Korekty i zwroty** | **Zwroty klientom** | `KOREKTA_zwrot_klientowi`, `KOREKTA_reklamacja` | Zmienny |
| | | | **Zwroty dostawcom** | `KOREKTA_zwrot_od_dostawcy` | Zmienny |
| **9.2** | | **Darowizny** | **Cele charytatywne** | `INNE_darowizna` | Jednorazowy |

---

## 🛠 **ZAWAANSOWANA IMPLEMENTACJA – SYSTEM KONTROLNY**

### **Mapowanie na Rachunek Zysków i Strat (RZiS) & Cash Flow:**
| Kategoria Tagów | Odpowiednik w RZiS | Sekcja w Cash Flow |
| :--- | :--- | :--- |
| **1.x PRZYCHODY OPERACYJNE** | Przychody ze sprzedaży | Działalność operacyjna |
| **2.x KOSZTY OPERACYJNE** | Koszty działalności operacyjnej | Działalność operacyjna |
| **3.x FINANSOWE** | Przychody/koszty finansowe | Działalność finansowa |
| **4.x INWESTYCYJNE** | --- | Działalność inwestycyjna |
| **5.x PODATKOWE** | Podatek dochodowy | Działalność operacyjna/finansowa |
| **6.x WYNAGRODZENIA** | Koszty osobowe | Działalność operacyjna |

### **Kluczowe Metryki do Grafiki/Dashboardu:**

**1. MARGINESY OPERACYJNE:**
*   `Marża brutto = (1.x - 2.1) / 1.x * 100%` (marża na surowcach)
*   `EBITDA = 1.x - (2.x + 6.x)` (zysk przed amortyzacją, odsetkami, podatkami)

**2. ANALIZA KOSZTÓW STAŁYCH vs. ZMIENNYCH:**
*   `Koszty Stałe = 2.2(część) + 2.3 + 3.1(rata kap.) + 5.1 + 6.x`
*   `Koszty Zmienne = 2.1 + 2.2(część) + 5.2`
*   `Próg rentowności = Koszty Stałe / Marża %`

**3. WYKRESY SPECJALISTYCZNE:**
*   **Waterfall (kaskadowy):** Od Przychodów (1.x) do Wyniku Netto.
*   **Wykres warstwowy (stacked area):** Skumulowane koszty w czasie z podziałem na kategorie.
*   **Treemap (mapa drzewa):** Wizualizacja proporcji wszystkich podkategorii kosztów (2.x) w danym miesiącu.
*   **Wykres kontrolny (statystyczny):** Średni miesięczny koszt danej kategorii ± odchylenie standardowe (wykrywanie anomalii).

### **Proces Zaawansowanego Tagowania:**

1.  **Poziom 0: Automatyczne pobieranie z banku** (MT940/CSV) – już rozdziela na wpływy/wypływy.
2.  **Poziom 1: Automatyczne reguły:**
    *   Kontrahent z listy "Klienci" → `1.x`
    *   Tytuł zawiera "VAT" → `5.2`
    *   Cykliczna, ta sama kwota 1-10 dnia miesiąca → `6.1`
    *   Kontrahent "ZUS", "US" → odpowiednio `6.2` lub `5.1`
3.  **Poziom 2 & 3: Półautomatyczne (z sugestiami):**
    *   System proponuje 3 najbardziej prawdopodobne tagi na podstawie historii.
    *   Użytkownik potwierdza lub wybiera inny z rozwijanej listy **słownika kontrolowanego**.
4.  **Poziom 4 (opcjonalny): Tag projektu/działu:** `#projekt_alfa`, `#dział_produkcja`

### **Przykład transakcji z pełnym tagowaniem:**
*   **Transakcja:** Wypłata, 15.03.2024, -12 750 zł, "Firma Serwisowa Sp. z o.o., faktura 001/2024 za naprawę wtryskarki"
*   **Automatyczne tagi:**
    *   `OUTFLOW`
    *   `2.0_KOSZTY_OPERACYJNE`
    *   `2.2_Usługi_obce` (z podpowiedzi)
*   **Ręczne doprecyzowanie:**
    *   `2.2.2_serwis_i_utrzymanie` (z listy rozwijanej)
    *   `#maszyna_nr_5` (tag dodatkowy)
    *   `#projekt_modernizacja_2024` (tag projektu)

### **Dashboard dla Dyrektora Finansowego:**

**Panel Główny:**
*   **Wskaźnik Płynności:** `(1.x - wszystkie OUTFLOW) / 2.1(koszty stałe) = X miesięcy przetrwania`
*   **DRILL-DOWN:** Kliknięcie w segment "2.2 Usługi obce" rozwija szczegóły: `2.2.1_podwykonawstwo`, `2.2.2_serwis`, `2.2.3_marketing`.

**Alerty:**
*   "Koszt `2.1.3_energia` przekroczył o 30% średnią z ostatnich 3 miesięcy"
*   "Udział `6.x_wynagrodzenia` w `1.x_przychodach` przekroczył bezpieczny próg 35%"

Ta struktura pozwala nie tylko na **piękne grafy**, ale przede wszystkim na **głęboką analizę przyczynowo-skutkową**, budżetowanie, forecasting i realne zarządzanie rentownością każdej linii biznesowej.
