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
015: struct Specification {
016:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
017: };
018: 
019: template <typename T>
020: struct ColorSpecification : public Specification<T> 
021: {
022:     Color m_color;
023:     ColorSpecification(Color color) : m_color(color) {}
024: 
025:     bool isSatisfied(const std::shared_ptr<T>& product) const override {
026:         return product->m_color == m_color; 
027:     }
028: };
029: 
030: template <typename T>
031: struct SizeSpecification : public Specification<T>
032: {
033:     Size m_size;
034:     SizeSpecification(Size size) : m_size(size) {}
035:         
036:     bool isSatisfied(const std::shared_ptr<T>& product) const override {
037:         return product->m_size == m_size;
038:     }
039: };
040: 
041: template <typename T>
042: struct Filter 
043: {
044:     virtual Products<T> filter(Products<T> products, const Specification<T>& spec) = 0;
045: };
046: 
047: struct ProductFilter : public Filter<Product>
048: {
049:     Products<Product> filter(Products<Product> products, const Specification<Product>& spec)
050:     {
051:         Products<Product> result;
052:         for (auto& product : products) {
053:             if (spec.isSatisfied(product))
054:                 result.push_back(product);
055:         }
056:         return result;
057:     }
058: };
059: 
060: // combining logical specifications - with logical 'and'
061: template <typename T>
062: struct AndSpecification : public Specification<T>
063: {
064:     const Specification<T>& m_first;
065:     const Specification<T>& m_second;
066: 
067:     AndSpecification(const Specification<T>& first, const Specification<T>& second)
068:         : m_first{ first }, m_second{ second } {}
069: 
070:     bool isSatisfied(const std::shared_ptr<Product>& product) const override {
071:         return m_first.isSatisfied(product) && m_second.isSatisfied(product);
072:     }
073: };
074: 
075: // combining logical specifications - with logical 'and' using operator notation
076: template <typename T>
077: AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
078:     return { first, second };
079: }
080: 
081: void test_01()
082: {
083:     Products<Product> products
084:     {
085:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
086:         std::make_shared<Product>("Chair", Color::Green, Size::Large),
087:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
088:     };
089: 
090:     ProductFilter productFilter;
091:     ColorSpecification<Product> greenProducts = ColorSpecification<Product>{ Color::Green };
092: 
093:     for (const auto& product : productFilter.filter(products, greenProducts)) {
094:         std::cout << product->m_name << " is green" << std::endl;
095:     }
096: }
097: 
098: void test_02()
099: {
100:     // combined specification
101:     AndSpecification<Product> specification = {
102:         SizeSpecification<Product>{ Size::Small },
103:         ColorSpecification<Product>{ Color::Gray }
104:     };
105: 
106:     // another combined specification - using overloaded operator &&
107:     AndSpecification<Product> anotherSpecification =
108:         SizeSpecification<Product>{ Size::Medium } && ColorSpecification<Product>{ Color::Red };
109: 
110:     auto computer = std::make_shared<Product>("Computer", Color::Gray, Size::Small);
111:     auto chair = std::make_shared<Product>("Chair", Color::Black, Size::Large);
112:     auto headset = std::make_shared<Product>("Headset", Color::Red, Size::Medium);
113: 
114:     bool result{};
115:     result = specification.isSatisfied(computer);
116:     std::cout << "Result: " << std::boolalpha << result << std::endl;
117: 
118:     result = specification.isSatisfied(chair);
119:     std::cout << "Result: " << std::boolalpha << result << std::endl;
120: 
121:     result = anotherSpecification.isSatisfied(headset);
122:     std::cout << "Result: " << std::boolalpha << result << std::endl;
123: }
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


