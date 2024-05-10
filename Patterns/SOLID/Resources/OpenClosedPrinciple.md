# Open-Closed-Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

&bdquo;Klassen sollten für Erweiterungen offen, für Änderungen geschlossen sein&rdquo;.

In anderen Worten:

> Das Prinzip bedeutet wörtlich genommen, dass man in der Lage sein sollte, das Verhalten einer Klasse zu erweitern, ohne sie dabei zu verändern.

Auf den ersten Blick mag das *Open-Closed-Prinzip* etwas seltsam erscheinen und die Frage aufwerfen,
wie man das Verhalten einer Klasse &bdquo;ändern&rdquo; können soll, ohne diese dabei zu &bdquo;verändern&rdquo;?

Wir betrachten das *Open-Closed-Prinzip* an zwei Beispielen.

### 1. Beispiel

Wir betrachten eine Klasse `Product` für Produkte eines E-Commerce Warenhauses.

In UML-Notation könnte ein einfaches Diagramm für die Klasse `Product` so aussehen:


<img src="./dp_single_responsibility_principle_class_product.svg" width="300">

*Abbildung* 1: Entwurf eine Klasse `Product`.

Jedes `Product`-Objekt verfügt über drei Eigenschaften: *Name*, *Preis* und *Gewicht*.

Stellen Sie sich nun vor, dass nach dem Entwurf der Produktklasse
und der gesamten E-Commerce-Plattform eine neue Anforderung von den Kunden kommt:

Sie wollen nun digitale Produkte wie E-Books, Filme und Audioaufnahmen kaufen.

Bis auf das Gewicht des Produkts ist alles in Ordnung.

Da es nun möglicherweise zwei Arten von Produkten gibt &ndash; materielle und digitale &ndash;,
sollten wir die Realisierung der `Product`-Klasse überdenken.

Wir könnten eine neue Methode `isDigital` in die Klasse `Product` integrieren:

```cpp
class Product
{
public:
    // code omitted for brevity
    bool isDigital() const {
        return m_weight == 0.0;
    }

    // code omitted for brevity
};
```

Offensichtlich haben wir die Klasse `Product` modifiziert &ndash; und damit dem *Open-Closed-Prinzip*  widersprochen.

Das Prinzip besagt, dass die Klasse

  * für Änderungen geschlossen sein sollte,
  * hingegen für Erweiterungen aber offen sein sollte.

Dies können wir erreichen, indem wir die Klasse `Product` neu gestalten und sie zu einer abstrakten Basisklasse für alle Produkte umbauen.

Wir erstellen als Nächstes zwei weitere Klassen, die von der nun umgestalteten Basisklasse `Product` erben: `PhysicalProduct` und `DigitalProduct`.

Das folgende Klassendiagramm zeigt das neue Design:

<img src="./dp_single_responsibility_principle_class_product_redesign.svg" width="600">

*Abbildung* 2: Redesign der Klasse `Product` mit zwei weiteren Klassen `PhysicalProduct` und `DigitalProduct`.


Wir können im letzten Diagramm erkennen, dass wir die Eigenschaft `m__weight` aus der Klasse `Product` entfernt haben.

Die Anforderungen des Kunden wurden mit zwei zusätzlichen Klassen `PhysicalProduct` und `DigitalProduct` erfüllt.

Eine dieser Klassen (`PhysicalProduct`) besitzt nun die Eigenschaft `m__weight`.

Die anderen Klasse `DigitalProduct`, für die ein Gewicht nicht relevant ist,
besitzt stattdessen eine Eigenschaft `m_filePath`, die symbolisch für die Ablage eines digitalen Produkts
in der internen Datenhaltung des E-Commerce Warenhauses stehen soll.

*Bemerkung*:
Das Ziel des *Open-Closed-Prinzips* wurde mit dem Konzept der *Vererbung* umgesetzt.


### 2. Beispiel

Das zweite Beispiel beschäftigt sich mit einer Reihe von Produkten (Klasse `Product`).
Wie beim ersten Beispiel betrachten wir den Umstand, dass an der Klasse `Product` Änderungen
vorgenommen werden müssen.

