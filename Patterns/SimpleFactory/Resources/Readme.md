# Simple Factory Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Erstellung von Objekten, ohne dem Client die Erstellungslogik zur Verf�gung zu stellen.&rdquo;

Das *Simple Factory Pattern* ist eine Vorgehensweise, Objekte zu erstellen,
ohne die Erstellungslogik dem Client zur Verf�gung zu stellen.
Das *Simple Factory Pattern* wird im eigentlichen Sinne *nicht* als Entwurfsmuster bezeichnet.

---

#### Struktur (UML):

*Bemerkung*:<br />

Nach dem *Separation of Concerns*-Prinzip sollte die Objekterstellung bzw. -beschaffung
von den dom�nenspezifischen Aufgaben, die ein Objekt hat, getrennt werden.

Eigentlich haben wir hierzu schon eine Vorgehensweise kennen gelernt:

Das Prinzip der *Dependency Injection*.

Das *Dependency Injection* folgt diesem Prinzip in der Gestalt,
dass der gesamte Objekterstellungs- und Abh�ngigkeitsaufl�sungsprozess
in einem Infrastrukturelement zentralisiert ist und sich die Objekte selbst nicht darum k�mmern m�ssen.

*Vorsicht*:<br />
Was tun wir, wenn ein Objekt irgendwann zur Laufzeit dynamisch erstellt werden muss?

An dieser Stelle kommen Objektfabriken ins Spiel!

Das folgende UML-Diagramm beschreibt eine Implementierung des *Simple Factory Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **ProductBase**: Basisklasse (oder Schnittstelle) f�r alle Produkte,
    die von der *Factory*-Klasse hergestellt werden sollen. Die Schnittstelle beschreibt eine oder mehrere Methoden,
    die von den konkreten Ableitungen der Klasse implementiert werden.
  * **ConcreteProduct**: Konkrete Implementierung der Klasse `ProductBase`.
    Objekte des Typs `ConcreteProduct` werden von der Klasse *Factory* erzeugt.
  * **Factory**: Diese Klasse besitzt eine Methode `getProduct`,
    die Objekte zur�ckliefert, die die `ProductBase`-Schnittstelle implementieren.
    �ber einen Parameter der `getProduct`-Methode wird typischerweise gesteuert, welches `ConcreteProduct` Objekt zu erzeugen ist.

<img src="dp_factory_pattern.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Factory Patterns*.

---

*Hinweis*:

Das UML-Diagramm aus *Abbildung* 1 kann in Sprachen wie C++ nicht immer auf genau diese Weise umgesetzt werden.
C++ ist &ndash; im Gegensatz zu vielen anderen Sprachen &ndash; konzeptionell

  * *Wert*- und
  * *Referenz*-basiert.

Objekte in C++ k�nnen sowohl am Stack (direkt erreichbar / als *Wert*) als auch auf der Halde
(indirekt erreichbar �ber einen *Zeiger*) liegen.
Was bedeutet das: M�chte eine Fabrik-Methode ein Objekt per *Value* zur�ckgeben, ist dies nicht
mit einer Umsetzung des Schnittstellenkonzepts m�glich. Siehe hierzu den folgenden Anwendungsfall.

---


#### Erster Anwendungsfall des *Simple Factory* Patterns:

Das *Simple Factory* Pattern kommt beispielsweise zum Zuge, wenn es

  * viele unterschiedliche M�glichkeiten gibt, ein Objekt zu konstruieren und
  * dies aber die Ursache von Fehlerquellen sein kann.

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

Zwei Konstruktoren in einer Klasse `Point` mit identischer Signatur,
aber unterschiedlicher Bedeutung:
Dies ist nicht m�glich, eine Abhilfe k�nnte so aussehen:

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

Dies ist jedoch keine sehr einfallsreiche Vorgehensweise, das Problem auf diese Weise zu l�sen.
Wir sollten vielmehr die jeweilige Instanziierung an separate Methoden delegieren:

