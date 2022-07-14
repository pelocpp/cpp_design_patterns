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

#### Ein weiterer Anwendungsfall des Factory Method Patterns:

Das Factory Method Pattern kommt auch dann zum Zuge, wenn es viele unterschiedene Möglichkeiten gibt,
ein Objekt zu konstruieren, dies aber die Ursache von Fehlerquellen sein kann:

*Beispiel*:

```cpp
01:     struct Point {
02:         Point(double x, double y) { /*...*/ }        // Cartesian coordinates
03:         // ... Implementation
04: 
05:         // Not OK: Cannot overload with same type of arguments
06:         // 
07:         // Point(double a, double b){ /*...*/ }      // Polar coordinates
08:         // ... Implementation
09:     };
```

Zwei Konstruktoren in einer Klasse mit identischer Signatur, aber unterschiedlich Bedeutung ist nicht möglich.
Eine mögliche Abhilfe könnte so aussehen:

```cpp
01: enum class PointType { cartesian, polar };
02: 
03: class Point
04: {
05: public:
06:     Point(double a, double b, PointType type = PointType::cartesian)
07:     {
08:         if (type == PointType::cartesian) {
09:             m_x = a;
10:             m_y = b;
11:         }
12:         else {
13:             m_x = a * cos(b);
14:             m_y = a * sin(b);
15:         }
16:     }
17: 
18: private:
19:     double m_x;
20:     double m_y;
21: };
```

Dies ist jedoch keine sehr einfallsreiche Vorgehensweise, das Problem auf diese Weise zu lösen.
Wir sollten vielmehr die jeweilige Instanziierung an separate Methoden delegieren:

```cpp
```

Wie man an der Implementierung beobachten kann, wird der explizite Gebrauch des Konstruktors
untersagt. Der Benutzer wird stattdessen gezungen, statische Methoden (Klassenmethoden) zu verwenden.

Auch das ist eine Essenz des *Factory Method* Patterns:

  * Umstellung auf private Konstruktor und Bereitstellung von Klassenmethoden.


---

#### *Virtual Constructor Idiom*:

Das *Factory Method* Muster wird auch als *Virtual Constructor* Pattern bezeichnet.
Dieses Idiom bringt zum Ausdruck, dass der Client mit einem Konstruktor ein Objekt erzeugt, dessen Typ er nicht kennt.
Der gesamte Zweck dieser Redewendung besteht darin, das Klonen eines Objekts über einen Basisklassenzeiger zu ermöglichen.
Hier ist ein Beispiel:

```cpp
class Base
{
public:
    Base() {}
    virtual ~Base() {}

    // the "Virtual Constructor"
    static Base* Create(int id);

    // the "Virtual Copy Constructor"
    virtual Base* Clone() = 0;

    virtual void printMe() = 0;
};

class Derived1 : public Base
{
public:
    Derived1()
    {
        std::cout << "default c'tor Derived1" << std::endl;
    }

    Derived1(const Derived1& rhs)
    {
        std::cout << "copy c'tor Derived1" << std::endl;
    }

    ~Derived1()
    {
        std::cout << "c'tor Derived1" << std::endl;
    }

    virtual Base* Clone() override
    {
        return new Derived1(*this);
    }

    virtual void printMe() override
    {
        std::cout << "I'm a Derived1" << std::endl;
    }
};

// dto. Derived2

// static method
Base* Base::Create(int id)
{
    if (id == 1)
    {
        return new Derived1();
    }
    else
    {
        return new Derived2();
    }
}

// global function
Base* CreateCopy(Base* pBase)
{
    return pBase->Clone();
}

void test_virtual_constructor_idiom()
{
    using namespace VirtualConstructorIdiom;

    std::cout << "Enter Id (1 or 2): ";
    int input;
    std::cin >> input;
    Base* pBase = Base::Create(input);
    Base* pCopy = CreateCopy(pBase);

    // dont know what object is created but still access functions through base pointer
    pBase->printMe();
    pCopy->printMe();

    delete pBase;
    delete pCopy;
}
```

*Beachte*: Der Client kennt den von `Base` geerbten Klassentyp nicht, ruft aber Methoden an diesem Objekt auf!

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

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/factory-method/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#FactoryMethod)

vor.

Das Beispiel zum *Virtual Constructor Idiom* stammt aus

[Stackoverflow: Virtual constructor idiom and factory design](https://stackoverflow.com/questions/11574075/virtual-constructor-idiom-and-factory-design)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
