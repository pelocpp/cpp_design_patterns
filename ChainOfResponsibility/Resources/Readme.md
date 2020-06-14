# Chain of Responsibility

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Chain of Responsibility Pattern* ist ein Entwurfsmuster,
das eine verkettete Liste von Methoden (*Handlern*) definiert,
von denen jede eine bestimmte Anforderung (Funktionalität) verarbeiten kann.
Wenn eine Anforderung an die Liste gesendet wird,
wird sie zunächst dem ersten Handler in der Liste übergeben.
Nun entscheidet jeder Handler für sich, die Anforderung entweder zu verarbeiten oder
diese an den nächsten Handler in der Liste weiterzuleiten.


#### Problem:


#### Lösung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Command Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Client**: Genereller Konsument der Klassen des Entwurfsmusters. Er erstellt das *Command Object* und verknüpft es mit *Receiver*-Objekten.
  * **Receiver**: Objekt, das weiß, wie das Kommando (Methode) auszuführen ist.
  * **CommandBase**: Abstrakte Klasse (oder Schnittstelle) für *Command*-Objekte. Enthält Informationen über das *Receiver*-Objekt,
    das für die Ausführung der Operation unter Verwendung der im *Command*-Objekt abgelegten Informationen verantwortlich ist.
  * **ConcreteCommand**: Konkrete Implementierung der abstrakten `CommandBase`-Klasse oder -Schnittstelle.
  * **Invoker**: Objekt, das entscheidet, wann das Kommando ausgeführt werden soll.


<img src="dp_command_pattern.png" width="700">

Abbildung 1: Schematische Darstellung des *Command Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/command/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

"Robot Movements"

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme.md)

---