```cpp
01: class Point
02: {
03: private:
04:     double     m_x;
05:     double     m_y;
06:     PointType  m_type;
07: 
08:     // private constructor, so that object can't be created directly
09:     Point(const double x, const double y, PointType t) 
10:         : m_x{ x }, m_y{ y }, m_type{ t } {}
11: 
12: public:
13:     friend std::ostream& operator<<(std::ostream& os, const Point& obj) {
14:         return os << "x: " << obj.m_x << " y: " << obj.m_y;
15:     }
16: 
17:     static Point NewCartesian(double x, double y) {
18:         return { x, y, PointType::cartesian };
19:     }
20: 
21:     static Point NewPolar(double a, double b) {
22:         return { a * cos(b), a * sin(b), PointType::polar };
23:     }
24: };
```

Wie man an der Implementierung beobachten kann, wird der explizite Gebrauch des Konstruktors
untersagt. Der Benutzer wird stattdessen gezwungen, statische Methoden (Klassenmethoden) zu verwenden:

```cpp
Point p{ Point::NewPolar(5.0, M_PI / 4) };
```

Jetzt haben wir die Funktionalit�ten zweier *Concerns* in eine Klasse gepackt:
Die von der Klasse `Point` als auch die ihrer Fabrik. Wir sollten den Codeanteil der Fabrik
in eine dedizierte Klasse verlagern. So f�hlen wir uns auch besser, 
was unsere Bedenken bzgl. des *Single Responsibility Principles* der SOLID-Designprinzipien anbelangt:

```cpp
01: class Point
02: {
03:     friend class PointFactory;
04: 
05: private:
06:     double m_x;
07:     double m_y;
08: 
09:     ...
10: };
11: 
12: class PointFactory
13: {
14: public:
15:     static Point NewCartesian(double x, double y) {
16:         return { x, y, PointType::cartesian };
17:     }
18: 
19:     static Point NewPolar(double a, double b) {
20:         return { a * cos(b), a * sin(b), PointType::polar };
21:     }
22: };
```

Auch hier gibt es noch die M�glichkeit einer Verfeinerung bzw. einer Stolperfalle:
Der Gebrauch des `friend`-Schl�sselworts ist h�ufig ein Indikator,
dass gegen das *Open-Closed-Prinzip* versto�en wird.


#### *Inner Factory*:

Wir machen eine kritische Beobachtung, die wir in unserer Factory-Klasse �bersehen haben:
Es gibt keine wirkliche Verbindung zwischen den beiden Klassen `PointFactory` und `Point`!

Warum m�ssen wir eine Fabrik �berhaupt au�erhalb der betroffenen Klasse entwerfen?
Wir k�nnten diese in die `Point`-Klasse integrieren (in einer so genannten *nested class*)
und den Benutzer auf diese Weise ermutigen, die Fabrik (sog. *Inner Factory*) zu verwenden.

```cpp
01: class Point
02: {
03: private:
04:     double m_x;
05:     double m_y;
06: 
07:     Point(double x, double y) : m_x{ x }, m_y{ y } {}
08: 
09: public:
10:     struct Factory
11:     {
12:         static Point NewCartesian(double x, double y) { 
13:             return { x,y };
14:         }
15: 
16:         static Point NewPolar(double r, double theta) { 
17:             return{ r * cos(theta), r * sin(theta) };
18:         }
19:     };
20: };
```

Anwendung:

```cpp
Point p{ Point::Factory::NewCartesian(2, 3) };
```

---

#### Die Essenz des *Simple Factory* Patterns:

> Umstellung auf private Konstruktoren und Bereitstellung von Klassenmethoden.

---


#### Zweiter Anwendungsfall des *Simple Factory* Patterns: &bdquo;What's wrong with `new`?&rdquo;
  
