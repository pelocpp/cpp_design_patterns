# Password-Generator

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall für das *Composite Pattern* Entwurfsmuster.

Dieses Entwurfsmuster setzt Objekte in Baumhierarchien zusammen und ermöglicht
auf diese Weise die Behandlung von Gruppen (oder Bäumen) von Objekten auf die gleiche Weise wie einzelne Objekte des gleichen Typs.
Das folgende Klassendiagramm
zeigt eine Hierarchie von Klassen, die zum Generieren von Passwörtern verwendet werden könnten:

<img src="dp_password_generator.svg" width="800">

Abbildung 1: Schematische Darstellung des *Composite* Patterns im Anwendungsfall *PasswortGenerator*.

`PasswordGenerator` ist die Basisklasse und verfügt über mehrere virtuelle Methoden:
`generate` gibt eine zufällig generierte Zeichenfolge zurück, `length` die Länge
der Zeichenfolge.
`allowedChars` gibt eine Zeichenfolge mit allen Zeichen zurück,
die zum Generieren verwendet werden dürfen. Also zum Beispiel `"0123456789"` im Falle
der Klasse `DigitGenerator`.
`BasicPasswordGenerator` wird von dieser Basisklasse abgeleitet
und definiert einen Generator mit einer Mindestlänge.
`DigitGenerator`, `SymbolGenerator`, `UpperLetterGenerator`
und `LowerLetterGenerator` werden von `BasicPasswordGenerator` abgeleitet und
überschreiben allesamt `allowedChars`, um die jeweiligen Teilmengen von Zeichen zu definieren,
die zum Generieren von zufälligen Texten verwendet werden dürfen.
Natürlich besitzen sie auch eine Methode `generate`, um an Hand dieser Vorgaben
ein Passwort zu generieren.

*Beispiel*:

```cpp
std::unique_ptr<PasswordGenerator> digiGen = std::make_unique<DigitGenerator>(4);
password = digiGen->generate(engine);
std::cout << "DigitGenerator:       " << password << std::endl;
```

Neben den einzelnen Spezialklassen für die Generierung eines Passworts
an Hand einer bestimmten Regel gibt es auch einen *zusammengesetzten* Generator:
Klasse `CompositePasswordGenerator`. Diese Klasse
repräsentiert gewissermaßen ein Kompositum von einer oder mehrerer
untergeordneter Spezialklassen.
`add` fügt einem zusammengesetzten Generator eine untergeordnete Komponente hinzu.
Die Klasse `CompositePasswordGenerator` besitzt ebenfalls eine Methode `generate`,
diese nimmt die Hilfe der unterlagerten Spezialklassen in Anspruch.

*Beispiel*:

```cpp
CompositePasswordGenerator compositeGenerator;
compositeGenerator.add(std::make_unique<UpperLetterGenerator>(8));
compositeGenerator.add(std::make_unique<LowerLetterGenerator>(8));
password = compositeGenerator.generate(engine);
std::cout << "CompositeGenerator:   " << password << std::endl;
```


#### Quellcode

[Siehe hier](../GeneratingPasswords.cpp)

---

[Zurück](Readme.md)

---
