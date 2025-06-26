# Framework dla Zautomatyzowanej Analizy Rozmów Sprzedażowych z Wykorzystaniem Zaawansowanych Modeli Językowych (LLM)

**Dokument Wewnętrzny: Propozycja Projektowa**

- **Wersja:** 1.0
- **Data:** 26.06.2025

## 1. Streszczenie Zarządcze (Executive Summary)

Niniejszy dokument opisuje architekturę i strategię wdrożenia zaawansowanego systemu analitycznego, którego celem jest automatyczne wykrywanie potencjalnych przypadków missellingu i misconduct w transkrypcjach rozmów sprzedażowych dotyczących produktów inwestycyjnych. W obliczu rosnących wymogów regulacyjnych (m.in. MiFID II, dyrektywy konsumenckie), ryzyka reputacyjnego oraz operacyjnej nieefektywności manualnych audytów, proponowane rozwiązanie oferuje strategiczną przewagę poprzez skalowalną, spójną i dogłębną analizę 100% interakcji z klientami.

System wykorzysta najnowszej generacji modele językowe (LLM), takie jak modele z rodziny Gemini, do semantycznej analizy dialogów, identyfikacji ryzykownych wypowiedzi i generowania ustrukturyzowanych raportów dla działu Compliance. Wdrożenie frameworku pozwoli na przejście z reaktywnego na proaktywny model zarządzania zgodnością, minimalizując ryzyko i podnosząc standardy obsługi klienta.

## 2. Kontekst Biznesowy i Cele Projektu

### 2.1. Identyfikacja Problemu

Obecne procesy kontroli jakości rozmów sprzedażowych opierają się głównie na manualnym, wyrywkowym odsłuchu, co generuje następujące wyzwania:

- **Ograniczony Zasięg:** Analizie poddawany jest jedynie niewielki procent rozmów, co stwarza ryzyko przeoczenia systemowych lub jednostkowych nieprawidłowości.
- **Wysokie Koszty Operacyjne:** Manualny audyt jest czasochłonny i wymaga zaangażowania wysoko wykwalifikowanych specjalistów.
- **Subiektywizm Oceny:** Ocena analityka może być niejednorodna i zależna od jego doświadczenia i interpretacji.
- **Reaktywność:** Problemy są często identyfikowane z opóźnieniem, już po wystąpieniu potencjalnej szkody.

### 2.2. Cele Projektu

Głównym celem jest wdrożenie zautomatyzowanego systemu, który zrealizuje następujące założenia:

- **Zwiększenie Pokrycia Analitycznego:** Docelowo analiza 100% zarejestrowanych rozmów sprzedażowych.
- **Podniesienie Efektywności Wykrywania:** Wzrost wskaźnika wykrywalności (True Positive Rate) zdefiniowanych nieprawidłowości.
- **Standaryzacja Procesu Oceny:** Zapewnienie obiektywnej i spójnej analizy w oparciu o predefiniowaną taksonomię ryzyka.
- **Optymalizacja Pracy Działu Compliance:** Redukcja czasu poświęcanego na manualny odsłuch i umożliwienie analitykom skupienia się na weryfikacji przypadków o najwyższym priorytecie.
- **Stworzenie Pętli Sprzężenia Zwrotnego:** Gromadzenie danych analitycznych w celu identyfikacji trendów, potrzeb szkoleniowych oraz doskonalenia skryptów sprzedażowych.

## 3. Architektura Systemu i Przepływ Danych (Data Flow)

Proponowany system będzie działał w oparciu o architekturę potokową (pipeline), składającą się z czterech głównych modułów.

> [Obraz schematu blokowego przedstawiającego przepływ danych: 1. Surowe Nagrania Audio -> 2. Moduł Transkrypcji (STT) -> 3. Oczyszczone Transkrypcje (z podziałem na mówców) -> 4. Rdzeń Analityczny (LLM) zasilany Taksonomią Nieprawidłowości -> 5. Ustrukturyzowane Wyniki (JSON) -> 6. Baza Danych Wyników -> 7. Interfejs Użytkownika dla Compliance / Dashboardy]

