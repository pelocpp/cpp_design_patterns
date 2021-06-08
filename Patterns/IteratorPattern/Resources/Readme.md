# Iterator Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Iterator Pattern* ist ein Entwurfsmuster,
das es ermöglicht, die Elemente eines Aggregatobjekts ohne Kenntnis seiner Struktur sequentiell
zu durchlaufen (zu *traversieren*).
Auf diese Weise wird das Traversieren von Listen, Bäumen und anderen Containerstrukturen
in einer standardisierten Weise ermöglicht.

#### Problem:

Eine *Collection* ist eine der am häufigsten verwendeten Datenstrukturen in der Programmierung.
Eine *Collection* stellt einen *Container* für eine Gruppe von Objekten dar:

<img src="dp_collections_iterator.png" width="600">

*Abbildung* 1: Unterschiedliche Arten von *Collections*.

Die meisten Collections speichern ihre Elemente in einfachen linearen (verketteten) Listen ab.
Wiederum andere basieren auf komplexeren Datenstrukturen wie Stapeln (Stack), Bäumen (Tree), Diagrammen oder anderen.
Unabhängig davon, wie eine Collection strukturiert ist,
sollte sie eine Möglichkeit bieten, ihre Elemente durchlaufen (traversieren) zu können,
so dass ein anderer Code diese Elemente verwenden kann.
Es versteht sich dabei von selbst, dass bei einem derartigen Durchlauf kein Element 
mehrfach oder überhaupt nicht erfasst werden darf.

Dies mag nach einer einfachen Aufgabe klingen, wenn die Elemente beispielsweise in einem Array
oder einer listenartigen Struktur abgelegt sind.
Es werden einfach alle Elemente der Reihe nach (Index eines Arrays, *next*-Zeiger in einer Liste) erfasst.
In einer komplexen Datenstruktur wie beispielsweise einer Baumstruktur
ist dies nicht so einfach! Hier gibt es zum Beispiel 
den "*Depth-First Traversal*" oder "*Breadth-First Traversal*" Algorithmus,
die bzgl. der Reihenfolge des Durchlaufens der Baumstruktur sehr unterschiedlich funktionieren:

<img src="dp_collections_iterator_tree_structures.png" width="600">

*Abbildung* 2: Eine Collection kann auf verschiedene Arten durchlaufen werden: *Depth-First Traversal* (links) versus *Breadth-First Traversal* (rechts).

#### Lösung:

Die Kernidee des *Iterator Patterns* besteht darin,
die Art und Weise des Durchlaufens einer Collection in ein separates Objekt zu extrahieren, das als *Iterator* bezeichnet wird.

Alle Iteratoren müssen dieselbe Schnittstelle implementieren.
Dadurch ist ein Clientcode mit jedem Typ von Collection oder jedem Traversierungsalgorithmus kompatibel,
sofern ein *Iterator*-Objekt vorhanden ist.

Möchte man eine Collection auf eine bestimmte Art und Weise durchlaufen
(z.B. "*Depth-First Traversal*" oder "*Breadth-First Traversal*"),
implementiert man einfach eine neue Iteratorklasse.
So muss man weder Änderungen an der Collection noch am Client vornehmen.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Iterator Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Client**: Fordert das *Iterator*-Objekt von einem aggregierten Objekt an und "konsumiert" es, wenn die Elemente durchlaufen werden sollen.
  * **AggregateBase**: Abstrakte Basisklasse (oder Schnittstelle) für alle konkreten Aggregate. Diese Klasse enthält eine Methode, die auf Anfrage ein Iterator-Objekt zurückgibt.
  * **ConcreteAggregate**: Repräsentiert die konkrete Implementierung der `AggregateBase`-Schnittstelle. Hat Zugriff auf die Elemente, die mit dem Iterator durchlaufen werden sollen.
  * **IteratorBase**: Abstrakte Klasse (oder Schnittstelle) eines konkreten Iterators. Enthält Methoden (präziser: die Signaturen von Methoden), mit denen die Elemente durchlaufen werden können.
  * **ConcreteIterator**: Konkrete Realisierung von `IteratorBase`.

<img src="dp_iterator_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Iterator Patterns*.


#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Standard Variante

[Quellcode 2](../ConceptualExample02.cpp) &ndash; C++ spezifische Variante

