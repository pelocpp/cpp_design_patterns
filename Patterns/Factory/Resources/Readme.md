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

&ldquo;Für die Erstellung von Objekten im Gegensatz zur *Builder*-Vorgehensweise, die stückweise erstellt.&rdquo;

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
05:         std::shared_ptr<IPizza> pizza{ nullptr };
06: 
07:         if (type == std::string{ "cheese" }) {
08:             pizza = std::make_shared<CheesePizza>();
09:         }
10:         else if (type == std::string{ "pepperoni" }) {
11:             pizza = std::make_shared<PepperoniPizza>();
12:         }
13:         else if (type == std::string{ "clam" }) {
14:             pizza = std::make_shared<ClamPizza>();
15:         }
16:         else if (type == std::string{ "veggie" }) {
17:             pizza = std::make_shared<VeggiePizza>();
18:         }
19: 
20:         return pizza;
21:     }
22: };
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
std::unique_ptr<IDocument> awkwardOpen(std::string path) {
    if (path.ends_with(".pdf")) return std::make_unique<PdfDocument>();
    if (path.ends_with(".html")) return std::make_unique<HtmlDocument>();
    return nullptr;
}
```

Wie gehen wir vor, wenn wir die `open`&ndash;Funktion um weitere Dokumentarten wie zum Beispiel
*OpenDocument* erweitern wollen?

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
09: public:
10:     explicit PdfDocument() {}
11:     explicit PdfDocument(std::string path) {}
12: 
13:     std::vector<std::string> getText() override {
14:         return { "Text from PDF" };
15:     }
16: };
17: 
18: class HtmlDocument : public IDocument 
19: ...
20: 
21: class OdtDocument : public IDocument 
22: ...
23: 
24: class DocumentFactory
25: {
26: public:
27:     using DocumentType = std::unique_ptr<IDocument>;
28: 
29:     using ConcreteOpener = std::function<DocumentType(std::string)>;
30: 
31:     void Register(const std::string& extension, const ConcreteOpener& opener) {
32:         openerByExtension.emplace(extension, opener);
33:     }
34: 
35:     DocumentType open(std::string path) {
36:         auto last_dot = path.find_last_of('.');
37:         if (last_dot != std::string::npos) {
38:             auto extension = path.substr(last_dot + 1);
39:             auto& opener = openerByExtension.at(extension);
40:             auto document = opener(path);
41:             return document;
42:         }
43:         else {
44:             throw std::invalid_argument{ "Trying to open a file with no extension" };
45:         }
46:     }
47: 
48: private:
49:     std::unordered_map<std::string, ConcreteOpener> openerByExtension;
50: };
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