### Krok 1: Pozyskiwanie i Przetwarzanie Wstępne Danych (ETL - Extract, Transform, Load)

- **Źródło:** System contact center przechowujący nagrania rozmów w formacie audio (np. `.wav`, `.mp3`).
- **Proces:**
    - **Transkrypcja (Speech-to-Text - STT):** Automatyczna konwersja plików audio na tekst. Kluczowe jest użycie silnika STT o wysokiej skuteczności dla języka polskiego, wspierającego terminologię finansową.
    - **Diarazycja Mówców (Speaker Diarization):** Automatyczne rozpoznanie i oznaczenie, która część dialogu należy do doradcy, a która do klienta (`[AGENT]`, `[KLIENT]`). Jest to krytyczne dla analizy kontekstowej.
    - **Czyszczenie i Normalizacja:** Usunięcie artefaktów (np. znaczniki czasu), normalizacja formatu tekstu.

### Krok 2: Rdzeń Analityczny (LLM Analysis Core)

- **Technologia:** Wywołania API do zaawansowanego modelu językowego (np. Gemini 1.5 Pro).
- **Proces:** Dla każdej transkrypcji system dynamicznie tworzy i wykonuje precyzyjnie skonstruowane zapytanie (prompt), składające się z:
    - **Kontekstu i Roli (Persona):** "Jesteś ekspertem ds. compliance w instytucji finansowej..."
    - **Taksonomii Nieprawidłowości:** Pełna, aktualna lista zdefiniowanych kategorii missellingu i misconduct wraz z przykładami (patrz sekcja 4.1).
    - **Zadania Analitycznego:** Jasna instrukcja nakazująca modelowi przeanalizowanie załączonej transkrypcji i zwrócenie wyniku w określonym formacie.
    - **Transkrypcji (Dane Wejściowe):** Pełny tekst rozmowy.
    - **Schematu Wyjściowego (Output Schema):** Wymuszenie na modelu odpowiedzi w formacie JSON, co zapewnia spójność i łatwość dalszego przetwarzania maszynowego.

### Krok 3: Repozytorium Wyników i Warstwa Danych

- **Technologia:** Baza danych (np. PostgreSQL, MongoDB) zoptymalizowana do przechowywania i odpytywania danych częściowo ustrukturyzowanych (JSON).
- **Proces:** Każdy wynik analizy jest zapisywany w bazie danych, powiązany z identyfikatorem rozmowy. Struktura rekordu obejmuje m.in.:
    - ID rozmowy
    - Pełną transkrypcję
    - Surową odpowiedź JSON z modelu
    - Status weryfikacji (np. Nowy, Potwierdzony, Odrzucony)
    - Notatki analityka Compliance

### Krok 4: Interfejs Użytkownika i Raportowanie (UI/BI Layer)

- **Technologia:** Aplikacja webowa (np. zbudowana w React/Angular) oraz narzędzia Business Intelligence (np. Power BI, Tableau).
- **Funkcjonalności:**
    - **Panel Spraw (Case Management):** Lista rozmów oflagowanych przez system, z możliwością sortowania i filtrowania (np. po typie ryzyka, dacie, doradcy).
    - **Widok Szczegółowy Rozmowy:** Interaktywny widok transkrypcji z automatycznie podświetlonymi fragmentami zidentyfikowanymi przez AI. Obok każdego fragmentu wyświetlana jest kategoria problemu i uzasadnienie modelu.
    - **Narzędzia Walidacji:** Możliwość potwierdzenia lub odrzucenia sugestii AI przez analityka, dodanie własnych komentarzy.
    - **Dashboardy Analityczne:** Agregacja danych w celu śledzenia trendów, np. najczęstsze typy nieprawidłowości, doradcy z najwyższym wskaźnikiem ryzyka, skuteczność modelu.

## 4. Kluczowe Komponenty i Koncepcje

