# Memento Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_memento_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Zum Speichern und Wiederherstellen des Zustands einer Komponente/eines Objekts.&rdquo;

Das *Memento Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
mit dem der aktuelle Status eines Objekts gespeichert werden kann,
ohne dabei etwaige Details seiner Realisierung offenzulegen.
Das Ursprungsobjekt kann nach Bedarf ge�ndert als auch
jederzeit in den gespeicherten Zustand zur�ckversetzt werden.

#### Problem:

Manchmal ist es erforderlich, den (internen) Status eines Objekts zu einem bestimmten Zeitpunkt zu erfassen
und diesen Status zu einem sp�teren Zeitpunkt wieder zu restaurieren.
H�ufig wird dieses Entwurfsmuster verwendet, um eine Anwendung um die &bdquo;*Undo*&rdquo;-Funktionalit�t zu bereichern.
Aus diesem Grund wird das Muster auch als &bdquo;*Undo via Rollback*&rdquo; bezeichnet,
in anderen B�chern wiederum tritt es als *Snapshot* Entwurfsmuster in Erscheinung.

#### L�sung:

Das Memento-Muster delegiert das Erstellen des Status-Schnappschusses an den tats�chlichen Eigent�mer dieses Status,
also das betrachtete Ursprungsobjekt.
Dies hat den Vorteil, dass ein Zugriff auf den Status des Objekts &bdquo;von au�en&rdquo; nicht notwendig ist,
der in den meisten F�llen auf Grund des Zugriffsschutzes der privaten (`private`) und gesch�tzten  (`protected`) Variablen auch gar nicht m�glich ist.
Das Ursprungsobjekt selbst hat den vollen Zugriff auf seinen eigenen Status.

Das Muster sieht vor, die Kopie des Objektstatus in einem speziellen Objekt namens &bdquo;Memento&rdquo; zu speichern.
Das &bdquo;Memento&rdquo;-Objekt ist keinem anderen Objekt zug�nglich als dem, das es erstellt hat.
Andere Objekte k�nnen �ber eine eingeschr�nkte Schnittstelle mit &bdquo;Memento&rdquo;-Objekten kommunizieren,
um so die Metadaten des &bdquo;Memento&rdquo;-Objekt abrufen zu k�nnen
(Erstellungszeit, Name des ausgef�hrten Vorgangs usw.).
Es ist nicht der Zugriff auf den im Schnappschuss enthaltene Status des urspr�nglichen Objekts m�glich.

Mit einer solchen restriktiven Richtlinie lassen sich Memento-Objekte in anderen Objekten speichern,
die als &bdquo;*CareTaker*&rdquo; bezeichnet werden. Da ein *CareTaker* nur �ber die eingeschr�nkte Schnittstelle mit dem Memento-Objekt kommunizieren kann,
kann er den im Memento-Objekt gespeicherten Status nicht manipulieren.
Gleichzeitig hat der Urheber Zugriff auf alle Daten des Memento-Objekts,
sodass er seinen urspr�nglichen Zustand nach Belieben wiederherstellen kann.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Memento Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Originator**: Erstellt ein Memento-Objekt, das den internen Status des Urhebers (*Originator*) erfasst.
    Der Urheber verwendet das Memento-Objekt, um seinen vorherigen Status wiederherzustellen.
  * **Memento**: Speichert den internen Status des Urheber-Objekts. Der Status kann beliebig umfangreich sind. Das Memento-Objekt muss zwei Schnittstellen unterst�tzen:
    Eine Schnittstelle zum *CareTaker*: Diese Schnittstelle darf keine Operationen oder keinen Zugriff auf den vom Memento-Objekt gespeicherten internen Zustand zulassen und ber�cksichtigt daher den Zugriffsschutz.
    Die andere Schnittstelle besteht zum Urheber und erm�glicht ihm den Zugriff auf den gesamten Status, der erforderlich ist,
    damit der Urheber einen urspr�nglichen Zustand wiederherstellen kann.
  * **CareTaker**: Ist verantwortlich f�r die Aufbewahrung des Memento-Objekts.
    Das Memento-Objekt ist f�r den *CareTaker* eine Black-Box,
    der CareTaker kann darauf nicht zugreifen. 


<img src="dp_memento.svg" width="600">

*Abbildung* 1: Schematische Darstellung des *Memento Patterns*.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfaches Beispiel

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Etwas ausf�hrlicheres Beispiel

---

#### &bdquo;Real-World&rdquo; Example:

Wir stellen eine Klasse `BankAccount` vor, 
in der wir jede �nderung als *Memento* aufzeichnen.
Zu einem sp�teren Zeitpunkt kann der Benutzer das `BankAccount`-Objekt auf diesen Snapshot zur�ckzusetzen.

In diesem Beispiel wird die `Memento`-Klasse als innere Klasse der `BankAccount`-Klasse implementiert.
Dies ist auch eine M�glichkeit, um der `BankAccount`-Klasse den vollen Zugriff auf alle Werte eines *Memento*-Objekts zu geben.

Das `BankAccount`-Beispiel demonstriert die Realisierung einer *Undo*/*Redo*-Funktionalit�t.

[Quellcode 3](../BankAccount.cpp) &ndash; Ein Bankkonto mit *Undo*/*Redo*-Funktionalit�t.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/memento/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento)

vor.

Das *Real*-*World*-Beispiel kann [hier](https://vishalchovatiya.com/posts//memento-design-pattern-in-modern-cpp/) im Original nachgelesen werden.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
