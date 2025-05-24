# Strategy Design Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_strategy_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Je nach Bedarf einen bestimmten Algorithmus aus einer Familie von Algorithmen ausw�hlen.&rdquo;

Das Strategie-Entwurfsmuster ist ein Entwurfsmuster,
in dem eine Reihe �hnlicher Algorithmen definiert und jeweils in eigenen Klassen eingekapselt und implementiert werden.
Der f�r einen bestimmten Zweck geeignete Algorithmus kann dann zur Laufzeit gem�� der vorliegenden Anforderungen ausgew�hlt
und eingesetzt werden.

#### Problem:

Dieses Entwurfsmuster empfiehlt sich f�r Situationen,
in denen sich Klassen nur im Verhalten (*Behavior*) unterscheiden.
In diesem Fall sind die Algorithmen in separate Klassen zu unterteilen,
die zur Laufzeit ausgew�hlt werden k�nnen.
Insbesondere kapselt das Entwurfsmuster die Algorithmen und macht sie austauschbar.

Diese Trennung erm�glicht, dass das Verhalten (Methode, Algorithmus) unabh�ngig von den Clients ist,
die es verwenden  und auf diese Weise variieren kann.
Eine Anwendung kann mit dem Fortschreiten der Anwendungsentwicklung
weitere, neue Algorithmen nahtlos hinzuzuf�gen.

#### L�sung:

Das &bdquo;Strategie Entwurfsmuster&rdquo; z�hlt zur Kategorie der &bdquo;Verhaltensmuster&rdquo; / &bdquo;Behavioral Pattern&rdquo;.
Es injiziert ein oder mehrere Verhaltensweisen in ein Objekt, die sich in ihrer Umgebung (&bdquo;*Object* / *Context*&rdquo;) austauschen lassen.

Das Strategie Pattern wird h�ufig eingesetzt, um das Verhalten einer Klasse zu �ndern,
ohne dies �ber eine Spezialisierung vorzunehmen.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Strategy Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Client**: Diese Klasse verwendet austauschbare Algorithmen. Sie besitzt eine Referenz eines `StrategyBase`-Objekts.
  * **StrategyBase**: Definiert eine Schnittstelle, die allen unterst�tzten Algorithmen gemeinsam ist.
    Der Client verwendet diese Schnittstelle, um den �ber eine `ConcreteStrategy`-Schnittstelle definierten Algorithmus aufzurufen.
  * **ConcreteStrategy**: Konkrete Strategieklasse, die von der `StrategyBase`-Klasse erbt.
    Jede Instanz implementiert einen anderen Algorithmus, der (�ber die `StrategyBase`-Schnittstelle)
    vom Client verwendet werden kann.

<img src="dp_strategy_pattern.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Strategy Patterns*.

## Umsetzung des Patterns in einer Klassenhierarchie

Wir betrachten die Anwendung des Strategy Design Patterns in einer Hiearchie von Klassen.

In *Abbildung* 2 kann man zwei Hierarchien erkennen:

  * Eine Hierarchie von anwendungsorientierten Klassen. Hier werden in einer Vaterklasse zentrale Methoden
  virtuell definiert (z.B. Methode `draw`), diese sind in den Kindklassen geeignet zu �berschreiben.

  * Die �berschriebenen Methoden k�nnten eine Realisierung umsetzen, wollen dies aber vermeiden,
  um f�r unterschiedliche Technologien (Strategien) anpassbar zu sein. Dazu ben�tigt man eine zweite Hierarchie von Klassen,
  die unterschiedliche Implementierungen bereitstellen.


<img src="dp_strategy_pattern_shapes.svg" width="700">

*Abbildung* 2: Anwendung des Strategy Design Patterns in einer Klassenhierarchie.


## Umsetzung des Strategy Design Patterns in Modern C++

In einer Umsetzung des Strategy Design Patterns mit Modern C++ Sprachmitteln
kommt das Klassentemplate `std::function` zum Einsatz.
`std::function` ist ein universeller polymorpher Funktionswrapper, der zum Beispiel Lambda Objekte, freie Funktionen
und andere aufrufbare Objekte kapseln kann.

Mit Hilfe von `std::function` fallen in dieser Variante alle Klassen weg, die mit Strategien zu tun haben.

<img src="dp_strategy_pattern_shapes_modern.svg" width="700">

*Abbildung* 3: Umsetzung des Strategy Design Patterns in Modern C++ mit `std::function`.


## Einsatz des Strategy Design Pattern in der STL

  * `std::sort`: Im optionalen dritten Parameter kann ein *Callable* �bergeben werden, dass die Strategie des Sortierens implementiert.

## Hinweis:

Man kann in der Implementierung zwischen dynamischer und statischer Auspr�gung unterscheiden.
Die statische Implementierung basiert in C++ auf der Verwendung von Schablonen (`template`),
die dynamische Implementierung auf dynamisch allokierten Strategy-Objekten (`new`),
die zur Laufzeit austauschbar sind.

---

&bdquo;Real-World&rdquo; Beispiel

Im Verzeichnis *ECommerceApp* ist ein Beispiel gezeigt, dass Bezahlvorg�nge in einer ECommerce-Anwendung auf Strategien umsetzt.

---

## Statisches Strategy Design Pattern mit Template Klassen

[Quellcode &bdquo;Statische Shapes&rdquo;](../StaticStrategyExample.cpp)

Das *Decorator Design Pattern* konnte man sowohl dynamisch als auch statisch implementieren,
und dies kann man beim *Strategy Design Pattern* genauso umsetzen.

Im Prinzip  gibt es nichts Besonderes an dieser Umsetzung zu beobachten,
au�er dass man den Algorithmus (hier im Beispiel: Methode `add_list_item`)
nicht �ber die *vtable* anspricht (indirekter Methodenaufruf),
sondern als C++&ndash;Template-Parameter �bergibt.
Dies bedeutet,
dass der Algorithmus/die Strategie zur Laufzeit nicht �nderbar ist.
Der Methodenaufruf selbst erfolgt dann direkt, was eine verbesserte Laufzeit zur Folge hat!

[Quellcode](../StaticStrategyExample.cpp) &ndash; Statische Umsetzung des Strategy Design Patterns (Templates)

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample.cpp) &ndash; Einfaches konzeptionelles Beispiel<br />
[Quellcode 2](../ConceptualExampleModern.cpp) &ndash; Einfaches konzeptionelles Beispiel mit `std::function`<br />
[Quellcode 3](../RealWorldExample.cpp) &ndash; Einfaches konzeptionelles Beispiel mit einer Hierarchie von Klassen<br />
[Quellcode 4](../RealWorldExampleModern.cpp) &ndash; Einfaches konzeptionelles Beispiel mit einer Hierarchie von Klassen und `std::function`<br />

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/strategy/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Strategy)

vor.


Das Beispiel zu der Auswahl der Bezahlungsmethode in einer E-Commerce App orierentiert sich an

[https://refactoring.guru/design-patterns/strategy](https://refactoring.guru/design-patterns/strategy/java/example)


Ein weiteres interessantes Beispiel zum Strategy Pattern widmet sich der Suche nach Knoten in einem gerichteten Graphen.
Die Art der Suche (Depth First Search / DFS, Breadth First Search / BFS)
wird als [Strategie](https://medium.com/@sabergholami72/strategy-design-pattern-when-and-how-to-use-it-60d5983f8ce2) realisiert.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
