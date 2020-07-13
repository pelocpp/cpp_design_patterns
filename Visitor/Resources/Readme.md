# Visitor Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das Visitor Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
...

#### Problem:



#### Lösung:



#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Command Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Originator**: Erstellt ein Memento-Objekt, das den internen Status des Urhebers erfasst.
    Der Urheber verwendet das Memento-Objekt, um seinen vorherigen Status wiederherzustellen.
  * **Memento**: Speichert den internen Status des Urheber-Objekts. Der Status kann beliebig umfangreich sind. Das Memento-Objekt muss zwei Schnittstellen unterstützen:
    Eine Schnittstelle zum *CareTaker*: Diese Schnittstelle darf keine Operationen oder keinen Zugriff auf den vom Memento-Objekt gespeicherten internen Zustand zulassen und berücksichtigt daher den Zugriffsschutz.
    Die andere Schnittstelle besteht zum Urheber und ermöglicht ihm den Zugriff auf den gesamten Status, der erforderlich ist,
    damit der Urheber einen ursprünglichen Zustand wiederherstellen kann.
  * **CareTaker**: Ist verantwortlich für die Aufbewahrung des Memento-Objekts.
    Das Memento-Objekt ist für den CareTaker eine Black-Box,
    der CareTaker kann darauf nicht zugreifen. 


<img src="dp_xxx.png" width="500">

Abbildung 1: Schematische Darstellung des *Visitor Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/command/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Command)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

"PersonCaretaker"

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme_05_Catalog.md)

---
