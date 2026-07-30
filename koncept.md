Ogólna koncepcja, która dobrze skaluje się do 2,5 mln transakcji przy małej liczbie zapytań do LLM, to nie jest klasyczne "daj dane do GPT i niech sklasyfikuje". To byłoby drogie, wolne i niestabilne.

Lepszy model to połączenie:

LLM jako generator wiedzy/reguł + klasyczny silnik obliczeniowy jako wykonawca na milionach rekordów.

Schemat:

                 ┌──────────────┐
                 │  2.5 mln      │
                 │  transakcji   │
                 └──────┬───────┘
                        │
                        ▼
              ┌──────────────────┐
              │  DuckDB / SQL    │
              │  szybka ewaluacja│
              └────────┬─────────┘
                       │
              wyniki błędów
              FP / FN
                       │
                       ▼
              ┌──────────────────┐
              │       LLM        │
              │ poprawia reguły  │
              └────────┬─────────┘
                       │
                 nowe reguły
                       │
                       ▼
              ┌──────────────────┐
              │  SQL / Regex     │
              │ klasyfikator      │
              └──────────────────┘
1. LLM nie klasyfikuje rekordów

Najważniejsza zasada.

Nie robimy:

transakcja 1 → GPT
transakcja 2 → GPT
...
transakcja 2 500 000 → GPT

To byłoby:

2,5 mln requestów,
ogromny koszt,
kilka dni działania,
brak powtarzalności.

Zamiast tego:

GPT → tworzy regułę

Przykład:

GPT analizuje 100 przykładów:

ABC Sp. z o.o.
Jan Kowalski ul. Lipowa 5
PHU Auto Serwis
Anna Nowak Warszawa

i generuje wiedzę:

firma:
- sp. z o.o.
- spółka
- phu
- fhu
- serwis
- transport
- sklep
2. Reguła jest wykonywana lokalnie

LLM zwraca np.:

{
 "keywords": [
   "sp. z o.o.",
   "phu",
   "fhu",
   "serwis",
   "transport"
 ]
}

Python buduje:

regexp_matches(
lower(nazwa_klienta),
'(sp\. z o\.o|phu|fhu|serwis|transport)'
)

DuckDB odpala to na:

2 500 000 rekordów

Koszt:

kilka sekund.

3. Używasz active learning

To jest klucz.

Nie pytasz LLM:

"co sądzisz o wszystkich danych?"

Pytasz:

"gdzie moja reguła się myli?"

Czyli:

Pierwsza wersja:

firma = zawiera "sp. z o.o."

Test:

2.5 mln rekordów

DuckDB znajduje:

False Positive

Czyli:

miało być osoba
ale uznałem za firmę

np.

Jan Sp. z o.o. Kowalski
False Negative

Czyli:

miało być firma
ale nie wykryłem

np.

Auto-Max Kowalski

Do LLM wysyłasz tylko:

Błędy:

FP:
- Jan Sp. z o.o. Kowalski
- Anna Serwis Nowak

FN:
- Auto-Max Kowalski
- ABC Handel

Czyli może:

50 rekordów.

Nie 2,5 mln.

4. Iteracyjne poprawianie reguły

Proces:

Iteracja 0

LLM:

firma = sp z oo

Wynik:

F1 = 0.72
Iteracja 1

Dajesz błędy:

FN:
Auto-Max
ABC Handel

LLM dodaje:

handel
auto

Nowa reguła:

sp z oo
phu
handel
auto

Wynik:

F1 = 0.86
Iteracja 2

Znów błędy.

Dodajesz:

usługi
zakład
produkcja

Wynik:

F1 = 0.93

Po kilku iteracjach masz bardzo dobrą regułę.

5. Klucz: reprezentatywny sampling

Nie wysyłasz wszystkich błędów.

Załóżmy:

FP = 200 000 rekordów

Nie ma sensu.

Robisz:

losuj 50 FP

ale lepiej:

clustering / różnorodność

Np.:

FP:

Jan Kowalski
Anna Kowalska
Piotr Nowak
...


to jeden typ błędu.

Ale:

ABC Auto
ABC Transport
ABC Handel

to inny typ.

Wysyłasz różne przypadki.

6. Cache reguł

LLM jest używany bardzo rzadko.

Przykładowo:

Iteracja 0:
GPT request #1

Iteracja 1:
GPT request #2

Iteracja 2:
GPT request #3

Iteracja 3:
GPT request #4

Po 5-10 iteracjach kończysz.

Czyli:

5-10 wywołań LLM

dla 2,5 mln rekordów.

7. Walidacja na osobnym zbiorze

Bardzo ważne.

Nie optymalizujesz na wszystkim.

Dzielisz:

2 500 000

↓

80%

train
2 mln


20%

test
500 tys.

Proces:

LLM poprawia reguły

↓

sprawdzasz F1 na train

↓

raz na koniec:

test

Dzięki temu unikasz dopasowania do przypadkowych przykładów.

8. Jeszcze lepsza wersja: hybryda reguł + ML

Docelowo można zrobić:

Reguły LLM
       +
Embedding similarity
       +
klasyczny model ML

Przykład:

Reguły:

sp z oo = +90%

Embedding:

"Auto-Max"
podobne do
"Auto Serwis"

Model:

firma / osoba

Ale dla danych typu:

"nazwa klienta + doklejony adres"

reguły często działają bardzo dobrze.

Podsumowanie architektury dla 2,5 mln rekordów

Najbardziej efektywny wzorzec:

Element	Zadanie
LLM	wymyślanie i poprawianie reguł
DuckDB	testowanie na milionach rekordów
Python	budowanie reguł i orkiestracja
Sampling	wybór najważniejszych błędów
Cache	ograniczenie kosztów API
Test set	kontrola jakości

W praktyce taki system może dojść do bardzo dobrej jakości po 5–20 wywołaniach LLM, zamiast milionów klasyfikacji. To jest dokładnie wzorzec stosowany w systemach human-in-the-loop / active learning dla dużych zbiorów danych.
