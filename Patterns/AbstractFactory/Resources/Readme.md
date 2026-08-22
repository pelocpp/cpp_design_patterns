# Abstract Factory

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

###### In einem Satz:

> &bdquo;Das Abstract Factory Pattern kapselt die Erzeugung zusammengehöriger Objekte einer Produktfamilie, ohne dass der Client deren konkrete Klassen kennen muss.&rdquo;

Das *Abstract Factory Pattern* gehört zur Kategorie der Erzeugungsmuster (*Creational Patterns*) und wird eingesetzt,
wenn ein System von der konkreten Implementierung der Objekte, die es verwendet,
entkoppelt werden soll.

Anstatt Objekte direkt mit `new` zu instanziieren, delegiert der Client die Objekterzeugung
an eine abstrakte Fabrik-Schnittstelle. Für jede &bdquo;Produktfamilie&bdquo; &ndash; also eine Gruppe von Objekten,
die thematisch oder funktional zusammengehören und typischerweise gemeinsam verwendet werden &ndash; gibt es eine
konkrete Fabrik-Implementierung.

Dadurch lässt sich zur Laufzeit oder Kompilierzeit entscheiden, welche Produktfamilie tatsächlich verwendet wird,
ohne dass der übrige Code angepasst werden muss.

Ein klassisches Beispiel ist eine GUI-Bibliothek, die je nach Betriebssystem passende Buttons, Checkboxen und Fenster erzeugt,
wobei sichergestellt wird, dass innerhalb einer Anwendung nur Elemente eines einzigen, konsistenten Stils gemischt werden.

Der große Vorteil liegt in der losen Kopplung:
Der Client arbeitet ausschließlich mit abstrakten Schnittstellen (abstrakte Fabrik und abstrakte Produkte)
und bleibt so unabhängig von konkreten Klassen.

In C++ wird dies typischerweise über abstrakte Basisklassen mit rein virtuellen Methoden umgesetzt,
wobei die konkreten Fabriken und Produkte davon erben.
Neue Produktfamilien lassen sich so relativ einfach hinzufügen (Open/Closed-Prinzip),
während das Hinzufügen neuer Produktarten innerhalb einer bestehenden Familie tendenziell aufwendiger ist,
da dann alle Fabriken angepasst werden müssen.


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
Working on Concrete Product A1
Working on Concrete Product B1

Client: Testing the same client code with the second factory type:
Working on Concrete Product A2
Working on Concrete Product B2
```

---

#### &bdquo;Real-World&rdquo; Beispiel:

Ein Klassiker für dieses Entwurfsmuster ist die Java Swing Oberflächenbibliothek und hier im
Speziellen der Aspekt "*Look and Feel*".
Für Oberflächensteuerelemente wie Listen, Comboboxen oder Eingabefelder gibt es hier verschiedene Varianten.
Diese Varianten sind in ihrer Grundfunktionalität gleich, unterscheiden sich aber in ihrem Aussehen
und teilweise auch in ihrem Verhalten.

<img src="dp_abstract_factory_pattern_ui_factory.svg" width="700" />

*Abbildung* 1: Eine abstrakte Fabrik für die Hantierung unterschiedlicher graphischer Steuerelemente.

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

---

#### Ein Vergleich


|                     | Simple Factory        | Factory Method            | Abstract Factory                       |
| ------------------- | --------------------- | ------------------------- | -------------------------------------- |
| Ziel                | Objekt erzeugen       | Erzeugung variabel machen | Produktfamilie erzeugen                |
| Anzahl Produktarten | typischerweise eine   | typischerweise eine       | **mehrere**                            |
| Factory-Hierarchie  | nein                  | **ja**                    | **ja**                                 |
| Polymorphe Factory  | nein                  | ja                        | ja                                     |
| Auswahlmechanismus  | z. B. `switch`        | virtuelle Factory Method  | virtuelle Factory Methods              |
| Beispiel            | `createProduct(type)` | `createProduct()`         | `createButton()`, `createCheckbox()`   |
| Hauptidee           | zentrale Erzeugung    | Erzeugung delegieren      | **kompatible Produktfamilie erzeugen** |


Man kann die Unterscheidung der drei Muster auch durch die Formulierung einer Frage hervorheben:

  * Simple Factory: Welches Produkt soll ich erzeugen?
  * Factory Method: Welche konkrete Factory soll die Erzeugung übernehmen?
  * Abstract Factory: Welche zusammengehörige Produktfamilie soll ich erzeugen?


Noch ein paar Aussagen zu den beiden Mustern *Abstract Factory* und *Factory Method*:

Sie haben gemeinsam, dass sie beide den Client von konkreten Typen entkoppeln.
Der Client kennt nur die Schnittstelle zur *Factory* und den Produkten. Welche Produkte konkret erstellt werden,
entscheidet die Unterklasse/Implementierung der Schnittstelle. Der Client stützt sich allein auf Abstraktion.

*Hauptunterschied*:

  * Der Hauptunterschied zwischen einer *Factory-Methode* und einer *abstrakten Factory* besteht darin,
  dass die Factory-Methode eine *Methode* und eine abstrakte Factory ein *Objekt* ist.

  * Da die Factory-Methode nur eine Methode ist, kann sie in einer Unterklasse überschrieben werden.

  * Die abstrakte Fabrik ist ein Objekt, das über mehrere Fabrikmethoden verfügt.

Damit zu weiteren Unterschieden auf Detailebene:

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

---

#### Zweites &bdquo;Real-World&rdquo; Beispiel:

Im &bdquo;Real-World&rdquo; Beispiel zu diesem Entwurfsmuster wird
die Herstellung verschiedener Fahrzeugtypen verschiedener Hersteller betrachtet.
Es gibt eine abstrakte Fabrikschnittstelle namens `IVehicleFactory` (*Abstract Factory*)
und drei konkrete Fabrikimplementierungen namens `BikeFactory`, `CarFactory` und `TruckFactory`. 
`IVehicleFactory` verfügt über eine Methode `create`,
mit der `Vehicle`-Objekte zurückgegeben werden.
Die Klasse `Vehicle` ist eine abstrakte Basisklasse für alle konkreten Produkte.

---

## Literaturhinweise

Das Beispiel ist portiert von C# nach C++ bzgl. der Vorlage unter

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#AbstractFactory).

Ein Beispiel zu verschiedenen Themes und grafischen Steuerelementen kann man
[hier](https://medium.com/@lokeshbihani99/abstract-factory-pattern-in-c-f0ed420fc9fb)
nachlesen.

Das Beispiel zu Fahrrädern, Autos und Trucks stammt aus diesem [Artikel](https://medium.com/@kamresh485/abstract-factory-pattern-in-c-ddc98f547801).


---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
