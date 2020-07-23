# Command Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Command Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
das eine Anforderung (einen *Request*, einen *Befehl*) in ein eigenständiges Objekt umwandelt,
das alle Informationen über das Kommando enthält.
Der Befehl kann dann nach Bedarf aufgerufen werden, häufig als Teil einer Reihe von Befehlen,
die in einer Warteschlange (*Queue*) abgelegt sind.
Die Befehle in der Warteschlange können auf diese Weise sequentiell abgearbeitet werden,
denkbar sind auch *Rollback*- bzw. *Undo*-Funktionalitäten.

#### Problem:

Das *Command Pattern* ist ein Entwurfsmuster, bei dem alle zur Ausführung einer Methode erforderlichen Informationen
in einem Objekt gekapselt sind, das sofort verwendet oder zum späteren Gebrauch aufbewahrt werden kann.
Dieses Objekt führt nichts aus, es enthält nur Informationen.

Es gibt drei Schlüsselbegriffe, die im Umfeld dieses Patterns zu definieren sind: *Client*, *Invoker* und *Receiver*.
Der *Client* erstellt das Befehlsobjekt ("*Command Object*").
Das *Invoker*-Objekt entscheidet, wann die Methode, deren Informationen (*Parameter*) im *Command Object* abgelegt sind, aufgerufen werden soll.
Das *Receiver*-Objekt ist eine Instanz einer Klasse, die den eigentlichen Code der auszuführenden Methode enthält.

#### Lösung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Command Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Client**: Genereller Konsument der Klassen des Entwurfsmusters. Er erstellt das *Command Object* und verknüpft es mit *Receiver*-Objekten.
  * **Receiver**: Objekt, das weiß, wie das Kommando (Methode) auszuführen ist.
  * **CommandBase**: Abstrakte Klasse (oder Schnittstelle) für *Command*-Objekte. Enthält Informationen über das *Receiver*-Objekt,
    das für die Ausführung der Operation unter Verwendung der im *Command*-Objekt abgelegten Informationen verantwortlich ist.
  * **ConcreteCommand**: Konkrete Implementierung der abstrakten `CommandBase`-Klasse bzw. -Schnittstelle.
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

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