Technisch betrachtet ist mit `new` nichts falsch &ndash;
in keinster Weise. Das Problem ist eher, dass im Falle
einer Hierarchie von Klassen und Schnittstellen der 
Anwender m�glicherweise mehr Kenntnisse der Schnittstellen hat &ndash;
und damit weniger von den realen Klassen, die diese
Schnittstellen implementieren.

Ein Beispiel hierzu:

```cpp
01: class IPizza
02: {
03: public:
04:     virtual void prepare() = 0;
05:     virtual void bake() = 0;
06:     virtual void cut() = 0;
07:     virtual void box() = 0;
08: };
09: 
10: static std::shared_ptr<IPizza> orderPizza()
11: {
12:     std::shared_ptr<IPizza> pizza{ std::make_shared<Pizza>()};
13: 
14:     pizza->prepare();
15:     pizza->bake();
16:     pizza->cut();
17:     pizza->box();
18: 
19:     return pizza;
20: }
```

Das liest sich nicht schlecht, nur es gibt doch
mehrere Arten von Pizzas:

```cpp
01: static std::shared_ptr<IPizza> orderPizza(std::string type)
02: {
03:     std::shared_ptr<IPizza> pizza{ nullptr };
04: 
05:     if (type == std::string{ "cheese" }) {
06:         pizza = std::make_shared<CheesePizza>();
07:     }
08:     else if (type == std::string{ "greek" }) {
09:         pizza = std::make_shared<GreekPizza>();
10:     }
11:     else if (type == std::string{ "pepperoni" }) {
12:         pizza = std::make_shared<PepperoniPizza>();
13:     }
14: 
15:     if (pizza != nullptr) {
16: 
17:         pizza->prepare();
18:         pizza->bake();
19:         pizza->cut();
20:         pizza->box();
21:     }
22: 
23:     return pizza;
24: }
```

Das ist jetzt schon besser. Nur wie entwickelt sich die Funktion
`orderPizza` weiter, wenn es neue Pizzavarianten gibt und 
andere, weniger erfolgreiche Pizzavarianten aus dem Sortiment
genommen werden. Dann wird die Wartung und Pflege dieser Methode
 `orderPizza` unangenehm.

Wie w�re es, wenn wir die Objekterzeugung des `Pizza`-Objekts
aus der Methode `orderPizza` herausnehmen?

Moment! *Objekterzeugung*. Da sind wir doch beim `new`-Operator angekommen!
Also machen wir die Beobachtung, dass es Sinn ergeben kann,
den Aufruf des `new`-Operators f�r eine Pizza an &bdquo;anderer&rdquo; Stelle
zu platzieren:

```cpp
01: class PizzaFactory
02: {
03: public:
04:     static std::shared_ptr<IPizza> createPizza(std::string type) {
05: 
06:         std::shared_ptr<IPizza> pizza{ nullptr };
07: 
08:         if (type == std::string{ "cheese" }) {
09:             pizza = std::make_shared<CheesePizza>();
10:         }
11:         else if (type == std::string{ "pepperoni" }) {
12:             pizza = std::make_shared<PepperoniPizza>();
13:         }
14:         else if (type == std::string{ "clam" }) {
15:             pizza = std::make_shared<ClamPizza>();
16:         }
17:         else if (type == std::string{ "veggie" }) {
18:             pizza = std::make_shared<VeggiePizza>();
19:         }
20: 
21:         return pizza;
22:     }
23: };
```

Here we are: Die `createPizza`-Methode samt zugeh�riger `PizzaFactory`-Klasse
f�llt in die Rubrik *Simple Factory*.


Damit sieht unsere `orderPizza`-Methode nun so aus:

```cpp
01: std::shared_ptr<IPizza> orderPizzaEx(std::string type)
02: {
03:     std::shared_ptr<IPizza> pizza{ PizzaFactory::createPizza(type) };
04: 
05:     if (pizza != nullptr) {
06: 
07:         pizza->prepare();
08:         pizza->bake();
09:         pizza->cut();
10:         pizza->box();
11:     }
12: 
13:     return pizza;
14: }
```

