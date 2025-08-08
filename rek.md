Propozycja zadania rekrutacyjnego
Temat:
Analiza tekstowa z wykorzystaniem NLP/ML do automatycznego przypisywania kategorii do zgłoszeń reklamacyjnych klientów banku.

Opis zadania:
Wyobraź sobie, że pracujesz w zespole Text Analytics w banku. Twoim zadaniem jest przygotowanie prototypowego rozwiązania do automatycznego przypisywania zgłoszeń reklamacyjnych klientów do jednej z kilku kategorii, które pozwolą przyspieszyć obsługę i analizę tych zgłoszeń.

Dostarczamy Ci zbiór przykładowych (syntetycznych) reklamacji w formie tekstowej oraz ich przypisania do 6 kategorii (np. opłaty, transakcje nieautoryzowane, obsługa klienta, kredyty, bankowość internetowa, inne).

Twoje zadanie:

Zbuduj model lub pipeline, który automatycznie przypisuje kategorię do reklamacji.
Możesz użyć klasycznych modeli ML, modeli językowych (np. BERT), lub metod GenAI – dobór metody zależy od Ciebie.

Zaprojektuj ocenę skuteczności działania systemu (np. accuracy, F1, analiza błędów).
Wyjaśnij, co dobrze działa, a co nie – i dlaczego.

Zaproponuj, jak można by to rozwiązanie wdrożyć w skali produkcyjnej – co byłoby kolejnym krokiem.

📊 Prezentacja wyników:
Poprosimy o 3-slajdową prezentację (max 1 slajd rezerwowy), którą zaprezentujesz zespołowi:

Slajd 1 – Problem i podejście
Jak rozumiesz zadanie i dane?

Jakie techniki wybrałeś i dlaczego?

Slajd 2 – Wyniki i obserwacje
Wyniki metryk (np. F1, Accuracy)

Przykłady poprawnych i błędnych predykcji

Analiza błędów / ograniczeń

Slajd 3 – Wdrożenie i rozwój
Jak widzisz integrację tego rozwiązania w produkcji?

Jakie byłyby kolejne kroki w rozwoju modelu/systemu?

Gdzie widzisz ryzyka i możliwości?

📦 Dane:
Możecie dołączyć:

Kilkaset syntetycznych zgłoszeń reklamacyjnych (np. 500–1000 rekordów, najlepiej CSV z tekst, kategoria).

Kilka opisów kategorii (np. 1 zdanie opisujące każdą z nich, jeśli nie są oczywiste).

Można też zasymulować dane, np. na podstawie publicznych źródeł (Twitter, forum bankowe, opinie itp.).

🧠 Co to zadanie sprawdza:
Umiejętność budowy pipeline'u NLP/ML lub wykorzystania GenAI

Umiejętność inżynierii cech / doboru modelu

Zrozumienie języka biznesu (prezentacja)

Krytyczne myślenie (co działa, co nie, jak rozwijać dalej)

Dobór metryk i interpretacja wyników

Jeśli chcesz, mogę przygotować przykładowy plik danych reklamacyjnych i szablon prezentacji do wysłania kandydatom. Czy to zadanie Ci odpowiada, czy wolisz inny temat (np. transkrypcje rozmów, kategoryzacja transakcji)?








Powiedziałeś(-aś):
spróbuj teraz zadanie z transkrypcjami rozmów


ChatGPT powiedział:
Świetnie — temat analizy transkrypcji rozmów to bardzo bogate źródło wyzwań NLP, idealne dla seniora. Zadanie powinno pozwalać na sprawdzenie:

czy kandydat umie operować na danych dialogowych (a nie tylko klasycznym tekście),

czy potrafi wydobyć wartościowe informacje z rozmów,

jak radzi sobie z rozumieniem kontekstu (kto mówi, co się wydarzyło, intencje),

czy potrafi zaproponować użyteczne wskaźniki / automatyzacje.

✅ Propozycja zadania rekrutacyjnego: analiza transkrypcji rozmów
Temat:
Wydobywanie informacji z rozmów klient–bank: klasyfikacja celu rozmowy oraz identyfikacja problematycznych interakcji.

📝 Opis zadania:
Jesteś częścią zespołu Text Analytics w banku. Otrzymujesz zestaw zanonimizowanych transkrypcji rozmów telefonicznych między doradcami a klientami. Twoim celem jest zbudowanie rozwiązania, które automatycznie:

Określa temat (lub cel) rozmowy – np. zapytanie o saldo, reklamacja, zlecenie przelewu, zapytanie o kredyt, sprzedaż produktu, itd.

Identyfikuje, czy rozmowa może być problematyczna lub wymaga interwencji – np. klient był niezadowolony, rozmowa się nie powiodła, wystąpił konflikt lub niezgodność komunikacji.

📦 Dane (dostarczacie kandydatowi):
Kilkadziesiąt (np. 50–100) przykładowych transkrypcji rozmów z klientami (syntetycznych lub zanonimizowanych).

Każda transkrypcja powinna zawierać:

oznaczenie wypowiedzi (Agent: vs Klient:)

pełen dialog (np. 10–30 wymian)

ewentualnie etykietę: temat, czy problematyczna (dla części danych – np. 50%).

Jeśli nie chcecie udostępniać realnych transkrypcji, możecie:

stworzyć syntetyczne na podstawie typowych scenariuszy (lub ja mogę pomóc je wygenerować).

🎯 Cele zadania:
Zbuduj model(y), które:

przypisują rozmowie temat (klasyfikacja wieloklasowa),

oceniają, czy rozmowa może być problematyczna (binarna klasyfikacja).

Zaproponuj sposób ekstrakcji dodatkowych informacji (opcjonalnie):

np. wykrycie fragmentu rozmowy, w którym klient wyraża frustrację,

lub identyfikacja momentu sprzedażowego (jeśli dotyczy).

Uzasadnij wybór metody – klasyczny ML, transformer, zero-shot GenAI, itd.

📊 Prezentacja (3 slajdy):
Slajd 1 – Podejście
Jak rozumiesz dane i problem?

Jakie techniki/model(e) wybrałeś i dlaczego?

Czy przetwarzałeś dialog jako całość, czy jako zbiór wypowiedzi?

Slajd 2 – Wyniki
Metryki klasyfikacyjne (np. F1, accuracy, precision/recall) – osobno dla celu rozmowy i detekcji problematycznych rozmów

Przykłady poprawnych vs błędnych klasyfikacji

Ewentualna analiza emocji / zachowań klienta

Slajd 3 – Co dalej
Co można byłoby rozwinąć lub ulepszyć?

Jakie byłyby kroki w kierunku produkcyjnego rozwiązania?

Jak można wykorzystać te informacje w banku? (np. alerty dla managerów, automatyczne raporty)

🧠 Co to zadanie sprawdza:
Umiejętność analizy danych dialogowych (a nie tylko klasyfikacji tekstu)

Znajomość NLP i ML (klasyczne i/lub GenAI)

Krytyczne myślenie przy wyborze podejścia i metryk

Umiejętność syntetycznej prezentacji wyników

Zrozumienie potencjału biznesowego
