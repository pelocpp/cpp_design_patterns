# Interpreter Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_interpreter_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

> &bdquo;Das Interpreter Pattern definiert für eine einfache Grammatik eine Klassenhierarchie, mit der sich Sätze dieser Sprache als Objektbaum darstellen und durch rekursives Auswerten dieses Baums interpretieren lassen.&rdquo;

Das *Interpreter Pattern* gehört zur Kategorie der Verhaltensmuster und wird eingesetzt,
wenn ein bestimmtes Problem häufig in einer klar abgegrenzten, meist einfachen Sprache formuliert werden kann.
Für diese Sprache definiert man eine Grammatik, wobei jede Regel der Grammatik durch eine eigene Klasse repräsentiert wird.
Ein konkreter Satz dieser Sprache wird dann nicht als Text, sondern als Baum von Objekten dieser Klassen abgebildet &ndash; man spricht
auch von einem abstrakten Syntaxbaum.

Jede Klasse implementiert eine gemeinsame Schnittstelle mit einer `interpret()`-Methode, die weiß, wie ihr jeweiliger Grammatikteil auszuwerten ist.
Terminale Ausdrücke (z. B. einzelne Zahlen oder Variablen) bilden dabei die Blätter des Baums,
während nicht-terminale Ausdrücke (z. B. Addition oder Konjunktion) innere Knoten sind,
die ihre Kindknoten rekursiv auswerten und die Teilergebnisse kombinieren.

Die eigentliche Auswertung eines Satzes erfolgt somit durch einen rekursiven Aufruf von `interpret()` über den gesamten Baum,
beginnend an der Wurzel.
Der Vorteil dieses Ansatzes liegt in seiner Erweiterbarkeit:
Neue Grammatikregeln lassen sich durch neue Klassen ergänzen, ohne bestehenden Code ändern zu müssen.

Allerdings eignet sich das Pattern nur für vergleichsweise einfache Sprachen, da die Klassenanzahl
mit der Komplexität der Grammatik schnell wächst und für aufwendigere Sprachen eher klassische Parser-Generatoren zum Einsatz kommen.

Typische Einsatzgebiete sind einfache Ausdrucksauswerter, Konfigurationssprachen, Suchfilter oder Regelwerke.


---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
