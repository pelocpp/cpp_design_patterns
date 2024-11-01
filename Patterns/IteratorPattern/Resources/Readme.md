# Iterator Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_iterator_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Um das Durchlaufen (Traversieren) einer Datenstruktur zu erleichtern.&rdquo;

Das *Iterator Pattern* ist ein Entwurfsmuster,
das es erm�glicht, die Elemente eines Aggregatobjekts ohne Kenntnis seiner Struktur sequentiell
zu durchlaufen (zu *traversieren*).
Auf diese Weise wird das Traversieren von Listen, B�umen und anderen Containerstrukturen
in einer standardisierten Weise erm�glicht.

#### Problem:

Eine *Collection* ist eine der am h�ufigsten verwendeten Datenstrukturen in der Programmierung.
Eine *Collection* stellt einen *Container* f�r eine Gruppe von Objekten dar:

<img src="dp_collections_iterator.png" width="600">

*Abbildung* 1: Unterschiedliche Arten von *Collections*.

Die meisten Collections speichern ihre Elemente in einfachen linearen (verketteten) Listen ab.
Wiederum andere basieren auf komplexeren Datenstrukturen wie Stapeln (Stack), B�umen (Tree), Diagrammen oder anderen.
Unabh�ngig davon, wie eine Collection strukturiert ist,
sollte sie eine M�glichkeit bieten, ihre Elemente durchlaufen (traversieren) zu k�nnen,
so dass ein anderer Code diese Elemente verwenden kann.
Es versteht sich dabei von selbst, dass bei einem derartigen Durchlauf kein Element 
mehrfach oder �berhaupt nicht erfasst werden darf.

Dies mag nach einer einfachen Aufgabe klingen, wenn die Elemente beispielsweise in einem Array
oder einer listenartigen Struktur abgelegt sind.
Es werden einfach alle Elemente der Reihe nach (Index eines Arrays, *next*-Zeiger in einer Liste) erfasst.
In einer komplexen Datenstruktur wie beispielsweise einer Baumstruktur
ist dies nicht so einfach! Hier gibt es zum Beispiel 
den "*Depth-First Traversal*" oder "*Breadth-First Traversal*" Algorithmus,
die bzgl. der Reihenfolge des Durchlaufens der Baumstruktur sehr unterschiedlich funktionieren:

<img src="dp_collections_iterator_tree_structures.png" width="600">

*Abbildung* 2: Eine Collection kann auf verschiedene Arten durchlaufen werden: *Depth-First Traversal* (links) versus *Breadth-First Traversal* (rechts).

#### L�sung:

Die Kernidee des *Iterator Patterns* besteht darin,
die Art und Weise des Durchlaufens einer Collection in ein separates Objekt zu extrahieren, das als *Iterator* bezeichnet wird.

Alle Iteratoren m�ssen dieselbe Schnittstelle implementieren.
Dadurch ist ein Clientcode mit jedem Typ von Collection oder jedem Traversierungsalgorithmus kompatibel,
sofern ein *Iterator*-Objekt vorhanden ist.

M�chte man eine Collection auf eine bestimmte Art und Weise durchlaufen
(z.B. "*Depth-First Traversal*" oder "*Breadth-First Traversal*"),
implementiert man einfach eine neue Iteratorklasse.
So muss man weder �nderungen an der Collection noch am Client vornehmen.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Iterator Patterns*.
Es besteht im Wesentlichen aus f�nf Teilen:

  * **Client**: Fordert das *Iterator*-Objekt von einem aggregierten Objekt an und "konsumiert" es, wenn die Elemente durchlaufen werden sollen.
  * **AggregateBase**: Abstrakte Basisklasse (oder Schnittstelle) f�r alle konkreten Aggregate. Diese Klasse enth�lt eine Methode, die auf Anfrage ein Iterator-Objekt zur�ckgibt.
  * **ConcreteAggregate**: Repr�sentiert die konkrete Implementierung der `AggregateBase`-Schnittstelle. Hat Zugriff auf die Elemente, die mit dem Iterator durchlaufen werden sollen.
  * **IteratorBase**: Abstrakte Klasse (oder Schnittstelle) eines konkreten Iterators. Enth�lt Methoden (pr�ziser: die Signaturen von Methoden), mit denen die Elemente durchlaufen werden k�nnen.
  * **ConcreteIterator**: Konkrete Realisierung von `IteratorBase`.

