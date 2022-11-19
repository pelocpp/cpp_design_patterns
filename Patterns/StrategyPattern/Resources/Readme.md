# Strategy Design Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_strategy_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Je nach Bedarf einen bestimmten Algorithmus aus einer Familie von Algorithmen auswählen.&rdquo;

Das Strategie-Entwurfsmuster ist ein Entwurfsmuster,
in dem eine Reihe ähnlicher Algorithmen definiert und jeweils in eigenen Klassen eingekapselt und implementiert werden.
Der für einen bestimmten Zweck geeignete Algorithmus kann dann zur Laufzeit gemäß der vorliegenden Anforderungen ausgewählt
und eingesetzt werden.

#### Problem:

Dieses Entwurfsmuster empfiehlt sich für Situationen,
in denen sich Klassen nur im Verhalten (*Behavior*) unterscheiden.
In diesem Fall sind die Algorithmen in separate Klassen zu unterteilen,
die zur Laufzeit ausgewählt werden können.
Insbesondere kapselt das Entwurfsmuster die Algorithmen und macht sie austauschbar.

Diese Trennung ermöglicht, dass das Verhalten (Methode, Algorithmus) unabhängig von den Clients ist,
die es verwenden  und auf diese Weise variieren kann.
Eine Anwendung kann mit dem Fortschreiten der Anwendungsentwicklung
weitere, neue Algorithmen nahtlos hinzuzufügen.

#### Lösung:

Das &ldquo;Strategie Entwurfsmuster&rdquo; zählt zur Kategorie der &ldquo;Verhaltensmuster&rdquo; / &ldquo;Behavioral Pattern&rdquo;.
Es injiziert ein oder mehrere Verhaltensweisen in ein Objekt, die sich in ihrer Umgebung (&ldquo;*Object* / *Context*&rdquo;) austauschen lassen.

Das Strategie Pattern wird häufig eingesetzt, um das Verhalten einer Klasse zu ändern,
ohne dies über eine Spezialisierung vorzunehmen.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Strategy Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Client**: Diese Klasse verwendet austauschbare Algorithmen. Sie besitzt eine Referenz eines `StrategyBase`-Objekts.
  * **StrategyBase**: Definiert eine Schnittstelle, die allen unterstützten Algorithmen gemeinsam ist.
    Der Client verwendet diese Schnittstelle, um den über eine `ConcreteStrategy`-Schnittstelle definierten Algorithmus aufzurufen.
  * **ConcreteStrategy**: Konkrete Strategieklasse, die von der `StrategyBase`-Klasse erbt.
    Jede Instanz implementiert einen anderen Algorithmus, der (über die `ConcreteStrategy`-Schnittstelle)
    vom Client verwendet werden kann.

<img src="dp_strategy_pattern.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Strategy Patterns*.

## Anwendungen des Design Pattern in der STL:

  * `std::sort`: Im optionalen dritten Parameter kann ein *callable* übergeben werden, dass die Strategie des Sortierens implementiert.

## Hinweis:

Man kann in der Implementierung zwischen dynamischer und statischer Ausprägung unterscheiden.
Die statische Implementierung basiert in C++ auf der Verwendung von Schablonen (`template`),
die dynamische Implementierung auf dynamisch allokierten Strategy-Objekten (`new`),
die zur Laufzeit austauschbar sind.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### Statisches Strategy Design Pattern mit Template Klassen

[Quellcode &ldquo;Statische Shapes&rdquo;](../StaticStrategyExample.cpp)

Das *Decorator Design Pattern* konnte man sowohl dynamisch als auch statisch implementieren,
und dies kann man beim *Strategy Design Pattern* genauso umsetzen.

Im Prinzip  gibt es nichts Besonderes an dieser Umsetzung zu beobachten,
außer dass man den Algorithmus (hier: Methode `add_list_item`)
nicht über die *vtable* ansprechen (indirekter Methodenaufruf),
sondern als C++&ndash;Template-Parameter übergeben, was bedeutet,
dass der Algorithmus/die Strategie zur Laufzeit nicht änderbar ist.
Der Methodenaufruf selbst ist dann direkt, was eine verbesserte Laufzeit zur Folge hat!

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/strategy/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Strategy)

vor.


Das Beispiel zu der Auswahl der Bezahlungsmethode in einer E-Commerce App orierentiert sich an

[https://refactoring.guru/design-patterns/strategy](https://refactoring.guru/design-patterns/strategy/java/example)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
