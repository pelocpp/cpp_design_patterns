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

http://www.vishalchovatiya.com/double-dispatch-in-cpp/#:~:text=Double%20Dispatch%20in%20C%2B%2B%20is,tables%20of%20respective%20two%20objects.



#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Visitor Patterns*.
Es besteht im Wesentlichen aus sechs Teilen:

  * **Client**: Anwender des *Visitor Patterns*. Er verwaltet die Objektstruktur und weist die Objekte innerhalb der Struktur an,
    wann ein Besucher akzeptiert werden soll.
  * **ObjectStructure**: Dies ist eine Klasse, die alle Objekte enthält, die besucht werden können.
    Es bietet einen Mechanismus zum Traversieren aller Elemente.
    Diese Struktur muss nicht zwingend eine *Collection* sein, es kann irgend eine komplexe Struktur sein, beispielsweise ein *Composite Object*.
  * **ElementBase**: Stellt eine Abstraktionsschnittstelle dar, die die `accept`-Operation deklariert. Dies ist der Einstiegspunkt, an dem ein Objekt vom Besucherobjekt "besucht" werden kann.
    Jedes Objekt aus einer *Collection* sollte diese Abstraktionsschnittstelle implementieren, um besucht werden zu können.
  * **ConcreteElement**: Diese Klassen erben von der abstrakten Basisklasse `ElementBase` oder implementieren eine Schnittstelle
    und definieren eine `accept`-Operation. Das *Visitor*-Objekt wird durch die `accept`-Operation an dieses Objekt übergeben.
  * **VisitorBase**: Deklariert eine `visit`-Methode (Operation) für jede Klasse von `ConcreteElement` in der Objektstruktur.
    Der Name und die Signatur der Operation identifizieren die Klasse, die die Anforderung an den Visitor sendet.
    Auf diese Weise kann der Besucher die konkrete Klasse des besuchten Elements bestimmen.
    So kann der Besucher direkt über diese spezielle Schnittstelle auf die fraglichen Elemente zugreifen.
  * **ConcreteVisitor**: Implementiert jede von einem Visitor deklarierte Operation (Methode).
    Jede Operation implementiert ein Fragment eines Algorithmus, der für die entsprechende Klasse oder das entsprechende Objekt in der Objektstruktur definiert ist.
    `ConcreteVisitor` stellt den Kontext für den Algorithmus bereit und speichert seinen lokalen Status.
    Dieser Zustand sammelt häufig Ergebnisse während des Durchlaufens der Struktur.

<img src="dp_visitor_pattern.svg" width="600">

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

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
