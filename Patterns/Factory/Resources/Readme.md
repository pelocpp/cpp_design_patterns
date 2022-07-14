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


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Factory Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **ProductBase**: Basisklasse (oder Schnittstelle) für alle Produkte,
    die von der *Factory*-Klassen hergestellt werden sollen. Die Schnittstelle beschreibt eine oder mehrere Methoden,
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
