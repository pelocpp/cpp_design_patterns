# Chain of Responsibility Pattern

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

Im Prinzip betrachten wir das Problem, dass ein bestimmtes Ereignis von einem anderen Objekt zu verarbeiten ist.
Das *Chain of Responsibility Pattern* ist eine formale Beschreibung dieses Problems.
Wir haben in diesem Muster eine *Quelle* (*Ereignis*, *Event*) und mehrere Objekte, die auf dieses Ereignis reagieren wollen.
Das Ereignis wird bei Eintreten an das erste Verarbeitungsobjekt übergeben.
Dieses kann den Befehl verarbeiten (oder auch nicht) und/oder an seinen Nachfolger senden.
Dies wird solange fortgesetzt, bis der Befehl verarbeitet wurde oder das Ende der Kette erreicht ist.
Das Objekt, das den Befehl sendet (das Ereignis ausgelöst hat), weiß nicht, welches Objekt in der Kette aller Verarbeitungsobjekte
den Befehl verarbeitet hat.

Bzgl. der Verarbeitung sind mehrere Szenarien denkbar: Hat ein Verarbeitungsobjekt die Anfrage übernommen,
kann es das Weiterreichen der Anfrage an die noch vorhandenen Objekte in der Kette unterlassen ("*Single-Cast*" Szenario).
Umgekehrt ist es denkbar, dass eine Anfrage prinzipiell die gesamte Kette aller Verarbeitungsobjekte durchläuft.
Kein, ein oder mehrere Objekte können hierbei ihren Beitrag zur Abarbeitung des Ereignisses beitragen.


#### Lösung:

Das Pattern ermöglicht es, eine Anfrage an eine Kette von Verarbeitungsobjekten zu senden,
ohne wissen zu müssen, welches Objekt / welche Objekte die Anfrage bearbeiten.
Die Anfrage wird entlang der Kette weitergeleitet, bis ein oder mehrere Empfänger die Anfrage bearbeiten.
Es kann auch sein, dass das Ereignis von keinem Empfänger bearbeitet wird.
Der Absender eines Ereignisses ist nicht mit einem bestimmten Empfänger direkt verbunden.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Chain of Responsibility Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Client**: Diese Klasse übergibt das Ereignis (die Anforderung) an das erste Objekt in der Kette der Verarbeitungsobjekte.
  * **HandlerBase**: Repräsentiert eine Schnittstelle oder Basisklasse für die konkreten Handler einer Verarbeitungskette.
    Typischerweise enthält es eine Instanzvariable, die auf das nächste Handlerobjekt in der Verarbeitungskette verweist.
  * **ConcreteHandler**: Konkrete Implementierung der `HandlerBase`-Klasse.


<img src="dp_chain_of_responsibility.svg" width="700">

Abbildung 1: Schematische Darstellung des *Chain of Responsibility Patterns*.


#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/chain-of-responsibility/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Chain)

vor.

## Weiterarbeit:

Siehe das Beispiel unter

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