<img src="dp_iterator_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Iterator Patterns*.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Standard Variante

[Quellcode 2](../ConceptualExample02.cpp) &ndash; C++ spezifische Variante

Die zweite Umsetzung des *Iterator Patterns* ber�cksichtigt, dass es in C++ f�r Container bereits vordefinierte Iteratoren gibt.
Dies kann man - wenn es sich bei der *ConcreteAggregate*-Klasse um einen STL-Standardcontainer handelt - ausnutzen.
Im zweiten Beispiel wird mittels

```cpp
using TIterator = typename std::vector<TElement>::iterator;
```

der Standard-Iterator des STL-Containers `std::vector<TElement>` verwendet.

Sollte die *ConcreteAggregate*-Klasse kein STL-Standardcontainer sein, und dies d�rfte in der Mehrzahl der zu betrachtenden 
Beispiele der Fall sein, dann muss containerspezifisch eine Realisierung der Iteratoren-Methoden
`reset`, `getCurrent` und `hasNext` erfolgen, siehe dazu folgende Definition der Basisklasse `IteratorBase`:

```cpp
template <typename T>
class IteratorBase
{
public:
    virtual ~IteratorBase() {}
    virtual void reset() = 0;
    virtual const T& getCurrent() const = 0;
    virtual bool hasNext() = 0;
};
```

#### Regelwerk f�r die Methoden `reset`, `getCurrent` und `hasNext`:

�hnlich wie f�r C++ Standard-Iteratoren gelten auch f�r die drei Methoden `reset`, `getCurrent` und `hasNext`
einige Regeln bzw. Konventionen:

  * Der Aufruf von `getCurrent` muss "gesch�tzt" sein:
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

    In diesem Fall liefert `getCurrent` immer dasselbe Objekt bzw. Element der Aufz�hlung zur�ck. 

  * `reset`-Methode

    Mit `reset` kann man eine aktive Traversierung / Iteration von Anfang an neu beginnen.

  * Aufruf einer `reset()`-Methode am Ende einer Iteration:

    Die Frage, die sich hier stellt, lautet: "Muss ich `reset` am Ende einer Iteration aufrufen,
    wenn ich mit demselben Iterator den Container  zum zweiten Mal durchlaufen m�chte?"
    Die Antwort lautet: Nein.

  * Prinzipieller Aufruf von `hasNext()`:

    Wie reagiert ein Aufruf von `hasNext()`, wenn der R�ckgabewert `false` ist?	
    Wenn ich genau dann `hasNext()` wieder aufrufe, sollte `hasNext()` `true` zur�ckliefern
    und damit eine zweite Iteration von Beginn an einleiten.

---

#### *Hinweis* 1: Mehrere Iterator-Objekte zu einem Container:

Nat�rlich ist es m�glich, von einem Container mehrere Iterator-Objekte zu erzeugen.
Wie immer Sie die Klasse `ConcreteIterator` realisieren: Wenn gleichzeitig mehrere Iterator-Objekte
einen Container traversieren, dann muss jeder Iterator f�r sich *autark* arbeiten.
 
---

#### *Hinweis* 2: �nderungen am Container w�hrend des Iterierens:

Prinzipiell sollte man erw�hnen, dass Sie bei der Realisierung eines Iterators zugrunde legen sollten,
dass w�hrend des Iterierens **keine** �nderungen am Container erfolgen d�rfen.

W�rden Sie das Ver�ndern des Containers hier zulassen, w�rde die Komplexit�t in der Realisierung eines korrekt funktionierenden
Iterators unverh�ltnism��ig stark ansteigen. Dies ist auch der Grund, warum Standard-Iteratoren in den Frameworks
J2SE und .NET in derartigen F�llen eine Ausnahme werfen
(Java: `ConcurrentModificationException`, C#: `System.InvalidOperationException`).

Eine einfache L�sung dieses Problems best�nde darin, die zu iterierenden Elemente vor dem Beginn des Traversierens 
einfach zu kopieren.
In der Regel d�rfte dies aus Gr�nden der Performance und des ben�tigten Arbeitsspeichers aber ausscheiden.
 
---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/iterator/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Iterator)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