Die zweite Umsetzung des *Iterator Patterns* berücksichtigt, dass es in C++ für Container bereits vordefinierte Iteratoren gibt.
Dies kann man - wenn es sich bei der *ConcreteAggregate*-Klasse um einen STL-Standardcontainer handelt - ausnutzen.
Im zweiten Beispiel wird mittels

```cpp
using TIterator = typename std::vector<TElement>::iterator;
```

der Standard-Iterator des STL-Containers `std::vector<TElement>` verwendet.

Sollte die *ConcreteAggregate*-Klasse kein STL-Standardcontainer sein, und dies dürfte in der Mehrzahl der zu betrachtenden 
Beispiele der Fall sein, dann muss containerspezifisch eine Realisierung der Iteratoren-Methoden
`reset`, `getCurrent` und `hasNext` erfolgen, siehe dazu folgende Definition der Basisklasse `IteratorBase`:

```cpp
template <typename T>
class IteratorBase
{
public:
    virtual ~IteratorBase() = default;
    virtual void reset() = 0;
    virtual const T& getCurrent() const = 0;
    virtual bool hasNext() = 0;
};
```

#### Regelwerk für die Methoden `reset`, `getCurrent` und `hasNext`:

Ähnlich wie für C++ Standard-Iteratoren gelten auch für die drei Methoden `reset`, `getCurrent` und `hasNext`
einige Regeln bzw. Konventionen:

  * Der Aufruf von `getCurrent` muss "geschützt" sein:
    ```cpp
    while (iter.hasNext()) { 
        elem = iter.getCurrent();
    }
    ```

  * Ein Aufruf von `getCurrent` ohne vorhergehenden Aufruf von `hasNext` bewirkt ein *"undefined behaviour"*:
    ```cpp
    // no preceding call of 'hasNext':
    elem = iter.getCurrent();  // "undefined behaviour", z.B. exception 
    ```

  * Wiederholter Aufruf von `getCurrent()` ohne `hasNext()`:

    In diesem Fall liefert `getCurrent` immer dasselbe Objekt bzw. Element der Aufzählung zurück. 

  * `reset`-Methode

    Mit `reset` kann man eine aktive Traversierung / Iteration von Anfang an neu beginnen.

  * Aufruf einer `reset()`-Methode am Ende einer Iteration:

    Die Frage, die sich hier stellt, lautet: "Muss ich `reset` am Ende einer Iteration aufrufen,
    wenn ich mit demselben Iterator den Container  zum zweiten Mal durchlaufen möchte?"
    Die Antwort lautet: Nein.

  * Prinzipieller Aufruf von `hasNext()`:

    Wie reagiert ein Aufruf von `hasNext()`, wenn der Rückgabewert `false` ist?	
    Wenn ich genau dann `hasNext()` wieder aufrufe, sollte `hasNext()` `true` zurückliefern
    und damit eine zweite Iteration von Beginn an einleiten.

---

#### *Hinweis* 1: Mehrere Iterator-Objekte zu einem Container:

Natürlich ist es möglich, von einem Container mehrere Iterator-Objekte zu erzeugen.
Wie immer Sie die Klasse `ConcreteIterator` realisieren: Wenn gleichzeitig mehrere Iterator-Objekte
einen Container traversieren, dann muss jeder Iterator für sich *autark* arbeiten.
 
---

#### *Hinweis* 2: Änderungen am Container während des Iterierens:

Prinzipiell sollte man erwähnen, dass Sie bei der Realisierung eines Iterators zugrunde legen sollten,
dass während des Iterierens **keine** Änderungen am Container erfolgen dürfen.

Würden Sie das Verändern des Containers hier zulassen, würde die Komplexität in der Realisierung eines korrekt funktionierenden
Iterators unverhältnismäßig stark ansteigen. Dies ist auch der Grund, warum Standard-Iteratoren in den Frameworks
J2SE und .NET in derartigen Fällen eine Ausnahme werfen
(Java: `ConcurrentModificationException`, C#: `System.InvalidOperationException`).

Eine einfache Lösung dieses Problems bestünde darin, die zu iterierenden Elemente vor dem Beginn des Traversierens 
einfach zu kopieren.
In der Regel dürfte dies aus Gründen der Performance und des benötigten Arbeitsspeichers aber ausscheiden.
 
---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/iterator/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Iterator)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
