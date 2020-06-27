# Abstract Factory

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Abstract Factory* Pattern ist ein Entwurfsmuster,
mit dem Gruppen miteinander verwandter Objekte erstellt werden können,
ohne dass die genauen konkreten Klassen angegeben werden müssen, die dabei verwendet werden sollen.
Eine von mehreren Factory-Klassen generiert die jeweiligen Objektmengen.

#### Problem:

Dieses Muster ist sehr gut, wenn Sie die Details der Objektinstanziierung trennen möchten.
Im Allgemeinen haben Fabriken mehr als eine Factory-Methode.
Jede Factory-Methode kapselt den `new`-Operator und die konkreten, plattformspezifischen Klassen.
Jede Plattform wird dann von einer Klasse reräsentiert, die sich von einer der Fabriken ableitet.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Abstract Factory Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Client**: Ein Client benutzt ausschließlich Methoden der beiden (abstrakten)
    Klassen `AbstractFactory` und `AbstractProduct`.
  * **AbstractFactory**: Abstrakte Basisklasse für alle konkreten Factory-Klassen, die miteinander verwandte Objekte erzeugen.
    Für jeden Objekttyp, der instanziiert wird, ist eine Methode enthalten.
  * **ConcreteFactory**: Diese Klasse leitet sich von `AbstractFactory` ab.
    `ConcreteFactory` überschreibt die Methoden von `AbstractFactory`, die neue miteinander verwandte Objekte generieren.
  * **AbstractProduct**: Basisklasse für alle Arten von Objekten, die von einer Factory erstellt werden können.
  * **ConcreteProduct**: Konkrete Implementierung der `AbstractProduct`-Klasse.
    Es kann natürlich mehrere Klassen geben, die sich von der `AbstractProduct`-Klasse mit jeweils
    spezifischer Funktionalität ableiten.

<img src="dp_abstract_factory.png" width="800">

Abbildung 1: Schematische Darstellung des *Abstract Factory* Entwurfsmusters.

Die Klassen `ProductA` und `ProductB` sind Stellvertreter der `ConcreteProduct` Klasse
aus Abbildung 1.

#### 'Real-World' Example:

Im  'Real-World' Beispiel zu diesem Entwurfsmuster wird
die Herstellung verschiedener Fahrzeugtypen verschiedener Hersteller betrachtet.
Es gibt eine abstrakte Fabrikschnittstelle namens `IVehicleFactory` (*abstract Factory*)
und zwei konkrete Fabrikimplementierungen namens `FordFactory`  und `MitsubishiFactory`. 
`IVehicleFactory` verfügt über drei Methoden `createEconomyCar`, `createRacingCar` und `createSUV`,
mit denen `Vehicle`-Objekte zurückgegeben werden.
Die Klasse `Vehicle` ist eine abstrakte Basisklasse für alle konkreten Produkte.

---

[Zurück](../../Readme_05_Catalog.md)

---
