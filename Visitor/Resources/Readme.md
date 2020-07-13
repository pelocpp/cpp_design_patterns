# Visitor Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Visitor Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
das eine Menge strukturierter Daten von den Funktionen trennt,
die auf ihr ausgeführt werden können. Dies unterstützt zum einen eine lose Kopplung
und es ermöglicht zum anderen das Hinzufügen zusätzlicher Operationen, ohne an den Datenklassen Änderungen vornehmen zu müssen.

#### Problem:

Das Ergebnis der Trennung von Objektstruktur und Funktionen (Algorithmen) ist ein Datenmodell
mit eingeschränkter Funktionalität und einer Gruppe von "*Besuchern*",
die Operationen auf den Daten ausführen.
Ein weiterer Vorteil ist die Möglichkeit, einen neuen *Besuchern* hinzufügen zu können,
ohne dabei die vorhandene Struktur ändern zu müssen. 
Die Klassen Daten sind mit Attributen (Eigenschaften, *getter*/*setter*-Methoden) so zu erstellen,
dass diese vom "Besucher"-Objekt geeignet verwendet werden können.
Typischerweise wird das Datenobjekt als Parameter an eine Methode des "Besucher"-Objekts übergeben
(die Konvention besteht darin, diese Methode `visit` zu nennen).

#### Lösung:

TO BE DONE:

https://refactoring.guru/design-patterns/visitor-double-dispatch




#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Visitor Patterns*.
Es besteht im Wesentlichen aus sechs Teilen:

  * **Client**: XXX
  * **ObjectStructure**: XXX
  * **ElementBase**: XXX
  * **ConcreteElement**: XXX
  * **VisitorBase**: XXX
  * **ConcreteVisitor**: XXX

<img src="dp_xxx.png" width="500">

Abbildung 1: Schematische Darstellung des *Visitor Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/command/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Visitor)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:



"PersonCaretaker"

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme_05_Catalog.md)

---