Diese Fallstudie beginnnen wir zunächst mit einem &bdquo;Bad-Practice&rdquo; Ansatz:


#### Beispiel: Violating the Open Closed Principle

```cpp
01: enum class Color { Red, Green, Black, Gray };
02: enum class Size { Small, Medium, Large };
03: 
04: struct Product
05: {
06:     std::string m_name;
07:     Color       m_color;
08:     Size        m_size;
09: };
10: 
11: template <typename T>
12: using Products = std::vector<std::shared_ptr<T>>;
13: 
14: struct ProductFilter 
15: {
16:     static Products<Product> byColor(const Products<Product>& products, Color color)
17:     {
18:         Products<Product> result{};
19:         for (const auto& product : products) {
20:             if (product->m_color == color) {
21:                 result.push_back(product);
22:             }
23:         }
24:         return result;
25:     }
26: 
27:     static Products<Product> bySize(const Products<Product>& products, Size size)
28:     {
29:         Products<Product> result{};
30:         for (const auto& product : products) {
31:             if (product->m_size == size) {
32:                 result.push_back(product);
33:             }
34:         }
35:         return result;
36:     }
37: 
38:     static Products<Product> bySizeAndColor(const Products<Product>& products, Size size, Color color)
39:     {
40:         Products<Product> result{};
41:         for (const auto& product : products) {
42:             if (product->m_size == size && product->m_color == color) {
43:                 result.push_back(product);
44:             }
45:         }
46:         return result;
47:     }
48: };
49: 
50: void main ()
51: {
52:     Products<Product> products
53:     {
54:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
55:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
56:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
57:     };
58: 
59:     for (const auto& product : ProductFilter::byColor(products, Color::Green))
60:         std::cout << product->m_name << " is green" << std::endl;
61:     
62:     for (const auto& product : ProductFilter::bySizeAndColor(products, Size::Large, Color::Green))
63:         std::cout << product->m_name << " is green & large" << std::endl;
64: }
```

  * Wir betrachten eine Reihe von Produkten (Klasse `Product`) und filtern diese
    nach einigen ihrer Attribute. An dem Beispielcode ist nichts auszusetzen,
    solange sich die Anforderungen nicht mehr ändern &ndash; was beim Software-Engineering niemals der Fall ist :)
  * Wir stellen uns nun vor, dass nachträglich
    Anforderungsänderungen und einige neue Filter-Operationen verlangt werden.
    In diesem Fall sind die Klassen `Product` und `ProductFilter` zu ändern
    und neue Filtermethoden hinzufügen.
  * Dieser Ansatz ist problematisch, da wir zwei Attribute (`Color` und `Size`) 
    und drei Filterfunktionen (bzgl. `Color`, `Size` und ihre Kombinationen) haben.
    Ein weiteres Attribut hätte zur Folge, dass acht neue Funktionen zu implementieren sind.
    Dieser Ansatz ist nicht nur nicht zielführend,
    der bereits existierende, realisierte Quellcode ist zu modifizieren.
    Dies ist eine Verletzung des *Open-Closed-Prinzips*:
    Es besagt, dass das System für Erweiterungen offen, aber für Modifikationen geschlossen zu sein hat.


#### Beispiel: Respecting the Open Closed Principle

Es gibt mehr als einen Weg, um das *Open-Closed-Prinzip* zu erreichen.
Das Design von Schnittstellen und das Hinzufügen einer Abstraktionsebene für Erweiterbarkeit
sind die am meisten verbreitete Vorgehensweise:

