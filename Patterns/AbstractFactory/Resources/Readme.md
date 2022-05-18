# Abstract Factory

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Abstract Factory* Pattern ist ein Entwurfsmuster,
mit dem Gruppen miteinander verwandter Objekte erstellt werden können,
ohne dass die genauen konkreten Klassen angegeben werden müssen, die dabei verwendet werden.
Eine von mehreren Factory-Klassen generiert die jeweiligen Objektmengen.

#### Problem:

Dieses Muster ist sehr gut, wenn Sie die Details der Objektinstanziierung trennen möchten.
Im Allgemeinen haben Fabriken mehr als eine Factory-Methode.
Jede Factory-Methode kapselt den `new`-Operator und die konkreten, plattformspezifischen Klassen.
Jede Plattform wird dann von einer Klasse repräsentiert, die sich von einer der Fabriken ableitet.

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

<img src="dp_abstract_factory_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Abstract Factory* Entwurfsmusters.

Die Klassen `ProductA1` und `ProductA2` bzw. `ProductB1` und `ProductB2` sind Stellvertreter
der `ConcreteProductA`- bzw. `ConcreteProductB`-Klasse aus *Abbildung* 1.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

Die Ausgaben des konzeptionellen Beispiels lauten:

```
Client: Testing client code with the first factory type:
The result of the product B1.
The result of the B1 collaborating with ( The result of the product A1. )

Client: Testing the same client code with the second factory type:
The result of the product B2.
The result of the B2 collaborating with ( The result of the product A2. )
```

---

#### Hinweis:

Die beiden Entwurfsmuster *Abstract Factory* und *Factory Method* sind nicht 
miteinander zu verwechseln.

Sie haben zumindest gemeinsam, dass sie beide den Client von konkreten Typen entkoppeln.
Der Client kennt nur die Schnittstelle zur *Factory* und den Produkten. Welche Produkte konkret erstellt werden,
entscheidet die Unterklasse/Implementierung der Schnittstelle. Der Client stützt sich allein auf Abstraktion.

Damit zu den Unterschieden:

**Abstract Factory**<br/>
  * Bietet eine Schnittstelle zum Erstellen von Familien verwandter oder abhängiger Objekte, ohne deren konkrete Klassen anzugeben.
  * Ganze Produktfamilie wird erstellt.
  * Breite Schnittstelle.
  * Schnittstelle (Abstract Factory) ist oft nur ein Interface und enthält keinen Implementierungscode.

**Factory Method**<br/>
  * Definiert eine Schnittstelle zum Erstellen eines Objekts, aber lässt
    die Unterklassen entscheiden, welche Klasse instanziiert werden soll.
    Mit dem *Factory Method Pattern* kann eine Klasse die Instanziierung auf Unterklassen verschieben.
  * Schmale Schnittstelle.
  * Schnittstelle ist oft abstrakt und enthält generischen Code (Herstellungscode, den alle Produkte durchlaufen müssen).

---

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#AbstractFactory)

vor.

#### 'Real-World' Beispiel:

Ein Klassiker für dieses Entwurfsmuster ist die Java Swing Oberflächenbibliothek und hier im
Speziellen der Aspekt "*Look and Feel*".
Für Oberflächensteuerelemente wie Listen, Comboboxen oder Eingabefelder gibt es hier verschiedene Varianten.
Diese Varianten sind in ihrer Grundfunktionalität gleich, unterscheiden sich aber in ihrem Aussehen
und teilweise auch in ihrem Verhalten.

Für jedes *Look and Feel* gibt es eine eigene Familie an graphischen Steuerelementen und damit
eine eigenen Fabrik. Abstrahiert werden all diese Fabriken durch eine zentral definierte abstrakte Fabrik.
Nur um einen Eindruck zu erhalten, finden Sie in Tabelle 1 eine - nicht vollständige - Auflistung
der unterschiedlichen Bibliotheken, also sprich konkreten UI-Fabriken vor:

| Plattform | Look and Feel |
|:-------------- |----|
| Cross Platform Look And Feel | Metal |
| Solaris, Linux with GTK+ 2.2 or later | GTK+ |
| Other Solaris, Linux | Motif | 
| Classic Windows | Windows | 
| HP UX | HP* | 

Tabelle 1: Verfügbare *Look and Feel* UI-Fabriken.


#### Zweites 'Real-World' Beispiel:

Im 'Real-World' Beispiel zu diesem Entwurfsmuster wird
die Herstellung verschiedener Fahrzeugtypen verschiedener Hersteller betrachtet.
Es gibt eine abstrakte Fabrikschnittstelle namens `IVehicleFactory` (*Abstract Factory*)
und zwei konkrete Fabrikimplementierungen namens `FordFactory`  und `MitsubishiFactory`. 
`IVehicleFactory` verfügt über drei Methoden `createEconomyCar`, `createRacingCar` und `createSUV`,
mit denen `Vehicle`-Objekte zurückgegeben werden.
Die Klasse `Vehicle` ist eine abstrakte Basisklasse für alle konkreten Produkte.

Die Ausgaben des '*Real-World*'-Beispiels lauten:

```
Model: Ford Focus
  Engine: 1.0 L EcoBoost I3
  Body: 5-door hatchback
  Doors: 5
  Transmission: 6-speed PowerShift automatic
  Accessories:
    Car Cover

Model: Ford GT1
  Engine: 5.4 L Supercharged Modular V8
  Body: Roadster
  Doors: 2
  Transmission: 6-speed manual
  Accessories:

Model: Ford Explorer
  Engine: 4.0 L Cologne V6
  Body: SUV
  Doors: 5
  Transmission: 5-speed M50D-R1 manual
  Accessories:
    Car Cover
    Sun Shade

Model: Mitsubishi I
  Engine: 659 cc DOHC MIVEC
  Body: Kei car
  Doors: 5
  Transmission: 6-speed automatic
  Accessories:

Model: Mitsubishi Lancer Evo IX
  Engine: 4B10 1.8 L DOHC I4
  Body: 4-door sedar
  Doors: 4
  Transmission: 6-speed twin-clutch transmission
  Accessories:

Model: Mitsubishi Pajero Super Exceed
  Engine: 6G75 3.8 V6
  Body: SUV
  Doors: 5
  Transmission: 5-speed manual
  Accessories:
```

Das Beispiel ist portiert von C# nach C++ bzgl. der Vorlage unter

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#AbstractFactory)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