### 4.1. Taksonomia Nieprawidłowości (Misconduct Taxonomy)

Jest to fundament systemu. Musi być precyzyjny i rozwijany we współpracy z działami Prawnym i Compliance. Przykładowa, rozszerzona taksonomia:

| Kategoria Główna | Podkategoria / Opis | Słowa Kluczowe / Przykładowe Zachowania |
| :--- | :--- | :--- |
| **Gwarancje i Ryzyko** | Gwarantowanie stopy zwrotu | `"Na pewno Pan zarobi"`, `"gwarantowany zysk"`, `"to nie może stracić"` |
| | Minimalizowanie ryzyka | `"Bezpieczne jak lokata"`, `"ryzyko jest czysto teoretyczne"`, `"praktycznie zerowe ryzyko"` |
| **Profilowanie Klienta** | Niewystarczające badanie potrzeb (ankieta MiFID) | Brak pytań o horyzont czasowy, cele, doświadczenie, stosunek do ryzyka |
| | Ignorowanie profilu klienta | Proponowanie produktu agresywnego klientowi deklarującemu awersję do ryzyka |
| **Koszty i Opłaty** | Niejasne przedstawienie kosztów | Pomijanie opłat za zarządzanie, wejście/wyjście; używanie skomplikowanego żargonu |
| | Ukrywanie struktury opłat | Brak informacji o całkowitym wskaźniku kosztów (TER) |
| **Presja i Techniki Sprzedażowe**| Wywieranie presji czasowej | `"Oferta tylko dzisiaj"`, `"musi się Pan szybko decydować"`, `"limit miejsc"` |
| | Wykorzystywanie braku wiedzy klienta | Stosowanie niezrozumiałego żargonu bez wyjaśnienia, aby wywołać wrażenie profesjonalizmu |
| **Zgodność Produktowa** | Sprzedaż produktu "off-label" | Proponowanie produktu do celów niezgodnych z jego konstrukcją (np. produktu długoterminowego na cel krótkoterminowy) |
| **Procedury i Regulacje** | Naruszenie procedur wewnętrznych | Brak nagrywania oświadczeń, brak dostarczenia wymaganych dokumentów (KID) |
| **Pozycjonowanie i Porównania** | Nierzetelne porównania | Porównywanie funduszu akcyjnego do lokaty bankowej bez jasnego wskazania różnic w ryzyku |
| | Celowe pomijanie alternatyw | Prezentowanie tylko jednego, najkorzystniejszego dla sprzedawcy produktu, bez przedstawienia innych opcji |
| **Język i Komunikacja** | Pasywna komunikacja o ryzyku | Używanie form warunkowych: `"Straciłby Pan, gdyby..."`, zamiast aktywnego: `"Ten produkt wiąże się z ryzykiem straty"` |
| | Bagatelizowanie znaczenia dokumentów | `"To tylko taka formalność, proszę tu podpisać"`; `"Standardowe zapisy, nie trzeba czytać"` |
| **Aspekty Behawioralne** | Wykorzystywanie autorytetu | `"Znam się na tym od lat i to jest najlepsza opcja"`; `"Wszyscy moi zamożni klienci to kupują"` |
| | Niezgodność komunikacji werbalnej z niewerbalną (ton głosu) | Wykrywanie wahania lub braku pewności w głosie doradcy podczas omawiania ryzyka (wymaga analizy audio) |

### 4.2. Zaawansowana Inżynieria Promptów (Prompt Engineering)

Skuteczność rdzenia analitycznego jest wprost proporcjonalna do jakości i precyzji zapytań (promptów) kierowanych do modelu LLM. Zamiast jednego, ogólnego polecenia, stosuje się wieloetapowe i wielowarstwowe strategie, aby prowadzić model przez proces analityczny, maksymalizując dokładność i minimalizując ryzyko błędów ("halucynacji").

**Kluczowe techniki:**

