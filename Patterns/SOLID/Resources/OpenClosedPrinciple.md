# Open-Closed-Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

&ldquo;Klassen sollten für Erweiterungen offen, für Änderungen geschlossen sein.&rdquo;

In anderen Worten:
Das Prinzip bedeutet wörtlich genommen, dass man in der Lage sein sollte,
das Verhalten einer Klasse zu erweitern, ohne sie dabei zu verändern.
Auf den ersten Blick mag das *Open-Closed-Prinzip* etwas seltsam erscheinen und die Frage aufwerfen,
wie man das Verhalten einer Klasse &ldquo;ändern&rdquo; können soll, ohne diese dabei zu &ldquo;verändern&rdquo;?

Es gibt darauf im objektorientierten Design mehrere Antworten wie beispielsweise

  * dynamischer Polymorphismus,
  * statischer Polymorphismus und/oder
  * C++-Templates

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
016:     virtual ~Specification() = default;
017:     virtual bool isSatisfied(const std::shared_ptr<T>& product) const = 0;
018: };
019: 
020: template <typename T>
021: struct ColorSpecification : public Specification<T> 
022: {
023:     Color m_color;
024:     ColorSpecification(Color color) : m_color(color) {}
025: 
026:     bool isSatisfied(const std::shared_ptr<T>& product) const {
027:         return product->m_color == m_color; 
028:     }
029: };
030: 
031: template <typename T>
032: struct SizeSpecification : public Specification<T>
033: {
034:     Size m_size;
035:     SizeSpecification(Size size) : m_size(size) {}
036:         
037:     bool isSatisfied(const std::shared_ptr<T>& product) const {
038:         return product->m_size == m_size;
039:     }
040: };
041: 
042: template <typename T>
043: using Items = std::vector<std::shared_ptr<T>>;
044: 
045: template <typename T>
046: struct Filter 
047: {
048:     virtual Items<T> filter(Items<T> products, const Specification<T>& spec) = 0;
049: };
050: 
051: struct ProductFilter : public Filter<Product>
052: {
053:     Products<Product> filter(Products<Product> products, const Specification<Product>& spec)
054:     {
055:         Products<Product> result;
056:         for (auto& product : products) {
057:             if (spec.isSatisfied(product))
058:                 result.push_back(product);
059:         }
060:         return result;
061:     }
062: };
063: 
064: // combining logical specifications - with logical 'and'
065: template <typename T>
066: struct AndSpecification : public Specification<T>
067: {
068:     const Specification<T>& m_first;
069:     const Specification<T>& m_second;
070: 
071:     AndSpecification(const Specification<T>& first, const Specification<T>& second)
072:         : m_first{ first }, m_second{ second } {}
073: 
074:     bool isSatisfied(const std::shared_ptr<Product>& product) const {
075:         return m_first.isSatisfied(product) && m_second.isSatisfied(product);
076:     }
077: };
078: 
079: // logical 'And' specification using operator notation
080: template <typename T>
081: AndSpecification<T> operator&&(const Specification<T>& first, const Specification<T>& second) {
082:     return { first, second };
083: }
084: 
085: void main ()
086: {
087:     Products<Product> products
088:     {
089:         std::make_shared<Product>("Computer", Color::Gray, Size::Small),
090:         std::make_shared<Product>("Chair", Color::Black, Size::Large),
091:         std::make_shared<Product>("Headset", Color::Red, Size::Medium)
092:     };
093: 
094:     // combined specification
095:     AndSpecification<Product> specification = {
096:         SizeSpecification<Product>{ Size::Small },
097:         ColorSpecification<Product>{ Color::Gray }
098:     };
099: 
100:     auto computer = std::make_shared<Product>("Computer", Color::Gray, Size::Small);
101:     auto chair = std::make_shared<Product>("Chair", Color::Black, Size::Large);
102: 
103:     bool result{};
104:     result = specification.isSatisfied(computer);
105:     std::cout << "Result: " << std::boolalpha << result << std::endl;
106: 
107:     result = specification.isSatisfied(chair);
108:     std::cout << "Result: " << std::boolalpha << result << std::endl;
109: }
```

###### Beachten Sie an dem Quellcode:
Die Filtermethode `filter` der Klasse `ProductFilter` ist nicht zu ändern.
Sie kann jetzt mit allen Arten von Spezifikationen arbeiten!

*Hinweis*:
Die Klasse `AndSpecification` ist nur in der Lage, zwei Spezifikationen aufzunehmen.
Mit variadischen Templates lassen sich in C++ beliebig viele Spezifikationen in einem Objekt zusammenfassen!
Sehen Sie hierzu eine Realisierung im Quellcode der Klasse `GenericSpecification`!


#### Vorteile des *Open-Closed-Prinzips*

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


