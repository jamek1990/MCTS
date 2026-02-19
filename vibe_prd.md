Jesteś doświadczonym Product Managerem i architektem systemów. 
Stwórz szczegółowy PRD (Product Requirements Document) dla następującego projektu:

[OPIS PROJEKTU]

---

PRD musi uwzględniać następujące zasady projektowe — traktuj je jako twarde wymagania 
techniczne, nie opcjonalne:

---

### 1. VERTICAL SLICES (Programowanie Pionowe)

Każda funkcjonalność musi być zaprojektowana jako kompletny, samodzielny wycinek 
systemu — od UI/API do bazy danych.

Dla każdego slice'a zdefiniuj:
- Wejście (trigger, endpoint, event)
- Logikę biznesową
- Warstwę danych (odczyt / zapis / transformacja)
- Wyjście (odpowiedź, efekt uboczny, zdarzenie)
- Kryteria akceptacji (testowalne, binarne)

Nie dopuszczaj poziomych warstw jako jednostek dostarczania. 
Każdy sprint/etap = działający slice end-to-end.

---

### 2. IDEMPOTENTNOŚĆ OPERACJI BATCHOWYCH

Wszystkie operacje batchowe i pipeline'y przetwarzania danych muszą być 
zaprojektowane tak, by ponowne uruchomienie po przerwaniu było bezpieczne 
(zero duplikatów, zero utraty danych).

Dla każdej operacji batchowej wymagaj opisu:
- Mechanizmu śledzenia stanu (checkpoint table, processed_ids, offset, cursor)
- Klucza idempotentności (skąd pochodzi, jak jest generowany)
- Strategii "at-least-once" z deduplikacją po stronie zapisu
- Obsługi częściowych niepowodzeń (retry scope — rekord vs batch vs job)
- Testu regresyjnego: "uruchom dwukrotnie, porównaj wyniki — muszą być identyczne"

Dopuszczalne wzorce: upsert po natural key, transakcja z warunkiem, 
idempotency key w nagłówku, outbox pattern, saga z kompensacją.

---

### 3. WYDAJNOŚĆ NA DUŻYCH ZBIORACH DANYCH

Każdy slice operujący na danych musi mieć zdefiniowane:
- Oczekiwany wolumen (rzędy, rozmiar, RPS) — podaj konkretne liczby
- Strategię partycjonowania / paginacji (keyset pagination zamiast OFFSET)
- Indeksy wymagane do działania (wymień explicite, uzasadnij)
- Czy operacja jest streamowana czy buforowana — uzasadnij
- Limity pamięciowe — brak operacji "załaduj wszystko do RAM"
- Plan skalowania: co się stanie przy 10x wolumenie?

Wymagaj benchmarków akceptacyjnych (np. "przetworzenie 1M rekordów < 5 min 
przy użyciu < 512 MB RAM").

---

### FORMAT WYJŚCIOWY PRD

Dla każdego slice'a użyj tej struktury:

#### Slice: [Nazwa]
**Cel biznesowy:** (1 zdanie)  
**Trigger:** (co uruchamia)  
**Wejście:** (schemat danych)  
**Logika:** (kroki, decyzje, reguły)  
**Wyjście:** (schemat, efekty)  
**Idempotentność:** (mechanizm + klucz)  
**Wydajność:** (wolumen, indeksy, strategia)  
**Kryteria akceptacji:** (lista testowalnych asercji)  
**Ryzyka:** (co może pójść nie tak)

---

Na końcu PRD dodaj:
- Listę wszystkich tabel/kolekcji z ich indeksami i estimated row count
- Diagram zależności między slices (text-based)
- Listę pytań otwartych wymagających decyzji przed implementacją
- Propozycję kolejności implementacji slices (z uzasadnieniem)

Pisz precyzyjnie. Nie używaj ogólników. Każde wymaganie musi być testowalne.
