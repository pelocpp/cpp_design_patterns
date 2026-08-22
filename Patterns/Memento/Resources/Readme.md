# Memento Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_memento_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

> &bdquo;Das Memento Pattern ermöglicht es, den Zustand eines Objekts zu speichern und später wiederherzustellen, ohne dessen interne Implementierung nach außen offenzulegen.&rdquo;

Das *Memento Pattern* dient dazu, den Zustand eines Objekts zu einem bestimmten Zeitpunkt zu speichern und später wiederherzustellen.
Dazu wird eine Momentaufnahme des Zustands in einem separaten Objekt, dem sogenannten *Memento*, abgelegt.
Das ursprüngliche Objekt kann seinen Zustand bei Bedarf aus diesem Memento wiederherstellen.

Ein wesentlicher Aspekt des Patterns ist, dass der gespeicherte Zustand außerhalb des ursprünglichen Objekts nicht verändert
oder eingesehen werden muss. Dadurch bleibt die Kapselung des ursprünglichen Objekts erhalten.

Ein weiteres Objekt, häufig als *Caretaker* bezeichnet, kann die Mementos verwalten, ohne deren Inhalt kennen zu müssen.

Typische Anwendungsfälle sind Undo/Redo-Mechanismen in Editoren, das Zurücksetzen von Einstellungen, Transaktionsverwaltung,
Spielstände in Spielen oder das Zurücksetzen fehlgeschlagener Operationen.

In modernem C++ lässt sich das Pattern besonders elegant mit `std::unique_ptr`, `std::optional` oder Value-Semantik umsetzen,
wodurch man auf manuelles Speichermanagement weitgehend verzichten kann.

Ein Nachteil des Patterns ist der potenziell hohe Speicherverbrauch, wenn viele oder große Snapshots gehalten werden müssen,
weshalb in der Praxis oft zusätzliche Strategien wie Differenzspeicherung oder Kompression zum Einsatz kommen.



#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Memento Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Originator**: Erstellt ein Memento-Objekt, das den internen Status des Urhebers (*Originator*) erfasst.
    Der Urheber verwendet das Memento-Objekt, um seinen vorherigen Status wiederherzustellen.
  * **Memento**: Speichert den internen Status des Urheber-Objekts. Der Status kann beliebig umfangreich sind. Das Memento-Objekt muss zwei Schnittstellen unterstützen:
    Eine Schnittstelle zum *CareTaker*: Diese Schnittstelle darf keine Operationen oder keinen Zugriff auf den vom Memento-Objekt gespeicherten internen Zustand zulassen und berücksichtigt daher den Zugriffsschutz.
    Die andere Schnittstelle besteht zum Urheber und ermöglicht ihm den Zugriff auf den gesamten Status, der erforderlich ist,
    damit der Urheber einen ursprünglichen Zustand wiederherstellen kann.
  * **CareTaker**: Ist verantwortlich für die Aufbewahrung des Memento-Objekts.
    Das Memento-Objekt ist für den *CareTaker* eine Black-Box,
    der CareTaker kann darauf nicht zugreifen. 


<img src="dp_memento.svg" width="600">

*Abbildung* 1: Schematische Darstellung des *Memento Patterns*.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp) &ndash; Einfaches Beispiel<br />

---

#### &bdquo;Real-World&rdquo; Example:

Wir stellen eine Klasse `BankAccount` vor, 
in der wir jede Änderung als *Memento* aufzeichnen.
Zu einem späteren Zeitpunkt kann der Benutzer das `BankAccount`-Objekt auf diesen Snapshot zurückzusetzen.

In diesem Beispiel wird die `Memento`-Klasse als innere Klasse der `BankAccount`-Klasse implementiert.
Dies ist auch eine Möglichkeit, um der `BankAccount`-Klasse den vollen Zugriff auf alle Werte eines *Memento*-Objekts zu geben.

Das `BankAccount`-Beispiel demonstriert die Realisierung einer *Undo*/*Redo*-Funktionalität.

[Quellcode](../BankAccount.cpp) &ndash; Ein Bankkonto mit *Undo*/*Redo*-Funktionalität.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/memento/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Memento)

vor.

Das *Real*-*World*-Beispiel kann [hier](https://vishalchovatiya.com/posts//memento-design-pattern-in-modern-cpp/) im Original nachgelesen werden.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