1.  **Strategia Łańcuchowa (Chain-of-Thought - CoT) i Dekompozycja Zadania:**
    Złożone zadanie analizy całej rozmowy jest rozbijane na prostsze, logicznie następujące po sobie kroki. To zmusza model do "myślenia krok po kroku" i budowania wniosków na solidnych podstawach.

    *   **Prompt 1 (Ekstrakcja i Streszczenie):** "Przeanalizuj poniższą transkrypcję. Zidentyfikuj i podsumuj w punktach: a) kluczowe potrzeby, cele i poziom wiedzy finansowej klienta, b) główne cechy, korzyści i ryzyka produktu przedstawione przez doradcę, c) najważniejsze momenty rozmowy, w których podejmowane są decyzje lub wyrażane są wątpliwości."
        *   *Cel:* Stworzenie skondensowanego, neutralnego podsumowania, które posłuży jako kontekst dla dalszej analizy.
    *   **Prompt 2 (Wstępna Identyfikacja Ryzyk):** "Bazując na transkrypcji ORAZ powyższym streszczeniu, zidentyfikuj fragmenty rozmowy, które mogą potencjalnie nosić znamiona nieprawidłowości zgodnie z załączoną taksonomią. Dla każdego fragmentu wskaż kategorię ryzyka i zacytuj odpowiedni fragment. Na tym etapie nie wydawaj ostatecznego werdyktu."
        *   *Cel:* Wstępne "oflagowanie" podejrzanych fragmentów bez dogłębnej oceny.
    *   **Prompt 3 (Głęboka Analiza i Formatowanie Wyjścia):** "Dla każdego zidentyfikowanego powyżej fragmentu, dokonaj szczegółowej analizy. Uzasadnij, dlaczego dany fragment jest (lub nie jest) nieprawidłowością w kontekście całej rozmowy i taksonomii. Wygeneruj ostateczny wynik w formacie JSON, używając podanego schematu. Jeśli nie zidentyfikowano żadnych ryzyk, zwróć pustą listę."
        *   *Cel:* Ostateczna, uargumentowana ocena i ustrukturyzowanie wyniku.

2.  **Uczenie na Przykładach (Few-Shot Learning):**
    W promcie, oprócz instrukcji, umieszcza się 2-3 wysokiej jakości przykłady kompletnej analizy (tzw. "shots"). Każdy przykład zawiera fragment transkrypcji i idealny, oczekiwany wynik w formacie JSON.
    *   *Przykład:*
        ```json
        {
          "input_transcript": "[AGENT]: ...i proszę Pana, ten fundusz to jest praktycznie zerowe ryzyko, bezpieczniejsze niż lokata...",
          "output_analysis": {
            "risk_category": "Gwarancje i Ryzyko",
            "risk_subcategory": "Minimalizowanie ryzyka",
            "quote": "praktycznie zerowe ryzyko, bezpieczniejsze niż lokata",
            "justification": "Agent wprost porównuje produkt inwestycyjny do lokaty bankowej, trywializując ryzyko inwestycyjne, co jest niedozwoloną praktyką i wprowadza klienta w błąd.",
            "severity_score": 9
          }
        }
        ```
    *   *Cel:* "Nauczenie" modelu pożądanego formatu wyjściowego, tonu i głębokości analizy na konkretnych, wzorcowych przykładach.

3.  **Definiowanie Roli i Kontekstu (Persona & Context Priming):**
    Zamiast generycznego "Jesteś asystentem AI", prompt precyzyjnie określa rolę, w jakiej ma działać model.
    *   *Przykład rozbudowanej persony:* "Jesteś niezwykle skrupulatnym i doświadczonym analitykiem compliance w banku nadzorowanym przez KNF. Twoim głównym zadaniem jest ochrona interesu klienta i reputacji firmy. Analizujesz rozmowy pod kątem dyrektywy MiFID II i wewnętrznych regulaminów. Jesteś wyczulony na wszelkie techniki manipulacyjne, minimalizowanie ryzyka i niejasności w komunikacji. Twoja ocena musi być obiektywna, oparta wyłącznie na faktach z transkrypcji."
    *   *Cel:* "Nastrojenie" modelu na odpowiedni tryb pracy, zwiększenie uwagi na konkretne aspekty analizy.

