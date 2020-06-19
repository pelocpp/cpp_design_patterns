# Proxy Pattern

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Proxy Pattern* ist ein strukturelles Entwurfsmuster,
das für ein anderes Objekt (Ressource) einen Art Ersatz oder Platzhalter bereitstellt.
Ein Proxy-Objekt kann zum Beispiel dann verwendet werden,
wenn aus bestimmten Gründen nicht direkt auf die Ressource zugegriffen werden kann
oder wenn nicht alle Methoden des ursprünglichen Objekt offen gelegt werden sollen.
Es ist auch denkbar, dass ein Proxy-Objekt dem ursprünglichen Objekt
zusätzliche Funktionen hinzufügt.
Die Verwendung von Proxys ist hilfreich, wenn die Ressource schwer zu instanziieren
oder sehr ressourcensensitiv ist (Beispiel: XML-Parser)


#### Problem:


<img src="dp_collections_iterator_tree_structures.png" width="600">

Abbildung 2: Eine Collection kann auf verschiedene Arten durchlaufen werden.

#### Lösung:

Die Kernidee des *Iterator Patterns* besteht darin,
die Art und Weise des Durchlaufs einer Collection in ein separates Objekt zu extrahieren, das als *Iterator* bezeichnet wird.

Alle Iteratoren müssen dieselbe Schnittstelle implementieren.
Dadurch ist ein Clientcode mit jedem Typ von Collection oder jedem Traversierungsalgorithmus kompatibel,
sofern ein *Iterator*-Objekt vorhanden ist.

Möchte man eine Collection auf eine bestimmte Art und Weise durchlaufen
(z.B. "*Depth-First Traversal*" oder "*Breadth-First Traversal*"),
implementiert man einfach eine neue Iteratorklasse.
So muss man weder Änderungen an der Collection oder am Client vornehmen.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Iterator Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Client**: Fordert das *Iterator*-Objekt von einem aggregierten Objekt an und "konsumiert" es, wenn die Elemente durchlaufen werden sollen.
  * **AggregateBase**: Abstrakte Basisklasse (oder Schnittstelle) für alle konkreten Aggregate. Diese Klasse enthält eine Methode, die auf Anfage ein Iterator-Objekt zurückgibt.
  * **ConcreteAggregate**: Repräsentiert die konkrete Implementierung der `AggregateBase`-Schnittstelle. Hat Zugriff auf die Elemente, die mit dem Iterator durchlaufen werden sollen.
  * **IteratorBase**: Abstrakte Klasse (oder Schnittstelle) eines konkreten Iterators. Enthält Methoden (präziser: die Signaturen von Methoden), mit denen die Elemente durchlaufen werden können.
  * **ConcreteIterator**: Konkrete Realisierung von `IteratorBase`.

<img src="dp_iterator_pattern.png" width="700">

Abbildung 1: Schematische Darstellung des *Iterator Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/iterator/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Proxy)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

Beispiel aus

https://refactoring.guru/design-patterns/iterator/cpp/example#example-0

Ist bei Conceptual 2 einzufügen !!!


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme.md)

---
