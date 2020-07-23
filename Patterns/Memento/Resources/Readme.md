# Memento Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Memento Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
mit dem der aktuelle Status eines Objekts gespeichert werden kann,
ohne dabei etwaige Details seiner Realisierung offenzulegen.
Das Ursprungsobjekt kann nach Bedarf geändert als auch
jederzeit in den gespeicherten Zustand zurückversetzt werden.

#### Problem:

Manchmal ist es erforderlich, den (internen) Status eines Objekts zu einem bestimmten Zeitpunkt zu erfassen
und diesen Status zu einem späteren Zeitpunkt wieder zu restaurieren.
Häufig wird dieses Enwurfsmuster verwendet, um eine Anwendung um die "*Undo*"-Funktionalität zu bereichern.
Aus diesem Grund wird das Muster auch als "*Undo via Rollback*" bezeichnet,
in anderen Büchern wiederum tritt es als *Snapshot* Entwurfsmuster in Erscheinung.

#### Lösung:

Das Memento-Muster delegiert das Erstellen des Status-Schnappschusses an den tatsächlichen Eigentümer dieses Status,
also das betrachtete Ursprungsobjekt.
Dies hat den Vorteil, dass ein Zugriff auf den Status des Objekts "von außen" nicht notwendig ist,
da in den meisten Fällen auf Grund des Zugriffsschutzes der privaten (`private`) und geschützten  (`protected`) Variablen auch gar nicht möglich ist.
Das Ursprungsobjekt selbst hat den vollen Zugriff auf seinen eigenen Status.

Das Muster sieht vor, die Kopie des Objektstatus in einem speziellen Objekt namens "Memento" zu speichern.
Das "Memento"-Objekt ist keinem anderen Objekt zugänglich als dem, das es erstellt hat.
Andere Objekte können über eine eingeschränkte Schnittstelle mit "Memento"-Objekten kommunizieren,
um so die Metadaten des "Memento"-Objekt abrufen zu können
(Erstellungszeit, Name des ausgeführten Vorgangs usw.).
Es ist nicht der Zugriff auf den im Schnappschuss enthaltene Status des ursprünglichen Objekts möglich.

Mit einer solchen restriktiven Richtlinie lassen sich Memento-Objekte in anderen Objekten speichern,
die als "*CareTaker*" bezeichnet werden. Da ein *CareTaker* nur über die eingeschränkte Schnittstelle mit dem Memento-Objekt kommunizieren kann,
kann er den im Memento-Objekt gespeicherten Status nicht manipulieren.
Gleichzeitig hat der Urheber Zugriff auf alle Daten des Memento-Objekts,
sodass er seinen ursprünglichen Zustand nach Belieben wiederherstellen kann.

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


<img src="dp_memento.png" width="500">

Abbildung 1: Schematische Darstellung des *Memento Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/memento/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

"PersonCaretaker"

https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
