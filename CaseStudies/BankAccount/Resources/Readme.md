# Bankkonten eines Bankinstituts

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

#### Aufgabe

Schreiben Sie ein C++-Programm, das ein Konto eines Bankinstituts simuliert.
Es sollen Geldbeträge einbezahlt und abgehoben werden können.
Realisieren Sie zu diesem Zweck eine Klasse `BankAccount` mit den zwei Methoden `deposit` und `withdraw`.

Etwaige Unterdeckungen des Kontos sind hier nicht zu berücksichtigen.
Mit der Methode `getBalance` kann man einen Kontostand abfragen.

Da die einzelnen Konto-Transaktionen im Rechenzentrum des Bankinstituts
zu einem späteren Zeitpunkt ausgeführt werden sollen,
benötigen wir eine Möglichkeit, mit der sich entsprechende Aufträge an das Bankinstitut
zwischenspeichern und damit verzögert ausführen lassen.

Welches klassische Entwurfsmuster bietet sich zur Realisierung an?

Schreiben Sie eine Testfunktion, die ein entsprechendes Szenario verifiziert.

---

#### Lösung

[Siehe hier](Solution.md)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---
