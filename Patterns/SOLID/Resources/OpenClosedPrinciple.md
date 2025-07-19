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
wie man das Verhalten einer Klasse &bdquo;erweitern&rdquo; können soll, ohne diese dabei zu &bdquo;verändern&rdquo;?

Wir betrachten das *Open-Closed-Prinzip* an zwei Beispielen.

### 1. Beispiel

Wir legen im Folgenden eine Klasse `Product` für Produkte eines E-Commerce Warenhauses zu Grunde.
In UML-Notation könnte ein einfaches UML-Diagramm für die Klasse `Product` so aussehen:

<img src="./dp_single_responsibility_principle_class_product.svg" width="300">

*Abbildung* 1: Entwurf einer Klasse `Product`.

Jedes `Product`-Objekt verfügt über drei Eigenschaften: *Name*, *Preis* und *Gewicht*.

Stellen Sie sich nun vor, dass nach dem Entwurf der Produktklasse
und der gesamten E-Commerce-Plattform eine neue Anforderung von den Kunden kommt:

Sie wollen nun digitale Produkte wie E-Books, Filme und Audioaufnahmen kaufen.

Bis auf das Gewicht des Produkts ist alles in Ordnung.

Da es nun möglicherweise zwei Arten von Produkten gibt &ndash; materielle und digitale &ndash;,
müssen wir die Realisierung der `Product`-Klasse überdenken.
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

Das Prinzip besagt, dass eine Klasse

  * für Änderungen geschlossen sein sollte,
  * hingegen für Erweiterungen aber offen sein sollte.

Dies können wir erreichen, indem wir die Klasse `Product` neu gestalten und sie zu einer abstrakten Basisklasse für konkrete Produkte umbauen.
Wir erstellen als nächstes zwei weitere Klassen, die von der nun umgestalteten Basisklasse `Product` erben: `PhysicalProduct` und `DigitalProduct`.

Das folgende Klassendiagramm zeigt das neue Design:

<img src="./dp_single_responsibility_principle_class_product_redesign.svg" width="600">

*Abbildung* 2: Redesign der Klasse `Product` mit zwei weiteren Klassen `PhysicalProduct` und `DigitalProduct`.

Wir können im letzten Diagramm erkennen, dass

  * die Eigenschaft `m_weight` aus der Klasse `Product` entfernt wurde,
  * die Anforderungen des Kunden mit zwei zusätzlichen Klassen `PhysicalProduct` und `DigitalProduct` umgesetzt wurden,
  * eine dieser Klassen (`PhysicalProduct`) in gewohnter Manier die Eigenschaft `m_weight` besitzt und
  * eine zweite, zusätzliche Klasse `DigitalProduct` entwickelt wurde, für die ein Gewicht nicht relevant ist,
stattdessen eine Eigenschaft `m_filePath` besitzt, die symbolisch für die Ablage eines digitalen Produkts
in der internen Datenhaltung des E-Commerce Warenhauses steht.

*Bemerkung*:
Das Ziel des *Open-Closed-Prinzips* wurde mit dem Konzept der *Vererbung* umgesetzt.


### 2. Beispiel

