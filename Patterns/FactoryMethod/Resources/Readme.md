# Factory Method Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Factory Method Pattern* ist ein Entwurfsmuster, mit dem Objekte erstellt werden können,
ohne den Objekttyp anzugeben, der hierzu verwendet werden soll.
Das Entwurfsmuster definiert zuallererst eine Methode, die ein Objekt erzeugt.
Welche Klasse hierbei herangezogen wird, entscheidet die konkrete Klasse, die diese Methode implementiert.


#### *Virtual Constructor*:

Dieses Entwurfsmuster ist auch unter dem Namen *Virtual Constructor* bekannt, dazu später noch mehr.

#### Beispiele:


Jeder Container der Standard Template Library verfügt über acht Factory-Funktionen zum Generieren verschiedener Iteratoren.

  * `begin`, `cbegin`: Gibt einen Iterator bzgl. des Anfangs des Containers zurück.
  * `end`, `cend`: Gibt einen Iterator bzgl. des Endes des Containers zurück.
  * `rbegin`, `crbegin`: Gibt einen Reverse-Iterator bzgl. des Anfangs des Containers zurück.
  * `rend`, `crend`: Gibt einen Reverse-Iterator bzgl. des Endes des Containers zurück.

Die mit `c` beginnenden Fabrikfunktionen geben konstante Iteratoren zurück.


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

#### *Virtual Constructor Idiom*:

Das *Factory Method* Muster wird auch als *Virtual Constructor* Pattern bezeichnet.
Dieses Idiom bringt zum Ausdruck, dass der Client mit einem Konstruktor ein Objekt erzeugt, dessen Typ er nicht kennt.
Der gesamte Zweck dieser Redewendung besteht darin, das Klonen eines Objekts über einen Basisklassenzeiger zu ermöglichen.
Hier ist ein Beispiel:

```cpp
01: // Product
02: class Window {
03: public:
04:     virtual Window* create() = 0;
05:     virtual Window* clone() = 0;
06:     virtual ~Window() {};
07: };
08: 
09: // Concrete Products 
10: class DefaultWindow : public Window {
11:     DefaultWindow* create() override {
12:         std::cout << "Create DefaultWindow" << std::endl;
13:         return new DefaultWindow();
14:     }
15:     DefaultWindow* clone() override {
16:         std::cout << "Clone DefaultWindow" << std::endl;
17:         return new DefaultWindow(*this);
18:     }
19: };
20: 
21: class FancyWindow : public Window {
22:     FancyWindow* create() override {
23:         std::cout << "Create FancyWindow" << std::endl;
24:         return new FancyWindow();
25:     }
26:     FancyWindow* clone() override {
27:         std::cout << "Clone FancyWindow" << std::endl;
28:         return new FancyWindow(*this);
29:     }
30: };
31: 
32: // Concrete Creator or Client                             
33: Window* createWindow(Window& oldWindow) {
34:     return oldWindow.create();
35: }
36: 
37: Window* cloneWindow(Window& oldWindow) {
38:     return oldWindow.clone();
39: }
40: 
41: void test_virtual_constructor_idiom()
42: {
43:     DefaultWindow defaultWindow;
44:     FancyWindow fancyWindow;
45: 
46:     Window* defaultWindow1 = createWindow(defaultWindow);
47:     Window* fancyWindow1 = createWindow(fancyWindow);
48: 
49:     Window* defaultWindow2 = cloneWindow(defaultWindow);
50:     Window* fancyWindow2 = cloneWindow(fancyWindow);
51: 
52:     delete defaultWindow1;
53:     delete fancyWindow1;
54:     delete defaultWindow2;
55:     delete fancyWindow2;
56: }
```

*Beachte*: Die Klasse `Window` unterstützt jetzt zwei Möglichkeiten, neue `Window`-Objekte zu erstellen:
ein standardmäßig konstruiertes Fensterobjekt mit der Member-Funktion `create` (Zeile 34)
und ein kopiert konstruiertes Fensterobjekt mit der Member-Funktion `clone` (Zeile 37).

Ein subtiler Unterschied besteht darin, dass die `clone`-Methode den `this`-Zeiger verwendet (Zeile 28). 

---

#### Hinweis:

Die beiden Entwurfsmuster *Simple Factory* und *Factory Method* sind nicht 
miteinander zu verwechseln.

**Simple Factory**<br/>
  * Mit dem *Simple Factory* Pattern versuchen wir, die Details in der Erstellung eines Objekts vor dem Anrufer (Client) zu abstrahieren.
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

Das Beispiel zum *Virtual Constructor Idiom* stammt aus

[Stackoverflow: Virtual constructor idiom and factory design](https://stackoverflow.com/questions/11574075/virtual-constructor-idiom-and-factory-design)


Ein zweites Beispiel zum *Virtual Constructor Idiom* ist

[Factory Method](https://www.modernescpp.com/index.php?option=com_content&view=article&id=657&catid=58)

entnommen.


---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
