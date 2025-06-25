# Prompt do analizy rozmów sprzedażowych

## Instrukcja główna

Przeanalizuj dołączoną transkrypcję rozmowy sprzedażowej produktu inwestycyjnego pod kątem naruszeń misselling i misconduct. Zwróć wynik w formacie JSON.

## Definicje naruszeń

### Misselling:
- Nieprawdziwe lub mylące informacje o produkcie
- Zatajanie istotnych ryzyk lub kosztów
- Sprzedaż produktu nieadekwatnego do profilu klienta
- Obietnice gwarantowanych zysków bez wspomnienia o ryzyku
- Ukrywanie opłat, prowizji lub innych kosztów
- Niewłaściwe przedstawienie poziomu ryzyka

### Misconduct:
- Agresywne techniki sprzedażowe lub wywieranie presji
- Ignorowanie sprzeciwu klienta lub jego wątpliwości
- Manipulowanie emocjami klienta
- Nierespektowanie czasu na przemyślenie decyzji
- Używanie technik wprowadzających w błąd
- Naruszenie zasad etyki zawodowej

## Format odpowiedzi

### Jeśli nie wykryto naruszeń:
```json
{
  "misselling": false,
  "misconduct": false
}
```

### Jeśli wykryto naruszenia:
```json
{
  "misselling": true/false,
  "misconduct": true/false,
  "details": {
    "misselling_evidence": {
      "quote": "dokładne zdanie z transkrypcji",
      "justification": "uzasadnienie dlaczego to naruszenie",
      "confidence": "wysoka/średnia/niska"
    },
    "misconduct_evidence": {
      "quote": "dokładne zdanie z transkrypcji", 
      "justification": "uzasadnienie dlaczego to naruszenie",
      "confidence": "wysoka/średnia/niska"
    }
  }
}
```

## Zasady analizy

1. **Precyzja**: Cytuj dokładnie fragmenty z transkrypcji
2. **Pewność**: Oceń poziom pewności swojej analizy (wysoka/średnia/niska)
3. **Kontekst**: Uwzględniaj pełny kontekst rozmowy, nie wyrywaj zdań
4. **Ostrożność**: W przypadku wątpliwości wybierz niższą ocenę pewności

## Przykłady zastosowania

**Przykład 1 - Misselling:**
```json
{
  "misselling": true,
  "misconduct": false,
  "details": {
    "misselling_evidence": {
      "quote": "Ten produkt gwarantuje 15% zysku rocznie bez żadnego ryzyka",
      "justification": "Obietnica gwarantowanego zysku bez wspomnienia o ryzyku - klasyczne misselling",
      "confidence": "wysoka"
    }
  }
}
```

**Przykład 2 - Misconduct:**
```json
{
  "misselling": false,
  "misconduct": true,
  "details": {
    "misconduct_evidence": {
      "quote": "Jeśli pan teraz nie podpisze, to jutro już tej oferty nie będzie",
      "justification": "Wywieranie presji czasowej i manipulowanie strachem klienta",
      "confidence": "wysoka"
    }
  }
}
```

---

**TRANSKRYPCJA DO ANALIZY:**
[Tu wklej transkrypcję rozmowy]