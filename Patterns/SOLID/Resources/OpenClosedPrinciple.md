# Open-Closed-Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

&ldquo;Klassen sollten für Erweiterungen offen, für Änderungen geschlossen sein&rdquo;

In anderen Worten:
Das Prinzip bedeutet wörtlich genommen, dass man in der Lage sein sollte,
das Verhalten einer Klasse zu erweitern, ohne diese dabei zu ändern.

Auf den ersten Blick mag das *Open-Closed-Prinzip* etwas seltsam erscheinen und die Frage aufwerfen,
wie man das Verhalten einer Klasse ändern können soll, ohne diese zu ändern?

Es gibt darauf Antworten im objektorientierten Design wie

  * dynamischer Polymorphismus,
  * statischer Polymorphismus und
  * C++-Templates

nur um einige Möglichkeiten aufzuzählen. 

Wir betrachten das *Open-Closed-Prinzip* an einem Beispiel:

#### Example: Violating the Open Closed Principle

```cpp
```

  * Wir betrachten eine Reihe von Produkten (Klasse `Product`) und filtern diese
    nach einigen ihrer Attribute. An dem Beispielcode ist nichts auszusetzen,
    solange sich die Anforderungen nicht mehr ändern &ndash; was beim Software-Engineering niemals der Fall ist :).

  * Wir stellen uns nun der Situation, dass nachträglich
    Anforderungsänderungen und einige neue Filter-Operationen verlangt werden.
    In diesem Fall sind die Klassen `Product` und `ProductFilter` erneut zu ändern
    und neue Filtermethoden hinzufügen.

  * Dieser Ansatz ist problematisch, da wir zwei Attribute (`Color` und `Size`) 
    und drei Funktionen (`Color`, `Size` und ihre Kombination) haben.
    Ein weiteres Attribut hätte zur Folge, dass acht neue Funktionen zu implementieren sind.
    Dieser Ansatz ist nicht nur nicht zielführend,
    der bereits existierende, realisierte Quellcode ist zu modifizieren.
    Dies ist eine Verletzung des *Open-Closed-Prinzips*:
    Es besagt, dass das System für Erweiterungen offen, aber für Modifikationen geschlossen zu sein hat.
    Im vorliegenden Beispiel ändern wir den vorhandenen Code, was eine Verletzung von OCP darstellt.


#### Example: Respecting the Open Closed Principle


Es gibt mehr als einen Weg, um das *Open-Closed-Prinzip* zu erreichen.
Das Design von Schnittstellen und das Hinzufügen einer Abstraktionsebene für Erweiterbarkeit
sind die am meisten verbreitete Vorgehensweise:

```cpp
```

###### Beachten Sie an dem Quellcode:
Die Filtermethode `filter` der Klasse `ProductFilter` ist nicht zu ändern.
Sie kann jetzt mit allen Arten von Spezifikationen arbeiten!

#### Vorteile des *Open-Closed-Prinzips*

  * Expressiveness &ndash; Ausdruckskraft
  * Maintainability &ndash; Wartbarkeit
  * Flexibility &ndash; Flexibilität

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
