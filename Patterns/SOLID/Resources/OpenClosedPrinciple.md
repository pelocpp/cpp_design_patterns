# Open-Closed-Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

&ldquo;Klassen sollten für Erweiterungen offen, für Änderungen geschlossen sein&rdquo;.

In anderen Worten:
Das Prinzip bedeutet wörtlich genommen, dass man in der Lage sein sollte,
das Verhalten einer Klasse zu erweitern, ohne sie dabei zu verändern.
Auf den ersten Blick mag das *Open-Closed-Prinzip* etwas seltsam erscheinen und die Frage aufwerfen,
wie man das Verhalten einer Klasse &ldquo;ändern&rdquo; können soll, ohne diese dabei zu &ldquo;verändern&rdquo;?

Es gibt darauf im objektorientierten Design mehrere Antworten wie beispielsweise

  * dynamischer Polymorphismus,
  * statischer Polymorphismus und/oder
  * C++-Templates.

Wir betrachten das *Open-Closed-Prinzip* an einem Beispiel:

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
16:     static Products<Product> byColor(Products<Product> products, Color color)
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
27:     static Products<Product> bySize(Products<Product> products, Size size)
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
38:     static Products<Product> bySizeAndColor(Products<Product> products, Size size, Color color)
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
55:         std::make_shared<Product>("Chair", Color::Black, Size::Large),
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
    und drei Filterfunktionen (bzgl. `Color`, `Size` und ihre Kombination) haben.
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
001: #include <iostream>
002: #include <string>
003: #include <vector>
004: #include <memory>
005: #include <initializer_list>
006: #include <numeric>
007: 
008: enum class Color { Red, Green, Black, Gray };
009: enum class Size { Small, Medium, Large };
010: 
011: struct Product
012: {
013:     std::string m_name;
014:     Color       m_color;
015:     Size        m_size;
016: };
017: 
018: template <typename T>
019: using Products = std::vector<std::shared_ptr<T>>;
020: 
021: template <typename T>
022: struct Specification {
023:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
024: };
025: 
026: template <typename T>
027: struct ColorSpecification : public Specification<T> 
028: {
029:     Color m_color;
030:     ColorSpecification(Color color) : m_color(color) {}
031: 
032:     bool isSatisfied(const std::shared_ptr<T>& product) const override {
033:         return product->m_color == m_color; 
034:     }
035: };
036: 
037: template <typename T>
038: struct SizeSpecification : public Specification<T>
039: {
040:     Size m_size;
041:     SizeSpecification(Size size) : m_size(size) {}
042:         
043:     bool isSatisfied(const std::shared_ptr<T>& product) const override {
044:         return product->m_size == m_size;
045:     }
046: };
047: 
048: template <typename T>
049: struct Filter 
050: {
051:     virtual Products<T> filter(Products<T> products, const Specification<T>& spec) = 0;
052: };
053: 
054: struct ProductFilter : public Filter<Product>
055: {
056:     Products<Product> filter(Products<Product> products, const Specification<Product>& spec)
057:     {
058:         Products<Product> result;
059:         for (auto& product : products) {
060:             if (spec.isSatisfied(product))
061:                 result.push_back(product);
062:         }
063:         return result;
064:     }
065: };
066: 
067: // combining logical specifications - with logical 'and'
068: template <typename T>
069: struct AndSpecification : public Specification<T>
070: {
071:     const Specification<T>& m_first;
072:     const Specification<T>& m_second;
073: 
074:     AndSpecification(const Specification<T>& first, const Specification<T>& second)
075:         : m_first{ first }, m_second{ second } {}
076: 
077:     bool isSatisfied(const std::shared_ptr<Product>& product) const override {
078:         return m_first.isSatisfied(product) && m_second.isSatisfied(product);
079:     }
080: };
081: 
082: // combining logical specifications - with logical 'and' using operator notation
083: template <typename T>
084: AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
085:     return { first, second };
086: }
087: 
088: void test_01()
089: {
090:     Products<Product> products
091:     {
092:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
093:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
094:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
095:     };
096: 
097:     ProductFilter productFilter;
098:     ColorSpecification<Product> greenProducts = ColorSpecification<Product>{ Color::Green };
099: 
100:     for (const auto& product : productFilter.filter(products, greenProducts)) {
101:         std::cout << product->m_name << " is green" << std::endl;
102:     }
103: }
104: 
105: void test_02()
106: {
107:     // combined specification
108:     AndSpecification<Product> specification = {
109:         SizeSpecification<Product>{ Size::Small },
110:         ColorSpecification<Product>{ Color::Gray }
111:     };
112: 
113:     // another combined specification - using overloaded operator &&
114:     AndSpecification<Product> anotherSpecification =
115:         SizeSpecification<Product>{ Size::Medium } && ColorSpecification<Product>{ Color::Red };
116: 
117:     auto computer = std::make_shared<Product>("Computer", Color::Gray, Size::Small);
118:     auto chair = std::make_shared<Product>("Chair", Color::Black, Size::Large);
119:     auto headset = std::make_shared<Product>("Headset", Color::Red, Size::Medium);
120: 
121:     bool result{};
122:     result = specification.isSatisfied(computer);
123:     std::cout << "Result: " << std::boolalpha << result << std::endl;
124: 
125:     result = specification.isSatisfied(chair);
126:     std::cout << "Result: " << std::boolalpha << result << std::endl;
127: 
128:     result = anotherSpecification.isSatisfied(headset);
129:     std::cout << "Result: " << std::boolalpha << result << std::endl;
130: }
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

Die Anregungen zu diesem Beispiel finden Sie in

[Open Closed Principle in C++](http://www.vishalchovatiya.com/open-closed-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---


