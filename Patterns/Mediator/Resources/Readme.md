# Mediator Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Mediator Pattern* ist ein Verhaltensentwurfsmuster, das die lose Kopplung von Objekten propagiert,
indem Klassen nicht mehr direkt miteinander kommunizieren müssen.
Stattdessen werden Mediatorobjekte verwendet, um die Interaktionen zwischen Klassen zu kapseln
und zu zentralisieren.

#### Problem:

Nicht selten bestehen Programme - zumindest in Teilen - aus umfangreichen Klassen.
Dies ist nicht ungewöhnlich, aber es kommt zu Problemen, wenn diese Klassen miteinander kommunizieren müssen.
Bei Verwendung des traditionellen Ansatzes, wenn Klassen direkt kommunizieren,
müssen diese Klassen ihre internen Implementierungen kennen bzw. im Zuge der Kommunikation offenlegen.

Dies führt zu der bekannten Beobachtung, da es zunehmend schwieriger, die Implementierung einer Klasse zu lesen und zu verstehen,
wenn das Programm immer komplexer wird. Derartige Klassen sind eng miteinander verbunden,
was aus konzeptioneller Sicht nicht gut ist.

#### Lösung:

Das *Mediator Pattern* löst dieses Problem. In diesem Muster ist die Kommunikation zwischen Objekten in einem Mediatorobjekt gekapselt.
Anstatt dass Klassen direkt kommunizieren, senden Klassen Nachrichten an den Mediator und der Mediator sendet
diese Nachrichten an die anderen Klassen.

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
   muss dieser nur den Mediator benachrichtigen.
   Wenn der Mediator die Benachrichtigung erhält, kann er den Absender leicht identifizieren, was möglicherweise gerade ausreicht,
   um zu entscheiden, welche Komponente im Gegenzug aktiviert werden soll (Aufruf einer Methode).
  * **MediatorBase**: Abstrakte Klasse (Schnittstelle) für das `Mediator`-Objekt.
   Diese Klasse enthält Methoden, die von Kollegen verwendet werden können.
   Die Mediator-Schnittstelle deklariert Kommunikationsmethoden mit Komponenten,
   die normalerweise nur eine einzige Benachrichtigungsmethode enthalten.
   Komponenten können jeden Kontext als Argumente dieser Methode übergeben, einschließlich ihrer eigenen Objekte,
   jedoch nur so, dass keine Kopplung zwischen einer empfangenden Komponente und der Klasse des Absenders auftritt.
  * **ConcreateMediator**: Implementierung der Methoden der `MediatorBase`-Klasse.
   Diese Klasse enthält Verweise auf alle Kollegen, die miteinander kommunizieren müssen.
   Konkrete Mediatoren kapseln die Beziehungen zwischen verschiedenen Kollegen.

<img src="dp_mediator_pattern.svg" width="700">

Abbildung 1: Schematische Darstellung des *Mediator Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/mediator/cpp/example#lang-features)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Mediator)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