```cpp
001: enum class Color { Red, Green, Black, Gray };
002: enum class Size { Small, Medium, Large };
003: 
004: struct Product
005: {
006:     std::string m_name;
007:     Color       m_color;
008:     Size        m_size;
009: };
010: 
011: template <typename T>
012: using Products = std::vector<std::shared_ptr<T>>;
013: 
014: template <typename T>
015: struct ISpecification {
016:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
017: };
018: 
019: template <typename T>
020: class ColorSpecification : public ISpecification<T> 
021: {
022: private:
023:     Color m_color;
024:         
025: public:
026:     ColorSpecification(Color color) : m_color{ color } {}
027: 
028:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const override {
029:         return product->m_color == m_color; 
030:     }
031: };
032: 
033: template <typename T>
034: class SizeSpecification : public ISpecification<T>
035: {
036: private:
037:     Size m_size;
038:         
039: public:
040:     SizeSpecification(Size size) : m_size{ size } {}
041:         
042:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const override {
043:         return product->m_size == m_size;
044:     }
045: };
046: 
047: template <typename T>
048: struct IFilter 
049: {
050:     virtual Products<T> filter(const Products<T>& products, const ISpecification<T>& spec) const = 0;
051: };
052: 
053: template <typename T>
054: struct ProductFilter : public IFilter<T>
055: {
056:     virtual Products<T> filter(const Products<T>& products, const ISpecification<T>& spec) const override
057:     {
058:         Products<T> result;
059:         for (const auto& product : products) {
060:             if (spec.isSatisfied(product))
061:                 result.push_back(product);
062:         }
063:         return result;
064:     }
065: };
066: 
067: // combining logical specifications - with logical 'and'
068: template <typename T>
069: class AndSpecification : public ISpecification<T>
070: {
071: private:
072:     const ISpecification<T>& m_first;
073:     const ISpecification<T>& m_second;
074: 
075: public:
076:     AndSpecification(const ISpecification<T>& first, const ISpecification<T>& second)
077:         : m_first{ first }, m_second{ second } {}
078: 
079:     virtual bool isSatisfied(const std::shared_ptr<Product>& product) const override {
080:         return m_first.isSatisfied(product) && m_second.isSatisfied(product);
081:     }
082: };
083: 
084: // combining logical specifications - with logical 'and' using operator notation
085: template <typename T>
086: AndSpecification<T> operator&& (const ISpecification<T>& first, const ISpecification<T>& second) {
087:     return AndSpecification<T>{ first, second };
088: }
089: 
090: void test_01()
091: {
092:     Products<Product> products
093:     {
094:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
095:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
096:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
097:     };
098: 
099:     ProductFilter<Product> productFilter;
100: 
101:     ColorSpecification<Product> greenProducts {
102:         ColorSpecification<Product>{ Color::Green }
103:     };
104: 
105:     for (const auto& product : productFilter.filter(products, greenProducts)) {
106:         std::cout << product->m_name << " is green" << std::endl;
107:     }
108: }
109: 
110: void test_02()
111: {
112:     Products<Product> products
113:     {
114:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
115:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
116:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
117:     };
118: 
119:     ProductFilter<Product> productFilter;
120: 
121:     ColorSpecification<Product> greenProducts {
122:         ColorSpecification<Product>{ Color::Green }
123:     };
124: 
125:     SizeSpecification largeProducts{
126:         SizeSpecification<Product>{ Size::Large }
127:     };
128: 
129:     for (const auto& product : productFilter.filter(products, greenProducts && largeProducts)) {
130:         std::cout << product->m_name << " is green and large" << std::endl;
131:     }
132: }
```

###### Beachten Sie an dem Quellcode:
Die Filtermethode `filter` der Klasse `ProductFilter` ist nicht zu ändern.
Sie kann jetzt mit allen Arten von Spezifikationen arbeiten!

*Hinweis*:
Die Klasse `AndSpecification` ist nur in der Lage, zwei Spezifikationen aufzunehmen.
Mit variadischen Templates lassen sich in C++ beliebig viele Spezifikationen in einem Objekt zusammenfassen!
Sehen Sie hierzu eine Realisierung im Quellcode der Klasse `GenericSpecification`!


#### Vorteile des *Open-Closed-Prinzips*:

  * Expressiveness &ndash; Ausdruckskraft
  * Maintainability &ndash; Wartbarkeit
  * Flexibility &ndash; Flexibilität

---

## Literaturhinweise

Die Anregungen zu diesem Beispiel finden Sie in

[Open Closed Principle in C++](http://www.vishalchovatiya.com/open-closed-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
