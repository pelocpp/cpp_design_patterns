# Abstract Factory

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Abstract Factory* Pattern ist ein Entwurfsmuster,
mit dem Gruppen miteinander verwandter Objekte erstellt werden k�nnen,
ohne dass die genauen konkreten Klassen angegeben werden m�ssen, die dabei verwendet werden.
Eine von mehreren Factory-Klassen generiert die jeweiligen Objekte.

#### Problem:

Dieses Muster ist sehr gut, wenn Sie die Details der Objektinstanziierung trennen m�chten.
Im Allgemeinen haben Fabriken mehr als eine Factory-Methode.
Jede Factory-Methode kapselt den `new`-Operator und die konkreten, plattformspezifischen Klassen.
Jede Plattform wird dann von einer Klasse repr�sentiert, die sich von einer der Fabriken ableitet.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Abstract Factory Patterns*.
Es besteht im Wesentlichen aus f�nf Teilen:

  * **Client**: Ein Client benutzt ausschlie�lich Methoden der beiden (abstrakten)
    Klassen `AbstractFactory` und `AbstractProduct`.
  * **AbstractFactory**: Abstrakte Basisklasse f�r alle konkreten Factory-Klassen, die miteinander verwandte Objekte erzeugen.
    F�r jeden Objekttyp, der instanziiert wird, ist eine Methode enthalten.
  * **ConcreteFactory**: Diese Klasse leitet sich von `AbstractFactory` ab.
    `ConcreteFactory` �berschreibt die Methoden von `AbstractFactory`, die neue miteinander verwandte Objekte generieren.
  * **AbstractProduct**: Basisklasse f�r alle Arten von Objekten, die von einer Factory erstellt werden k�nnen.
  * **ConcreteProduct**: Konkrete Implementierung der `AbstractProduct`-Klasse.
    Es kann nat�rlich mehrere Klassen geben, die sich von der `AbstractProduct`-Klasse mit jeweils
    spezifischer Funktionalit�t ableiten.

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

Ein Klassiker f�r dieses Entwurfsmuster ist die Java Swing Oberfl�chenbibliothek und hier im
Speziellen der Aspekt "*Look and Feel*".
F�r Oberfl�chensteuerelemente wie Listen, Comboboxen oder Eingabefelder gibt es hier verschiedene Varianten.
Diese Varianten sind in ihrer Grundfunktionalit�t gleich, unterscheiden sich aber in ihrem Aussehen
und teilweise auch in ihrem Verhalten.

<img src="dp_abstract_factory_pattern_ui_factory.svg" width="700" />

*Abbildung* 1: Eine abstrakte Fabrik f�r die Hantierung unterschiedlicher graphischer Steuerelemente.

F�r jedes *Look and Feel* gibt es eine eigene Familie an graphischen Steuerelementen und damit
eine eigenen Fabrik. Abstrahiert werden all diese Fabriken durch eine zentral definierte abstrakte Fabrik.
Nur um einen Eindruck zu erhalten, finden Sie in Tabelle 1 eine - nicht vollst�ndige - Auflistung
der unterschiedlichen Bibliotheken, also sprich konkreten UI-Fabriken vor:

| Plattform | Look and Feel |
|:-------------- |----|
| Cross Platform Look And Feel | Metal |
| Solaris, Linux with GTK+ 2.2 or later | GTK+ |
| Other Solaris, Linux | Motif | 
| Classic Windows | Windows | 
| HP UX | HP* | 

Tabelle 1: Verf�gbare *Look and Feel* UI-Fabriken.

---

#### Hinweis:

Die beiden Entwurfsmuster *Abstract Factory* und *Factory Method* sind nicht 
miteinander zu verwechseln.

Sie haben zumindest gemeinsam, dass sie beide den Client von konkreten Typen entkoppeln.
Der Client kennt nur die Schnittstelle zur *Factory* und den Produkten. Welche Produkte konkret erstellt werden,
entscheidet die Unterklasse/Implementierung der Schnittstelle. Der Client st�tzt sich allein auf Abstraktion.

*Hauptunterschied*:

  * Der Hauptunterschied zwischen einer *Factory-Methode* und einer *abstrakten Factory* besteht darin,
  dass die Factory-Methode eine *Methode* und eine abstrakte Factory ein *Objekt* ist.

  * Da die Factory-Methode nur eine Methode ist, kann sie in einer Unterklasse �berschrieben werden.

  * Die abstrakte Fabrik ist ein Objekt, das �ber mehrere Fabrikmethoden verf�gt.

Damit zu weiteren Unterschieden auf Detailebene:

**Abstract Factory**<br/>
  * Bietet eine Schnittstelle zum Erstellen von Familien verwandter oder abh�ngiger Objekte, ohne deren konkrete Klassen anzugeben.
  * Ganze Produktfamilie wird erstellt.
  * Breite Schnittstelle.
  * Schnittstelle (Abstract Factory) ist oft nur ein Interface und enth�lt keinen Implementierungscode.

**Factory Method**<br/>
  * Definiert eine Schnittstelle zum Erstellen eines Objekts, aber l�sst
    die Unterklassen entscheiden, welche Klasse instanziiert werden soll.
    Mit dem *Factory Method Pattern* kann eine Klasse die Instanziierung auf Unterklassen verschieben.
  * Schmale Schnittstelle.
  * Schnittstelle ist oft abstrakt und enth�lt generischen Code (Herstellungscode, den alle Produkte durchlaufen m�ssen).

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
`IVehicleFactory` verf�gt �ber eine Methode `create`,
mit der `Vehicle`-Objekte zur�ckgegeben werden.
Die Klasse `Vehicle` ist eine abstrakte Basisklasse f�r alle konkreten Produkte.

---

## Literaturhinweise

Das Beispiel ist portiert von C# nach C++ bzgl. der Vorlage unter

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#AbstractFactory).

Ein Beispiel zu verschiedenen Themes und grafischen Steuerelementen kann man
[hier](https://medium.com/@lokeshbihani99/abstract-factory-pattern-in-c-f0ed420fc9fb)
nachlesen.

Das Beispiel zu Fahrr�dern, Autos und Trucks stammt aus diesem [Artikel](https://medium.com/@kamresh485/abstract-factory-pattern-in-c-ddc98f547801).


---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
