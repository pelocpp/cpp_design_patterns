# Factory Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_factory_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Erstellung von Objekten, ohne dem Client die Erstellungslogik zur Verfügung zu stellen.&rdquo;

Das *Factory Pattern* ist ein Entwurfsmuster, mit dem Objekte erstellt werden können,
ohne die Erstellungslogik dem Client zur Verfügung zu stellen.
Für die neu erstellten Objekte steht eine gemeinsame Schnittstelle zur Verfügung.

#### Lösung:

Dieses Muster wird auch als *Simple Factory* Pattern bezeichnet.
Das *Factory*-Entwurfsmuster definiert eine Fabrikklasse mit einer Methode zum Erstellen von Objekten unterschiedlichen Typs
und überlässt die Auswahl des konkreten Klassentyps der Fabrikklasse.

##### Also man beachte:

  * Die Objekte, die von der Fabrikklasse zurückgeliefert werden, stehen in einer Vererbungshierarchie. 
  * Der Client der Fabrik hat keine Kenntnis darüber, welches konkrete Objekt er bei einer Anforderung aus dieser Klassenhierarchie erhält. 

##### Eine weitere Anwendungsmöglichkeit:
  
Unter Verwendung eines Objektpools kann die Fabrikklasse entscheiden,
ob sie bei Anforderung ein neues Objekt oder ein vorhandenes Objekt aus dem Pool zurückliefert.
Damit lässt sich Speicherplatz einsparen (siehe dazu auch das [Flyweight Pattern](https://github.com/pelocpp/cpp_design_patterns/blob/master/Patterns/Flyweight/Resources/Readme.md)).
Im Regelfall setzt dies aber voraus, dass die Objekte unveränderbar (*immutable*) sind.

##### Vorbemerkung: &ldquo;What's wrong with `new`?&rdquo;
  
Technisch betrachtet ist mit `new` nichts falsch &ndash;
in keinster Weise. Das Problem ist eher, dass im Falle
einer Hierarchie von Klassen und Schnittstellen der 
Anwender möglicherweise mehr Kenntnisse der Schnittstellen hat &ndash;
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
10: std::shared_ptr<IPizza> orderPizza()
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
01: std::shared_ptr<IPizza> orderPizza(std::string type)
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
15:     pizza->prepare();
16:     pizza->bake();
17:     pizza->cut();
18:     pizza->box();
19: 
20:     return pizza;
21: }
```

Das ist jetzt schon besser. Nur wie entwickelt sich die Funktion
`orderPizza` weiter, wenn es neue Pizzavarianten gibt und 
andere, weniger erfolgreiche Pizzavarianten aus dem Sortiment
genommen werden. Dann wird die Wartung und Pflege dieser Methode
 `orderPizza` unangenehm.

Wie wäre es, wenn wir die Objekterzeugung des `Pizza`-Objekts
aus der Methode `orderPizza` herausnehmen?

Moment! *Objekterzeugung*. Da sind wir doch beim `new`-Operator angekommen!
Also machen wir die Beobachtung, dass es Sinn ergeben kann,
den Aufruf des `new`-Operators für eine Pizza an &ldquo;anderer&rdquo; Stelle
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

Damit sieht unsere `orderPizza`-Methode nun so aus:

```cpp
std::shared_ptr<IPizza> orderPizzaEx(std::string type)
{
    std::shared_ptr<IPizza> pizza = PizzaFactory::createPizza(type);

    pizza->prepare();
    pizza->bake();
    pizza->cut();
    pizza->box();

    return pizza;
}
```

Diese Überlegungen sollen die Einführung eines
&ldquo;Fabrik&rdquo;-Gedankens motivieren.

---

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Factory Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **ProductBase**: Basisklasse (oder Schnittstelle) für alle Produkte,
    die von der *Factory*-Klasse hergestellt werden sollen. Die Schnittstelle beschreibt eine oder mehrere Methoden,
    die von den konkreten Ableitungen der Klasse implementiert werden.
  * **ConcreteProduct**: Konkrete Implementierung der Klasse `ProductBase`.
    Objekte des Typs `ConcreteProduct` werden von der Klasse *Factory* erzeugt.
  * **Factory**: Diese Klasse besitzt eine Methode `getProduct`,
    die Objekte zurückliefert, die die `ProductBase`-Schnittstelle implementieren.
    Über einen Parameter der `getProduct`-Methode wird typischerweise gesteuert, welches `ConcreteProduct` Objekt zu erzeugen ist.

<img src="dp_factory_pattern.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Factory Patterns*.

---

#### Abgrenzung zu anderen Entwurfsmustern:

  * Das *Factory Pattern* erstellt seine Objekte im Ganzen im Gegensatz zur *Builder*-Vorgehensweise.
    Hier werden die Objekte stückweise erstellt.  

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### Erstes Real-World Example:

Im Quellcode finden Sie ein selbsterklärendes Beispiel: *Mobil Phones*

---

#### Zweites Real-World Example:

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

Dabei sollten wir das *Open-Closed-Prinzip* nicht außer Acht lassen!

Eine Factory-Klasse ist hier angesagt. Eine weitere Option vor dem Hintergrund sich ständig variierender
Dokumenttypen ist eine Registrierungsfunktionen, die es gestattet, eigene Typen zu registrieren:

```cpp
01: struct IDocument 
02: {
03:     virtual ~IDocument() = default;
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

Das zweite Real-World Beispiel stammt aus dem Buch 
[Software Architecture with C++](https://www.amazon.de/Software-Architecture-effective-architecture-techniques/dp/1838554599)
von Adrian Ostrowski und Piotr Gaczkowski.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
