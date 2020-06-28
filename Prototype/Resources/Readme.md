# Prototype Pattern

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Prototype Pattern* ist ein Entwurfsmuster, das zum Instanziieren einer Klasse durch Kopieren oder Klonen der Eigenschaften eines vorhandenen Objekts verwendet wird.
Das neue Objekt ist eine exakte Kopie des Prototyps, ermöglicht jedoch Änderungen, ohne das Original zu verändern.

#### Problem:

Mit dem *Prototype* Entwurfsmuster können wir die Komplexität des Erstellens
neuer Instanzen vor dem Client verbergen. Das Konzept besteht darin, ein vorhandenes Objekt zu kopieren,
anstatt eine neue Instanz (samt dazugehöriger Klasse) von Grund auf neu zu erstellen.
Dies kann bisweilen mit einem recht zeitintensiven Aufwand verbunden sein.

Das vorhandene Objekt fungiert als Prototyp eines neuen Objekts und besitzt seinen Status.
Das neu kopierte Objekt kann dieselben Eigenschaften nur bei Bedarf ändern.
Dieser Ansatz spart Ressourcen und Zeit,
insbesondere wenn die Objekterstellung nicht-trivial ist.

#### Lösung:

Das *Prototype* Entwurfsmuster ist ein erzeugendes Entwurfsmuster.
Das Entwurfsmuster ist erforderlich, wenn die Objekterstellung zeitaufwändig und kostspielig ist.
Daher erstellen wir ein neues Objekt auf Basis eines vorhandenen Objekts.
Am einfachsten lässt sich ein 
Eine der einfachsten Vorgehensweisen zum Erstellen von Objekten aus vorhandenen Objekten
ist das Kopieren eines Objekts (Kopier-Konstruktor).
Diese Art der Objekterstellung wird als *Klonen* bezeichnet.
Allerdings muss diese Methode nicht zwingend von allen C++-Objekten unterstützt werden.

#### Struktur (UML):

TODO

Das folgende UML-Diagramm beschreibt eine Implementierung des *Prototype Patterns*.
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


<img src="dp_prototype.png" width="500">

Abbildung 1: Schematische Darstellung des *Prototype Patterns*.

#### Hinweis:

In JavaScript ist das *Prototype Pattern* quasi nativ enthalten.

Die Erstellung von Objekten erfolgt hier - unter anderem - auf der Basis von so genannten
"Konstruktorfunktionen", die als Blaupausen für neue Objekte verwendet werden können,
Man spricht dabei auch von der so genannten *"Prototypische Vererbung"*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/prototype/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Prototype)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

"PersonCaretaker"

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme.md)

---

