# Iterator Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Iterator Pattern* ist ein Entwurfsmuster,
das es ermöglicht, die Elemente eines Aggregatobjekts ohne Kenntnis seiner Struktur sequentiell
zu durchlaufen (*traversieren*).
Auf diese Weise wird das Traversieren von Listen, Bäumen und anderen Containerstrukturen
in einer standardisierten Weise ermöglicht.

#### Problem:

*Collections* ist einer der am häufigsten verwendeten Datentypen in der Programmierung.
Eine *Collection* ist ein *Container* für eine Gruppe von Objekten:

<img src="dp_collections_iterator.png" width="600">

Abbildung 1: Unterschiedliche Arten von *Collections*.

Die meisten Collections speichern ihre Elemente in einfachen linearen (verketteten) Listen.
Einige von ihnen basieren jedoch auf Stapeln (Stack), Bäumen (Tree), Diagrammen und anderen komplexen Datenstrukturen.
Unabhängig davon, wie eine Collection strukturiert ist,
sollte sie eine Möglichkeit bieten, ihre Elemente durchlaufen (traversieren) zu können,
so dass ein anderer Code diese Elemente verwenden kann.
Es versteht sich von selbst, dass bei einem derartigen Durchlauf kein Element 
mehrfach oder überhaupt nicht erfasst werden darf.

Dies mag nach einer einfachen Aufgabe klingen, wenn die Elemene beispielsweise in einem Array
oder einer listenartigen Struktur abgekegt sind.
Es werden einfach alle Elemente der Reihe nach (Index eines Array, next-Zeiger in einer Liste) erfasst.
In einer komplexen Datenstruktur wie beispielsweise einer Baumstruktur
ist dies nicht so einfach! Hier gibt es zum Beispiel 
den "*Depth-First Traversal*" oder "*Breadth-First Traversal*" Algorithmus,
die prinzipiell bzgl. der Reihenfolge des Durchlaufen äußerst unterschiedlich funktionieren:

<img src="dp_collections_iterator_tree_structures.png" width="600">

Abbildung 2: Eine Collection kann auf verschiedene Arten durchlaufen werden.

#### Lösung:

Die Kernidee des *Iterator Patterns* besteht darin,
das Art und Weise des Durchlaufs einer Collection in ein separates Objekt zu extrahieren, das als *Iterator* bezeichnet wird.

Alle Iteratoren müssen dieselbe Schnittstelle implementieren.
Dadurch ist ein Clientcode mit jedem Typ von Collection oder jedeTraversierungsalgorithmus kompatibel,
sofern ein *Iterator*-Objekt vorhanden ist.

Möchte man eine Collection auf eine bestimmte Art und Weise durchlaufen
(z.B. "*Depth-First Traversal*" oder "*Breadth-First Traversal*" bei baumartigen Strukturen)
implementiert man einfach eine neue Iteratorklasse.
So muss man weder Änderungen an der Collection oder am Client vornehmen.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Chain of Responsibility Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Client**: Fordert das *Iterator*-Objekt von einem aggregierten Objekt an und "konsumiert" es, wenn die Elemente durchlaufen werden sollen.
  * **AggregateBase**: Abstrakte Basisklasse (oder Schnittstelle) für alle konkreten Aggregate. Diese Klasse enthält eine Methode, die auf Anfage ein Iterator-Objekt zurückgibt.
  * **ConcreteAggregate**: Repräsentiert die konkrete Implementierung der `AggregateBase`-Schnittstelle. Hat Zugriff auf die Elemente, die mit dem Iterator durchlaufen werden.
  * **IteratorBase**: Abstrakte Klasse (oder Schnittstelle) eines konkreten Iterators. Enthält Methoden (präziser: die Signaturen von Methoden), mit denen die Elemente durchlaufen können.
  * **ConcreteIterator**: Konkrete Realisierung von `IteratorBase`..

<img src="dp_iterator_pattern.png" width="700">

Abbildung 1: Schematische Darstellung des *Iterator Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/iterator/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Iterator)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

"FiftyPenceHandler"

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme.md)

---
