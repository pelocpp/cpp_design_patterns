# Facade Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_facade-pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Bereitstellung einer einheitlichen (vereinfachten) Schnittstelle durch Verbergen einer vorhandenen Systemkomplexit�t.&rdquo;

Das *Facade Pattern* ist ein strukturelles Entwurfsmuster,
das verwendet wird, um den Zugriff auf Funktionen in komplexen oder schlecht gestalteten Subsystemen/Bibliotheken
oder Vergleichbares zu vereinfachen.
Die Fassadenklasse stellt eine einfache Schnittstelle zur Verf�gung,
die die Implementierungsdetails des zugrunde liegenden Codes verbirgt.

#### Problem:

Gegeben sei ein komplexes Subsystem mit vielen Klassen und Abh�ngigkeiten zwischen ihnen.
Clients die dieses Subsystem oder Teile davon nutzen m�chten,
m�ssen sich mit den verschiedenen Schnittstellen der enthaltenen Klassen befassen und die Funktionsweise verstehen.
Dabei bauen sie zwangsl�ufig viele Abh�ngigkeiten zu verschiedenen Objekten auf und koppeln sich eng an die Klassen des Subsystems.
Das *Facade Pattern* definiert eine vereinfachte Schnittstelle zur Benutzung eines Systems (Bibliothek) oder einer Menge von Objekten.

#### L�sung:

Die *Facade* (dt. Fassade) wird zwischen Clients und dem Subsystem geschaltet.
Es "kapselt" dabei das Subsystem, beinhaltet die komplexe Logik zum Arbeiten mit dem Subsystem
und bietet f�r den Client eine vereinfachte Schnittstelle (Methoden) nach au�en an.
Die Fassade delegiert die Clientaufrufe an das Subsystem.
Dadurch kann der Client das System �ber die Facade nutzen,
ohne die Klassen, ihre Beziehungen, und Abh�ngigkeiten zu kennen.

Der Einsatz des *Facade Pattern* bietet sich vor allem dann an, wenn mehrere Entwickler eines Teams davon
profitieren k�nnen. Es m�ssen sich nicht alle Entwickler des Teams mit dem komplexen Subsystem besch�ftigen.

#### Hinweis 1:

Eine Facade kann auch als eine Art "*Wrapper*" angesehen werden. H�ufig gibt es - zum Beispiel unter Windows -
Bibliotheken, die rein prozedural sind (DLL, *Dynamic Link Library*).
Mit Hilfe einer Facade kann man eine objektorientierte Sicht auf eine reine C-Bibliothek zur 
Verf�gung stellen.

#### Hinweis 2:

Eine Facadenklasse soll eine Vereinfachung in der Komplexit�t des/der unterlagerten Subsystems/Subsysteme darstellen.
Dies hat allerdings auch zur Folge, dass die Facadenklasse nur einen Teil
(in manchen F�llen sogar nur einen Bruchteil) von den F�higkeiten der Subsysteme besitzt.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Facade Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Facade**: Diese Klasse enth�lt eine Reihe einfacher Funktionen (Methoden), die ihren Benutzern zur Verf�gung gestellt werden und die die Komplexit�t der schwer zu verwendenden Subsysteme verbergen.
  * **SubSystemA/B**: Die komplexe Funktionalit�t, auf die �ber die Fassadenklasse zugegriffen wird, muss nicht in einem einzelnen Subsystem (Paket, Namensraum, Bibliothek, ...) vorhanden sein.
  * **ClassA/B**: Diese Klassen (Funktionen bei einer prozeduralen Schnittstelle) enthalten die Funktionalit�t, die �ber die Fassade pr�sentiert wird.

<img src="dp_facade_pattern.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Facade Patterns*.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

## Pro / Kontra:

###### Pros:

  * Die Komplexit�t eines existierenden Quellcodes kann vor dem Client verborgen werden.
  * &bdquo;Macht Schnittstellen einfach richtig zu bedienen und schwer falsch zu verwenden.&rdquo; (Scott Meyers).
  * Kann behilflich sein, komplexe Systeme auf eine andere Plattform zu portieren, weil der Client nur auf die Fassade angewiesen ist.

###### Kontras:

  * Eine Fassade hat m�glicherweise zu viele Verantwortlichkeiten und endet im Antimuster &bdquo;God Object&rdquo;.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/facade/cpp/example#lang-features)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Facade)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