Diese �berlegungen sollen die Einf�hrung eines &bdquo;Fabrik&rdquo;-Gedankens motivieren.

---

#### Abgrenzung zu anderen Entwurfsmustern:

> Das *Factory Pattern* erstellt seine Objekte im Ganzen im Gegensatz zur *Builder*-Vorgehensweise.
  Hier werden die Objekte st�ckweise erstellt.  

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### Erstes &bdquo;Real-World&rdquo; Example:

Im Quellcode finden Sie ein selbsterkl�rendes Beispiel: *Mobil Phones*

---

#### Zweites &bdquo;Real-World&rdquo; Example:

Wir betrachten ein zweites, konkretes Beispiel,
in dem es um Dokumente unterschiedlichen Formats geht:

```cpp
// non recommendable implementation
std::unique_ptr<IDocument> open(std::string path) 
{
    if (path.ends_with(".pdf"))
        return std::make_unique<PdfDocument>(path);

    if (path.ends_with(".html")) 
        return std::make_unique<HtmlDocument>(path);

    return nullptr;
}
```

Wie gehen wir vor, wenn wir die `open`-Funktion um weitere Dokumentarten wie zum Beispiel
*OdtDocument* erweitern wollen?

Dabei sollten wir das *Open-Closed-Prinzip* nicht au�er Acht lassen!

Eine Simple Factory-Klasse ist hier angesagt. Eine weitere Option vor dem Hintergrund sich st�ndig variierender
Dokumenttypen ist eine Registrierungsfunktionen, die es gestattet, eigene Typen zu registrieren:

```cpp
01: struct IDocument 
02: {
03:     virtual ~IDocument() {}
04:     virtual std::vector<std::string> getText() = 0;
05: };
06: 
07: class PdfDocument : public IDocument 
08: {
09: private:
10:     std::string m_path;
11: 
12: public:
13:     PdfDocument(std::string path) : m_path{ path } {}
14: 
15:     std::vector<std::string> getText() override {
16:         return { "Text from PDF" };
17:     }
18: };
19: 
20: class HtmlDocument : public IDocument 
21: ...
22: 
23: class OdtDocument : public IDocument 
24: ...
25: 
26: template <typename T>
27: using DocumentType = std::unique_ptr<T>;
28: 
29: using Document = DocumentType<IDocument>;
30: 
31: using DocumentReader = std::function<Document(std::string)>;
32: 
33: class DocumentFactory
34: {
35: private:
36:     std::unordered_map<std::string, DocumentReader> m_readers;
37: 
38: public:
39:     void add(const std::string& extension, const DocumentReader& reader) {
40:         m_readers.emplace(extension, reader);
41:     }
42: 
43:     Document open(std::string path) {
44:         auto lastDot = path.find_last_of('.');
45:         if (lastDot != std::string::npos) {
46:             std::string extension = path.substr(lastDot + 1);
47:             DocumentReader& reader = m_readers.at(extension);
48:             Document document = reader(path);
49:             return document;
50:         }
51:         else {
52:             throw std::invalid_argument{ "Trying to open a file with no extension" };
53:         }
54:     }
55: };
```

*Bemerkung*:
In dem Beispiel sind einige Modern C++&ndash;Sprachkonstrukte enthalten:

  * `std::map`-Objekt mit *Callables* (hier: `std::function`-Objekte)
  * Lambdas mit *Trailing Return Types*

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[Factory Method vs. Simple Factory](https://dzone.com/articles/factory-method-vs-simple-factory-1)

und 

[Factory vs Factory Method vs Abstract Factory](https://medium.com/bitmountn/factory-vs-factory-method-vs-abstract-factory-c3adaeb5ac9a)

vor.

Das zweite &bdquo;Real-World&rdquo;-Beispiel stammt aus dem Buch 
[Software Architecture with C++](https://www.amazon.de/Software-Architecture-effective-architecture-techniques/dp/1838554599)
von Adrian Ostrowski und Piotr Gaczkowski.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
