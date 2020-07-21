# State Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *State Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*.

Das Muster beschreibt, wie ein Objekt sein Verhalten in Abhängigkeit
von seinem aktuellen internen Zustand vollständig ändern kann.
Es scheint, als hätte das Objekt seine Klasse geändert.

#### Problem:

    
#### Lösung:

Mit diesem Entwurfsmuster lässt sich das Verhalten eines Objekts
als Reaktion auf Änderungen seines internen Zustands ändern.
Das Verhalten ist zur Laufzeit änderbar, ohne dass die für den Zugriff auf das Objekt
verwendete bzw. vorhandene Schnittstelle sich ändert.
Die Änderungen sind im Kontext des Objekts verborgen.

Dieses Muster ist sehr nützlich beim Erstellen von Software Zustandsautomaten,
bei denen sich die Funktionalität eines Objekts je nach Status grundlegend ändert.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *State Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Context**: Diese Klasse hat Zugriff auf das konkrete Statusobjekt,
    das das Verhalten gemäß seinem aktuellen Status bereitstellt.
  * **StateBase**: Abstrakte Klasse für konkrete Zustandsklassen.
    Sie definiert die Schnittstelle, die von der `Context`-Klasse verwendet wird.
  * **ConcreteState**: Konkrete Implementierung der `StateBase`-Klasse.
    Die Funktionalität dieser Objekte wird von der Kontextklasse genutzt.

<img src="dp_state_pattern.png" width="500">

Abbildung 1: Schematische Darstellung des *State Patterns*.


#### Conceptual Example:

*Hinweis*:

Das *Conceptual Example* liegt in drei Versionen vor:

  * Ein einfaches Beispiel - mit *raw*-Zeigern 
  * Dasselbe Beispiel - mit `std::shared_ptr`-Zeigern
  * Ein zweites einfaches Beispiel

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/state/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#State)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme_05_Catalog.md)

---
