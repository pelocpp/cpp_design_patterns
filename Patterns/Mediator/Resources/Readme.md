# Mediator Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_mediator_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Mediator Pattern* ist ein Verhaltensentwurfsmuster, das die lose Kopplung von Objekten propagiert,
indem Klassen nicht mehr direkt miteinander kommunizieren.
Stattdessen werden Mediatorobjekte verwendet, um die Interaktionen zwischen Klassen zu kapseln
und zu zentralisieren.

#### Problem:

Nicht selten bestehen Programme &ndash; zumindest in Teilen &ndash; aus umfangreichen Klassen.
Dies ist nicht ungewöhnlich, aber es kommt zu Problemen, wenn diese Klassen miteinander kommunizieren müssen.
Bei Verwendung des traditionellen Ansatzes, wenn Klassen direkt kommunizieren,
müssen diese Klassen ihre internen Implementierungen kennen bzw. im Zuge der Kommunikation offenlegen.

Dies führt zu der bekannten Beobachtung, da es zunehmend schwieriger wird, die Implementierung einer Klasse zu lesen und zu verstehen,
wenn das Programm immer komplexer wird. Derartige Klassen sind eng miteinander verbunden,
was aus konzeptioneller Sicht nicht gut ist.

#### Lösung:

Das *Mediator Pattern* löst dieses Problem, in diesem Muster ist die Kommunikation zwischen Objekten in einem Mediatorobjekt gekapselt.
Anstatt dass Klassen direkt kommunizieren, senden Klassen Nachrichten an den Mediator und der Mediator sendet
diese Nachrichten an die anderen Klassen weiter.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Mediator Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **ColleagueBase**: Abstrakte Klasse (oder Schnittstelle) für alle konkreten Komponenten, auch im Jargon dieses Musters als "*Kollegen*" bezeichnet.
   *Kollegen* sind Klassen, die Geschäftslogik enthalten. Jede Komponente hat einen geschützten (`protected`) Verweis auf einen Mediator,
   der mit dem Typ der Mediatorschnittstelle deklariert ist (`MediatorBase`).
   Der *Kollege* kennt folglich die tatsächliche Klasse des Mediators nicht.
   Sie können die Komponente (Kollege) daher in anderen Programmen wiederverwenden,
   indem Sie sie mit einem anderen Mediator verknüpfen.
  * **ConcreteColleague**: Eine Implementierung der `ColleagueBase`-Klasse. Konkrete Kollegen sind Klassen,
   die miteinander kommunizieren. *Kollegen*
   sollten keine anderen Komponenten kennen. Wenn innerhalb oder mit einer Komponente etwas Wichtiges passiert,
   muss diese nur den Mediator benachrichtigen.
   Wenn der Mediator die Benachrichtigung erhält, kann er den Absender leicht identifizieren, 
   was ausreichend sein sollte,
   um zu entscheiden, welche Komponente(n) im Gegenzug zu aktivieren ist (sind) &ndash; Aufruf einer Methode.
  * **MediatorBase**: Abstrakte Klasse (Schnittstelle) für das `Mediator`-Objekt.
   Diese Klasse enthält Methoden, die von Kollegen verwendet werden können.
   Die Mediator-Schnittstelle deklariert Kommunikationsmethoden für Komponenten,
   in der Regel sind dies nur wenige Benachrichtigungsmethoden.
   Komponenten können jeden Kontext als Argument dieser Methode übergeben,
   einschließlich eines Verweises auf sich selbst (`this`),
   jedoch ist dabei zu beachten, dass keine Kopplung zwischen einer empfangenden Komponente und der Klasse des Absenders entsteht.
  * **ConcreateMediator**: Implementierung der Methoden der `MediatorBase`-Klasse.
   Diese Klasse enthält Verweise auf alle Kollegen, die miteinander kommunizieren wollen.
   Konkrete Mediatoren kapseln die Beziehungen zwischen verschiedenen Kollegen.

<img src="dp_mediator_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Mediator Patterns*.

---

#### Conceptual Example:

*Hinweis*:

Das *Conceptual Example* liegt in drei Varianten vor:

  * Variante 1: klassisch &ndash; d.h. mit "raw"-Zeigern.
  * Variante 2: Wie Variante 1, aber mit `std::shared_ptr` Objekten und `std::enable_shared_from_this<>` Mechanismus.
  * Variante 3: Prinzipiell wie Variante 2, nur: Die Entscheidung, welche empfangende Komponente
    aufzurufen ist, wird dieses Mal über das Absenderobjekt getroffen (und nicht über eine Parameterkennung).

[Quellcode 1](../ConceptualExample01.cpp)

[Quellcode 2](../ConceptualExample02.cpp)

[Quellcode 3](../ConceptualExample03.cpp)

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/mediator/cpp/example#lang-features)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Mediator)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