4.  **Wymuszanie Struktury Wyjściowej (JSON Schema):**
    Aby zapewnić 100% niezawodność w dalszym, automatycznym przetwarzaniu, w promcie umieszcza się definicję schematu JSON, którego model musi bezwzględnie przestrzegać.
    *   *Przykład:* "Twoja odpowiedź MUSI być poprawnym obiektem JSON pasującym do następującego schematu: `{\"findings\": [{\"category\": \"string\", \"quote\": \"string\", \"justification\": \"string\", \"severity\": \"integer (1-10)\"}]}`. Nie dołączaj żadnego tekstu przed ani po obiekcie JSON."
    *   *Cel:* Gwarancja maszynowej czytelności wyników i eliminacja potrzeby parsowania niestrukturyzowanego tekstu.

Takie podejście, łączące kilka zaawansowanych technik, przekształca model LLM z "generatora tekstu" w precyzyjne narzędzie analityczne, dostosowane do specyficznych wymagań dziedziny compliance.

## 5. Fazy Wdrożenia i Mierniki Sukcesu (KPIs)

### 5.1. Fazy Projektu

- **Faza 1: Proof of Concept (PoC) (1-2 miesiące):**
    - **Cel:** Weryfikacja technicznej wykonalności i skuteczności modelu na ograniczonej próbce (ok. 100-200 transkrypcji).
    - **Działania:** Opracowanie wstępnej taksonomii, development podstawowego skryptu analitycznego, manualna weryfikacja wyników.
- **Faza 2: Wdrożenie Pilotażowe (MVP) (3-4 miesiące):**
    - **Cel:** Uruchomienie systemu dla jednego zespołu sprzedażowego, budowa podstawowego interfejsu dla Compliance.
    - **Działania:** Integracja z systemem STT, budowa bazy danych, stworzenie panelu do weryfikacji.
- **Faza 3: Pełne Wdrożenie (Rollout) i Optymalizacja (ciągłe):**
    - **Cel:** Stopniowe rozszerzanie systemu na całą organizację.
    - **Działania:** Skalowanie infrastruktury, rozwój dashboardów analitycznych, ciągłe doskonalenie taksonomii i promptów w oparciu o feedback od analityków.

### 5.2. Kluczowe Wskaźniki Efektywności (KPIs)

- **Precyzja Modelu (Precision):** Jaki procent rozmów oflagowanych przez system jako problematyczne został faktycznie potwierdzony przez analityka?
- **Czułość Modelu (Recall):** Jaki procent wszystkich faktycznie problematycznych rozmów (zidentyfikowanych manualnie w próbce kontrolnej) został poprawnie wykryty przez system?
- **Redukcja Czasu Analizy:** Średni czas potrzebny na analizę jednej rozmowy (manualnie vs. weryfikacja w systemie).
- **Procent Pokrycia Analitycznego:** % wszystkich rozmów poddanych analizie.

## 6. Analiza Ryzyka i Kwestie Bezpieczeństwa

- **Poufność Danych:** Konieczność zapewnienia, że dane (transkrypcje) są przetwarzane w bezpiecznym środowisku (np. poprzez wykorzystanie usług chmurowych klasy enterprise z odpowiednimi umowami o przetwarzaniu danych) lub z zastosowaniem technik anonimizacji/pseudonimizacji.
- **Jakość Transkrypcji:** Skuteczność systemu jest silnie uzależniona od jakości silnika STT. Należy przeprowadzić ewaluację dostawców tej technologii.
- **"Halucynacje" Modelu:** Ryzyko, że model wygeneruje nieprawdziwe lub niepoparte dowodami wnioski. Minimalizowane przez precyzyjną inżynierię promptów i obowiązkowy nadzór ludzki (Human-in-the-Loop).
