# Factory Method Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Erstellung von Objekten auf Basis einer Schnittstelle in einer Oberklasse,
die es den Unterklassen aber erlaubt, den Typ der zu erstellenden Objekte zu ändern.&rdquo;

Das *Factory Method Pattern* ist ein Entwurfsmuster, mit dem Objekte erstellt werden können,
ohne den Objekttyp anzugeben, der hierzu verwendet werden soll.
Das Entwurfsmuster definiert zuallererst eine Methode, die ein Objekt erzeugt.
Welche Klasse hierbei herangezogen wird, entscheidet die konkrete Klasse, die diese Methode implementiert.

Zum Erstellen des Objekts wird eine Schnittstelle benötigt.
Die Unterklassen entscheiden, welche Klasse instanziiert werden soll.
Mit dem *Factory Method Pattern* kann eine Klasse die Instanziierung auf Unterklassen verschieben.

**Konsequenz**: *Factory Methoden* verhindern, dass anwendungsspezifische Klassen
in der Anwendung in Erscheinung treten. 

#### Lösung:

Das *Factory*-Entwurfsmuster definiert eine Schnittstelle zum Erstellen eines Objekts
und überlässt die Auswahl des konkreten Klassentyps den Unterklassen.
Das Entwurfsmuster macht ein Software-Design leichter anpassbar und weniger abhängig 
von anderen Klassen.

In dem Muster kommen zwei Vererbungshierarchien vor: eine mit den *Factory*-Klassen und
eine zweite mit den zu erzeugenden Objekten. Diese werden in dem Muster häufig als *Produkte* bezeichnet.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Factory Method Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **FactoryBase**: Abstrakte Klasse (oder Schnittstelle) für konkrete *Factory*-Klassen,
    die die gesuchten Objekte zurückgeben.
    Diese Klasse enthält die Signatur der Methode `FactoryMethod`,
    die ein `ProductBase`-Objekt zurückliefert.
  * **ConcreteFactory**: Repräsentiert eine konkrete Umsetzung der `FactoryBase`-Klasse.
    Normalerweise überschreibt diese Klasse die generierende Methode
    `FactoryMethod` und gibt ein `ConcreteProduct`-Objekt zurück.
  * **ProductBase**: Basisklasse (oder Schnittstelle) für alle Produkte,
    die von konkreten *Factory*-Klassen hergestellt werden.
  * **ConcreteProduct**: Konkrete Implementierung der Klasse `ProductBase`.
    Konkrete `ProductBase`-Klassen sollten produktspezifische
    Funktionalitäten enthalten. Objekte des Typs `ConcreteProduct` werden von Methoden
    der *Factory*-Klassen erstellt.

<img src="dp_factory_method_pattern.svg" width="500">

*Abbildung* 1: Schematische Darstellung des *Factory Method Patterns*.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfaches Beispiel

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Beispiel, das "konzeptionell" den Einsatz von *Factory Methods* aufzeigt.

---

#### Beispiele:


Jeder Container der Standard Template Library verfügt über acht Factory-Funktionen zum Generieren verschiedener Iteratoren.

  * `begin`, `cbegin`: Gibt einen Iterator bzgl. des Anfangs des Containers zurück.
  * `end`, `cend`: Gibt einen Iterator bzgl. des Endes des Containers zurück.
  * `rbegin`, `crbegin`: Gibt einen Reverse-Iterator bzgl. des Anfangs des Containers zurück.
  * `rend`, `crend`: Gibt einen Reverse-Iterator bzgl. des Endes des Containers zurück.

Die mit `c` beginnenden Fabrikfunktionen geben konstante Iteratoren zurück.

---


#### 'Real-World' Beispiel:

[Quellcode 3](../RealWorldFactoryMethod.cpp) - *Real-World*-Beispiel (`ITelevision`), das exemplarisch mehrere *Factory Methods* betrachtet.<br/>

In *Quellcode 3* findet sich ein Programm mit den Klassen `ITelevision`, `LEDTelevision`, `OledTelevision`,
`AbstractTVFactory`, `LEDTVFactory` und `OledTVFactory` vor.
Studieren Sie die Methoden `manufactureTelevision`, `assembleTelevision`, `shippingCharge` 
und `productionCharge` der Klasse `AbstractTVFactory`.
Beschreiben Sie, wie diese Methoden zur Namensgebung des *Factory Method Patterns* beitragen.

<img src="dp_factory_method_pattern_television.svg" width="900">

*Abbildung* 2: Das *Factory Method Pattern* am Beispiel der Produktion von Fernsehgeräten.

---

#### Hinweis:

Die beiden Entwurfsmuster *Simple Factory* und *Factory Method* sind nicht 
miteinander zu verwechseln.

**Simple Factory**<br/>
  * Mit dem *Simple Factory* Pattern versuchen wir, die Details in der Erstellung eines Objekts vor dem Aufrufer (Client) zu abstrahieren.
    Das einzige, was der Client weiß, indem er eine Methode aufruft und den gewünschten Parameter übergibt, ist,
    dass er ein Objekt eines bestimmten Typs erhält. Aber wie dieses Objekt erstellt wird, weiß der Client-Code nicht.

**Factory Method**<br/>
  * Das *Factory Method* Pattern bietet sich an, wenn die Anforderungen an die Erstellung eines Objekts mehr als nur der Aufruf des `new`-Operators sind.
    Sind zur Erzeugung des Objekts mehrere Schritte notwendig, möchte man diese Schritte ggf. anpassen können
    oder sind diese Schritte bei verschiedenen Objekten unterschiedlich, verwendet man das *Factory Method* Pattern.
  * Oder anders ausgedrückt: 
    Gibt es einen Algorithmus / eine Strategie, um die Erzeugung einer Produktfamilie zu steuern,
    dann kommt das *Factory Method* Pattern in Betracht. Dieses lässt sich gut mit dem *Template Pattern*, oder auch *Strategy Pattern* kombinieren,
    da man mit einer Schablone (Template) die Schritte zum Erstellen des untergeordneten Elements abstrahieren kann.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/factory-method/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#FactoryMethod)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