Das zweite Beispiel beschäftigt sich ebenfalls mit einer Reihe von Produkten (Klasse `Product`).
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
012: concept ProductRequirements = requires(T t) {
013:     { t.m_name };
014:     { t.m_color };
015:     { t.m_size };
016: };
017: 
018: template <typename T>
019: concept ProductRequirementsImproved = requires(T t) {
020:     { t.m_name } -> std::same_as<std::string&>;
021:     { t.m_color } -> std::same_as<Color&>;
022:     { t.m_size } -> std::same_as<Size&>;
023: };
024: 
025: template <typename T>
026:     requires ProductRequirements<T>
027: using Products = std::vector<std::shared_ptr<T>>;
028: 
029: template <typename T>
030:     requires ProductRequirements<T>
031: struct ISpecification {
032:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
033: };
034: 
035: template <typename T>
036: class ColorSpecification : public ISpecification<T> 
037: {
038: private:
039:     Color m_color;
040:         
041: public:
042:     ColorSpecification(Color color) : m_color{ color } {}
043: 
044:     bool isSatisfied(const std::shared_ptr<T>& product) const override {
045:         return product->m_color == m_color; 
046:     }
047: };
048: 
049: template <typename T>
050: class SizeSpecification : public ISpecification<T>
051: {
052: private:
053:     Size m_size;
054:         
055: public:
056:     SizeSpecification(Size size) : m_size{ size } {}
057:         
058:     bool isSatisfied(const std::shared_ptr<T>& product) const override {
059:         return product->m_size == m_size;
060:     }
061: };
062: 
063: template <typename T>
064:     requires ProductRequirements<T>
065: struct IFilter 
066: {
067:     virtual Products<T> filter(const Products<T>& products, const ISpecification<T>& spec) const = 0;
068: };
069: 
070: template <typename T>
071: struct ProductFilter : public IFilter<T>
072: {
073:     Products<T> filter(const Products<T>& products, const ISpecification<T>& spec) const override
074:     {
075:         Products<T> result{};
076:         for (const auto& product : products) {
077:             if (spec.isSatisfied(product))
078:                 result.push_back(product);
079:         }
080:         return result;
081:     }
082: };
083: 
084: // combining logical specifications - with logical 'and'
085: template <typename T>
086:     requires ProductRequirements<T>
087: class AndSpecification : public ISpecification<T>
088: {
089: private:
090:     const ISpecification<T>& m_first;
091:     const ISpecification<T>& m_second;
092: 
093: public:
094:     AndSpecification(const ISpecification<T>& first, const ISpecification<T>& second)
095:         : m_first{ first }, m_second{ second } {}
096: 
097:     bool isSatisfied(const std::shared_ptr<Product>& product) const override {
098:         return m_first.isSatisfied(product) && m_second.isSatisfied(product);
099:     }
100: };
101: 
102: // combining logical specifications - with logical 'and' using operator notation
103: template <typename T>
104: AndSpecification<T> operator&& (const ISpecification<T>& first, const ISpecification<T>& second) {
105:     return AndSpecification<T>{ first, second };
106: }
107: 
108: static void test_conceptual_example_ocp_01()
109: {
110:     Products<Product> products
111:     {
112:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
113:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
114:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
115:     };
116: 
117:     ProductFilter<Product> productFilter;
118: 
119:     ColorSpecification<Product> greenSpecification{ Color::Green };
120: 
121:     for (const auto& product : productFilter.filter(products, greenSpecification)) {
122:         std::cout << product->m_name << " is green" << std::endl;
123:     }
124: }
125: 
126: static void test_conceptual_example_ocp_02()
127: {
128:     Products<Product> products
129:     {
130:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
131:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
132:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
133:     };
134: 
135:     ProductFilter<Product> productFilter;
136: 
137:     ColorSpecification<Product> greenSpecification{ Color::Green };
138: 
139:     SizeSpecification<Product> largeSpecification{ Size::Large };
140: 
141:     for (const auto& product : productFilter.filter(products, greenSpecification&& largeSpecification)) {
142:         std::cout << product->m_name << " is green and large" << std::endl;
143:     }
144: }
145: 
146: static void test_conceptual_example_ocp_03()
147: {
148:     // combined specification
149:     AndSpecification<Product> specification {
150:         SizeSpecification<Product>{ Size::Small },
151:         ColorSpecification<Product>{ Color::Gray }
152:     };
153: 
154:     // another combined specification - using overloaded operator &&
155:     AndSpecification<Product> anotherSpecification {
156:         SizeSpecification<Product>{ Size::Medium } &&
157:         ColorSpecification<Product>{ Color::Red }
158:     };
159: 
160:     std::shared_ptr<Product> computer {
161:         std::make_shared<Product>("Computer", Color::Gray, Size::Small) 
162:     };
163:     
164:     std::shared_ptr<Product> chair {
165:         std::make_shared<Product>("Chair", Color::Green, Size::Large)
166:     };
167:     
168:     std::shared_ptr<Product> headset {
169:          std::make_shared<Product>("Headset", Color::Red, Size::Medium)
170:     };
171: 
172:     bool result{ specification.isSatisfied(computer) };
173:     std::cout << "Result: " << std::boolalpha << result << std::endl;
174: 
175:     result = specification.isSatisfied(chair);
176:     std::cout << "Result: " << std::boolalpha << result << std::endl;
177: 
178:     result = anotherSpecification.isSatisfied(headset);
179:     std::cout << "Result: " << std::boolalpha << result << std::endl;
180: }
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

#### Conceptual Example:

[Quellcode](../OCP.cpp)

---

## Literaturhinweise

Die Anregungen zu diesem Beispiel finden Sie in

[Open Closed Principle in C++](https://vishalchovatiya.com/posts//single-responsibility-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
