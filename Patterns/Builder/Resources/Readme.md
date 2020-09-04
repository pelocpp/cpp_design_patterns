# Builder Pattern

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Builder Pattern* ist ein Entwurfsmuster, mit dem schrittweise komplexe Objekte mit der richtigen Reihenfolge von Aktionen erstellt werden können.
Die Konstruktion wird von einem *Director*-Objekt gesteuert,
das nur den Objekttyp kennen muss, den es erstellen soll.

#### Ziel / Absicht:

Das *Builder Pattern* ist ein Entwurfsmuster aus der Kategorie der *Creational Pattern*. 
Mit diesem Entwurfsmuster soll die Konstruktion eines komplexen Objekts von seiner Darstellung getrennt werden.
Dieses Muster wird verwendet, wenn komplexe Objekte, die erstellt werden müssen, aus Bestandteilen bestehen,
die in einer bestimmten Reihenfolge oder unter Verwendung eines bestimmten Algorithmus erstellt werden müssen.

#### Lösung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Builder Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Product**: Klasse, die das komplexe Objekt repräsentiert, das zu erstellen ist.
  * **Builder**: Abstrakte Basisklasse (oder Schnittstelle) für `Builder`-Objekte. Es werden die Schritte definiert,
    die ausgeführt werden müssen, um ein komplexes Objekt (Produkt) korrekt zu erstellen.
    Typischerweise ist jeder Schritt eine abstrakte Methode, die durch eine konkrete Implementierung überschrieben wird.
  * **ConcreteBuilder**: Stellt eine Implementierung der `Builder`-Schnittstelle bereit. Ein `Builder`-Objekt ist ein Objekt,
    das andere komplexe Objekte ("Produkte") erstellen kann.
  * **Director**: Stellt die Klasse dar, die den Algorithmus steuert, der zum Erstellen des komplexen Objekts verwendet wird.

<img src="dp_builder_pattern.svg" width="550">

Abbildung 1: Schematische Darstellung des *Builder Patterns*.


#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/builder/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Builder)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
