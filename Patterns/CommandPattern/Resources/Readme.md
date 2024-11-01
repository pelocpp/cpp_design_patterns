# Command Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_command_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Entkoppelt einen Sender und Empf�nger, indem ein separates Objekt f�r ein oder mehrere Operationen erstellt wird.&rdquo;

Das *Command Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
das eine Anforderung (einen *Request*, einen *Befehl*) in ein eigenst�ndiges Objekt umwandelt,
das alle Informationen �ber das Kommando enth�lt.
Der Befehl kann dann nach Bedarf aufgerufen werden, h�ufig als Teil einer Reihe von Befehlen,
die in einer Warteschlange (*Queue*) abgelegt sind.
Die Befehle in der Warteschlange k�nnen auf diese Weise sequentiell abgearbeitet werden,
denkbar sind auch *Rollback*- bzw. *Undo*-Funktionalit�ten.

#### Problem:

Das *Command Pattern* ist ein Entwurfsmuster, bei dem alle zur Ausf�hrung einer Methode erforderlichen Informationen
in einem Objekt gekapselt sind, das sofort verwendet oder zum sp�teren Gebrauch aufbewahrt werden kann.
Dieses Objekt f�hrt nichts aus, es enth�lt nur Informationen.

Es gibt drei Schl�sselbegriffe, die im Umfeld dieses Patterns zu definieren sind: *Client*, *Invoker* und *Receiver*.
Der *Client* erstellt das Befehlsobjekt ("*Command Object*").
Das *Invoker*-Objekt entscheidet, wann die Methode, deren Informationen (*Parameter*) im *Command Object* abgelegt sind, aufgerufen werden soll.
Das *Receiver*-Objekt ist eine Instanz einer Klasse, die den eigentlichen Code der auszuf�hrenden Methode enth�lt.

#### L�sung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Command Patterns*.
Es besteht im Wesentlichen aus f�nf Teilen:

  * **Client**: Genereller Konsument der Klassen des Entwurfsmusters. Er erstellt das *Command Object* und verkn�pft es mit *Receiver*-Objekten.
  * **Receiver**: Objekt, das wei�, wie das Kommando (Methode) auszuf�hren ist.
  * **CommandBase**: Abstrakte Klasse (oder Schnittstelle) f�r *Command*-Objekte. Enth�lt Informationen �ber das *Receiver*-Objekt,
    das f�r die Ausf�hrung der Operation unter Verwendung der im *Command*-Objekt abgelegten Informationen verantwortlich ist.
  * **ConcreteCommand**: Konkrete Implementierung der abstrakten `CommandBase`-Klasse bzw. -Schnittstelle.
  * **Invoker**: Objekt, das entscheidet, wann das Kommando ausgef�hrt werden soll.


<img src="dp_command_pattern.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Command Patterns*.

---

#### 'Beginners Example':

Bei den Fallstudien zu diesem Seminar finden Sie unter dem Stichwort &bdquo;Bankkonten&rdquo;
ein praxisnahes Beispiel vor.

---


#### Conceptual Example:

[Quellcode 1](../ConceptualExample_01.cpp) &ndash; Sehr einfaches Beispiel

[Quellcode 2](../ConceptualExample_02.cpp) &ndash; Ein etwas ausf�hrlicheres Beispiel

---

#### &bdquo;Real-World&rdquo; Beispiel:

F�r das *Command Pattern* wird in
["Entwurfsmuster: Das umfassende Handbuch" von Matthias Geirhos](https://www.amazon.de/Entwurfsmuster-umfassende-Handbuch-Matthias-Geirhos/dp/3836227622)
ein Beispiel aus dem Umfeld der Spieleprogrammierung betrachtet: Die Implementierung eines Ausschnitts aus dem Schachspiel,
soweit er die Verwendung des *Command Pattern* Entwurfsmusters betrifft, siehe *Abbildung* 2:

<img src="dp_command_pattern_chess.svg" width="800">

*Abbildung* 2: Ein Schachspiel modelliert mit dem *Command Pattern*.

Ein Kommando wird in *Abbildung* 2 durch die Klasse `Move` dargestellt.
Davon leiten sich unterschiedliche Kommandos ab, beim Schachspiel reden wir hier von einem Spielzug.
Neben einem "normalen" Zug, der nur die Regeln der jeweiligen Spielfigur zu beachten hat, gibt es auch spezielle Z�ge
wie "Rochade" (engl. *Castling*)
und die "Umwandlung eines Bauern" (engl. *PromotePawn*).

Ein Spielfeld (engl. *Board*) verwaltet Spielz�ge, oder eben Kommandos, um in der Nomenklatur dieses Entwurfsmusters zu bleiben.
In einer listenartigen Datenstruktur (`std::queue`) kann es mehrere Z�ge (Kommandos) abspeichern, ohne diese sofort auszuf�hren.

F�r die konkrete Ausf�hrung eines Spielzugs ist die Klasse `ChessPiece` verantwortlich. 

  * Bringen Sie das Beispiel auf Ihrem Rechner zum Laufen.
  * �berlegen Sie, welche Beteiligten des allgemeinen Musters (*Receiver*, *CommandBase*, etc.) welchen Klassen des Schachspiels zuzuordnen sind. 
  * Erg�nzen Sie eine Klasse `PromotePawn` und integrieren Sie das Kommando "Umwandlung des Bauern" in das Spiel.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/command/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
