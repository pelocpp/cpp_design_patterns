# Das *Type Erasure* Idiom

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Um einen generischen Container zu erstellen, der eine Vielzahl unterschiedlicher, konkreter Typen aufnehmen kann.&rdquo;

*Type Erasure* ermöglicht es, verschiedene Datentypen mit einem generischen Interface zu verwenden.
Das Idiom *Type Erasure* ist auch unter dem Namen &bdquo;*Duck Typing*&rdquo; bekannt.
Der Begriff geht auf ein Gedicht von [James Whitcomb Riley](https://de.wikipedia.org/wiki/James_Whitcomb_Riley) zurück:

&bdquo;*When I see a bird that walks like a duck and swims like a duck and quacks like a duck, I call that bird a duck.*&rdquo;

Was ist damit gemeint bzw. welchen Zusammenhang gibt es zur objekt-orientierten Programmierung?
Wir stellen uns eine Funktion

<pre>
void acceptsOnlyDucks(Duck& duck);
</pre>

vor, die nur Objekte des Typs `Duck` akzeptiert.
In statisch typisierten Sprachen wie C++ kann diese Funktion nur mit Objekten aufgerufen werden,
deren Typ sich von `Duck`  abgeleitet.

Es gibt aber auch andere Programmiersprachen wie beispielsweise Python.
Hier könnten alle Datentypen verwendet werden, die sich wie ein Objekt des Typs `Duck` &bdquo;*verhalten*&rdquo;.
Damit ist gemeint:  &bdquo;Wenn ein Vogel sich wie eine Ente verhält, dann ist es eine Ente&rdquo;.
Ein Sprichwort in Python bringt das verschärft auf den Punkt: &bdquo;*Don't ask for permission, ask for forgiveness.*&rdquo;.

Etwas mehr vor einem programmiersprachlichen Hintergrund formuliert bedeutet das:
Wir rufen eine Funktion `acceptsOnlyDucks` mit einem Vogel auf und hoffen auf das Beste :).
Geht irgend etwas schief, dann gibt es immer noch die Möglichkeiten des Exception Handlings.
Sprachlich gibt es diese Vorgehensweise in Python &ndash; und mit etwas Aufwand auch in C++,
wie wir im folgenden Beispiel sehen werden:

#### Motivation: *Polymorphismus mit Schnittstellen*
 
Wir betrachten zunächst den klassischen Weg des *Polymorphismus mit Schnittstellen*.
Zunächst definieren wir eine Schnittstelle (hier: `IAnimal`), die ausschließlich aus rein virtuellen Methoden besteht.

Anschließend erstellen wir für jede Implementierung, die diese Schnittstelle verwenden möchte,
eine Unterklasse, die von der Basisklasse (Schnittstellenklasse) erbt und ihre Methoden implementiert.

```cpp
01: class IAnimal
02: {
03: public:
04:     virtual std::string see() const = 0;
05:     virtual std::string say() const = 0;
06: };
07: 
08: class Cow : public IAnimal
09: {
10: public:
11:     virtual std::string see() const override { return "cow"; }
12:     virtual std::string say() const override { return "moo"; }
13: };
14: 
15: class Pig : public IAnimal
16: {
17: public:
18:     std::string see() const { return "pig"; }
19:     std::string say() const { return "oink"; }
20: };
21: 
22: class Dog : public IAnimal
23: {
24: public:
25:     std::string see() const { return "dog"; }
26:     std::string say() const { return "woof"; }
27: };
28: 
29: void seeAndSay(const std::shared_ptr<IAnimal>& animal)
30: {
31:     std::cout 
32:         << "The " << animal->see() << " says '"
33:         << animal->say() << "' :)." << std::endl;
34: }
35: 
36: static void clientCode()
37: {
38:     std::shared_ptr<IAnimal> aCow { std::make_shared<Cow>() };
39:     std::shared_ptr<IAnimal> aPig { std::make_shared<Pig>() };
40:     std::shared_ptr<IAnimal> aDog { std::make_shared<Dog>() };
41: 
42:     seeAndSay(aCow);
43:     seeAndSay(aPig);
44:     seeAndSay(aDog);
45: }
```

#### Motivation: *Polymorphismus mit Templates*
 
Die Strategie des letzten Beispiels funktioniert solange, 
wie die konkreten Typen, mit denen wir arbeiten wollen,
alle von einer gemeinsamen Basisklasse erben, die alle erforderlichen Funktionen bereitstellt.

Nicht immer haben wir diese Situation vorliegen.
Möglicherweise haben wir keine Kontrolle über die konkreten Typen (zum Beispiel Klassen wie `std::string`),
oder es ist nicht einmal der Fall gegeben, dass der konkrete Typ eine Basisklasse besitzt (zum Beispiel Datentyp `int`).

Dies ist aber noch lange kein Hinderungsgrund, nicht doch auf eine andere Weise das Ziel zu erreichen.
Mit Templates lassen sich Datentypen *polymorph* machen:

```cpp
01: template <typename T>
02: void seeAndSay(const std::shared_ptr<T>& animal)
03: {
04:     std::cout
05:         << "The " << animal->see() << " says '"
06:         << animal->say() << "' :)." << std::endl;
07: }
```

Diese Methode `seeAndSay` lässt
sich für alle Objekte aufrufen, die eine `see()`- und `say()`-Methode ohne Argumente besitzen.

Beispiel:

```cpp
01: class Dog
02: {
03: public:
04:     std::string see() const { return "dog"; }
05:     std::string say() const { return "woof"; }
06: };
07: 
08: static void clientCode()
09: {
10:     std::shared_ptr<Dog> aDog{ std::make_shared<Dog>() };
11:     seeAndSay<Dog>(aDog);
12: }
```

#### Motivation: *Nachteile von Polymorphismus mit Templates*
 
Objekte unterschiedlichen Typs lassen sich nicht &ndash; ohne Weiteres &ndash; in einem Container / Array ablegen:

```cpp
std::shared_ptr<Cow> aCow { std::make_shared<Cow>() };
std::shared_ptr<Pig> aPig { std::make_shared<Pig>() };
std::shared_ptr<Dog> aDog { std::make_shared<Dog>() };

??? animals[] = { aCow, aPig, aDog };
```

Mit dem Ansatz des *Polymorphismus mit Templates* lässt sich ein solches Array nicht erstellen,
da es keinen gemeinsamen Basisklassentyp für das Array gibt.

#### Erste Skizzierung eines Lösungsansatzes:

Wenn wir für die vorliegenden Objekte nicht die gewünschte Vererbungshierarchie haben
und wenn wir die Datentypen der Objekte nicht ändern können,
dann könnten wir zumindest eine eigene Vererbungshierarchie
(bestehend aus Wrapper-Objekten/Hüllen-Objekten) aufbauen.
Das heißt, wir definieren unsere eigene Schnittstelle (hier: `MyAnimal`) und implementieren sie mehrfach.

Jede Implementierung der Schnittstelle umschließt eine Klasse `Cow`, eine Klasse `Pig` oder eine Klasse `Dog`
und ruft diese für ihre virtuellen Methoden auf.
Dann erstellen wir Wrapper-Objekte, die von `MyAnimal` erben.
Jeder Wrapper tut nichts weiter als das &bdquo;echte&rdquo; zu Grunde liegende Objekt aufzurufen:

Jetzt können wir mit Instanzen von `MyAnimal` arbeiten, die jeweils ein `Cow`-, `Pig`- oder `Dog`-Objekt umschließen:

```cpp
01: class MyAnimal
02: {
03: public:
04:     virtual std::string see() const = 0;
05:     virtual std::string say() const = 0;
06: };
07: 
08: class Cow
09: {
10: public:
11:     std::string see() const { return "cow"; }
12:     std::string say() const { return "moo"; }
13: };
14: 
15: class Pig
16: {
17: public:
18:     std::string see() const { return "pig"; }
19:     std::string say() const { return "oink"; }
20: };
21: 
22: class Dog
23: {
24: public:
25:     std::string see() const { return "dog"; }
26:     std::string say() const { return "woof"; }
27: };
28: 
29: class MyCow : public MyAnimal
30: {
31: private:
32:     Cow m_cow;
33: 
34: public:
35:     virtual std::string see() const override { return m_cow.see(); }
36:     virtual std::string say() const override { return m_cow.say(); }
37: };
38: 
39: class MyPig : public MyAnimal
40: {
41: private:
42:     Pig m_pig;
43: 
44: public:
45:     virtual std::string see() const override { return m_pig.see(); }
46:     virtual std::string say() const override { return m_pig.say(); }
47: };
48: 
49: class MyDog : public MyAnimal
50: {
51: private:
52:     Dog m_dog;
53: 
54: public:
55:     virtual std::string see() const override { return m_dog.see(); }
56:     virtual std::string say() const override { return m_dog.say(); }
57: };
58: 
59: void seeAndSay(const std::shared_ptr<MyAnimal>& animal)
60: {
61:     std::cout
62:         << "The " << animal->see() << " says '"
63:         << animal->say() << "' :)." << std::endl;
64: }
65: 
66: static void clientCode()
67: {
68:     std::shared_ptr<MyAnimal> aCow{ std::make_shared<MyCow>() };
69:     std::shared_ptr<MyAnimal> aPig{ std::make_shared<MyPig>() };
70:     std::shared_ptr<MyAnimal> aDog{ std::make_shared<MyDog>() };
71: 
72:     std::vector<std::shared_ptr<MyAnimal>> animals = { aCow , aPig , aDog };
73: 
74:     for (const auto& animal : animals) {
75:         seeAndSay(animal);
76:     }
77: }
```

Das funktioniert, aber es gibt einen eklatanten Nachteil:
Wir müssen für jeden konkreten Typ, den wir verpacken möchten (zum Beispiel Klasse `Cow`),
eine Wrapper-Klasse (hier: Klasse `MyCow`) definieren.

Wir haben jedoch bereits eine einfache Möglichkeit gesehen, den Compiler diese Arbeit für uns erledigen zu lassen:
Durch die Verwendung von Templates:

```cpp
01: template <typename T>
02: class AnimalWrapper : public MyAnimal
03: {
04: private:
05:     const T& m_animal;
06: 
07: public:
08:     AnimalWrapper(const T& animal) : m_animal{ animal } {}
09: 
10:     virtual std::string see() const override { return m_animal.see(); }
11:     virtual std::string say() const override { return m_animal.say(); }
12: };
```

#### Das *Type Erasure* Idiom

Das, was wir im letzten Abschnitt gebaut haben, ist die Grundlage des &bdquo;*Type Erasure*&rdquo; Idioms.
Was wir noch erledigen sollten, ist, all diese Maschinerie hinter einer weiteren Klasse zu verstecken,
damit ein Aufrufer sich nicht mit diesen benutzerdefinierten Schnittstellen und Templates befassen muss:

```cpp
01: class SeeAndSay
02: {
03:     // 'interface'
04:     class MyAnimal
05:     {
06:     public:
07:         virtual std::string see() const = 0;
08:         virtual std::string say() const = 0;
09:     };
10: 
11:     // derived type(s) / 'wrapper class'
12:     template <typename T>
13:     class AnimalWrapper : public MyAnimal
14:     {
15:     private:
16:         const T& m_animal;
17: 
18:     public:
19:         AnimalWrapper(const T& animal) : m_animal{ animal } {}
20: 
21:         virtual std::string see() const override { return m_animal->see(); }
22:         virtual std::string say() const override { return m_animal->say(); }
23:     };
24: 
25:     // registered animals
26:     std::vector<std::shared_ptr<MyAnimal>> m_animals;
27: 
28: public:
29:     template <typename T>    
30:     void addAnimal(const T& animal)
31:     {
32:         m_animals.push_back(std::make_shared<AnimalWrapper<T>>(animal));
33:     }
34: 
35:     void seeAndSay(const std::shared_ptr<MyAnimal>& animal) {
36:         std::cout
37:             << "The " << animal->see() << " says '"
38:             << animal->say() << "' :)." << std::endl;
39:     }
40: 
41:     void print() {
42:         for (const auto& animal : m_animals) {
43:             seeAndSay(animal);
44:         }
45:     }
46: };
47: 
48: static void clientCode()
49: {
50:     SeeAndSay animals;
51: 
52:     std::shared_ptr<Cow> aCow{ std::make_shared<Cow>() };
53:     std::shared_ptr<Pig> aPig{ std::make_shared<Pig>() };
54:     std::shared_ptr<Dog> aDog{ std::make_shared<Dog>() };
55: 
56:     animals.addAnimal(aCow);
57:     animals.addAnimal(aPig);
58:     animals.addAnimal(aDog);
59: 
60:     animals.print();
61: }
```

#### *Type Erasure* Nomenklatur

Die im letzten Abschnitt verwendeten Bezeichner `MyAnimal` und `AnimalWrapper` treten im &bdquo;echten Leben&rdquo;
so natürlich nicht auf, sie haben standardisierte Bezeichner:

  * `MyAnimal` ist ein Beispiel eines *Type Erasure* **Konzepts**: Klasse `Concept`.
  * `AnimalWrapper` ist ein Beispiel eines *Type Erasure* **Modells**: Klasse `Model`.

Ein **Konzept** beschreibt die Schnittstelle, gegen die wir in der Hüllenklasse programmieren müssen.

Ein **Modell** ist ein auf Templates basierendes Wrapper-Objekt, das die **Konzept**-Schnittstelle implementiert
und alle Konzept-Methoden an den zugrunde liegenden, konkreten Typ weiterleitet.

Wir formulieren das letzte Beispiel entsprechend der *Type Erasure* Namensgebung um:

```cpp
01: class SeeAndSay
02: {
03:     // 'interface'
04:     class AnimalConcept
05:     {
06:     public:
07:         virtual std::string see() const = 0;
08:         virtual std::string say() const = 0;
09:     };
10: 
11:     // derived type(s)
12:     template <typename T>
13:     class AnimalModel : public AnimalConcept
14:     {
15:     private:
16:         const T& m_animal;
17: 
18:     public:
19:         AnimalModel (const T& animal) : m_animal{ animal } {}
20: 
21:         virtual std::string see() const override { return m_animal->see(); }
22:         virtual std::string say() const override { return m_animal->say(); }
23:     };
24: 
25:     // registered animals
26:     std::vector<std::shared_ptr<AnimalConcept>> m_animals;
27: 
28: public:
29:     template <typename T>
30:     void addAnimal(const T& animal)
31:     {
32:         m_animals.push_back(std::make_shared<AnimalModel<T>>(animal));
33:     }
34: 
35:     void seeAndSay(const std::shared_ptr<AnimalConcept>& animal) {
36:         std::cout
37:             << "The " << animal->see() << " says '"
38:             << animal->say() << "' :)." << std::endl;
39:     }
40: 
41:     void print() {
42:         for (const auto& animal : m_animals) {
43:             seeAndSay(animal);
44:         }
45:     }
46: };
47: 
48: static void clientCode()
49: {
50:     SeeAndSay animals;
51: 
52:     std::shared_ptr<Cow> aCow = std::make_shared<Cow>();
53:     std::shared_ptr<Pig> aPig = std::make_shared<Pig>();
54:     std::shared_ptr<Dog> aDog = std::make_shared<Dog>();
55: 
56:     animals.addAnimal(aCow);
57:     animals.addAnimal(aPig);
58:     animals.addAnimal(aDog);
59: 
60:     animals.print();
61: }
```

Damit wären wir fast Ende unserer Betrachtungen des *Type Erasure* Idioms.
Wer die letzte Variation gut betrachtet hat, wird feststellen,
dass wir pro beteiligtem Objekt zwei `std::shared_ptr`-Objekte verwendet haben:

  * `std::shared_ptr<AnyAnmimal>` &ndash; Einen Shared-Pointer für das Objekt selbst
  * `std::shared_ptr<AnimalConcept>` &ndash; Einen Shared-Pointer für das Hüllenobjekt

Dies muss so natürlich nicht der Fall sein, 
die betroffenen Objekt können auch *per-value* vorhanden sein.

Die Referenz dieser Objekte wird dann im Hüllenobjekt abgelegt.
Die Hüllenobjekte selbst werden nach wie vor dynamisch erzeugt, in
den Instanzvariablen verwalten sie eine Referenz des umhüllten Objekts:

```cpp
01: class SeeAndSay
02: {
03:     // 'interface'
04:     class AnimalConcept
05:     {
06:     public:
07:         virtual std::string see() const = 0;
08:         virtual std::string say() const = 0;
09:     };
10: 
11:     // derived type(s)
12:     template <typename T>
13:     class AnimalModel : public AnimalConcept
14:     {
15:     private:
16:         const T& m_animal;
17: 
18:     public:
19:         AnimalModel(const T& animal) : m_animal{ animal } {}
20: 
21:         virtual std::string see() const override { return m_animal.see(); }
22:         virtual std::string say() const override { return m_animal.say(); }
23:     };
24: 
25:     // registered animals
26:     std::vector<std::shared_ptr<AnimalConcept>> m_animals;
27: 
28: public:
29:     template <typename T>
30:     void addAnimal(const T& animal)
31:     {
32:         m_animals.push_back(std::make_shared<AnimalModel<T>>(animal));
33:     }
34: 
35:     void seeAndSay(const std::shared_ptr<AnimalConcept>& animal) {
36:         std::cout
37:             << "The " << animal->see() << " says '"
38:             << animal->say() << "' :)." << std::endl;
39:     }
40: 
41:     void print() {
42:         for (const auto& animal : m_animals) {
43:             seeAndSay(animal);
44:         }
45:     }
46: };
47: 
48: static void clientCode()
49: {
50:     SeeAndSay animals;
51: 
52:     Cow aCow{};
53:     Pig aPig{};
54:     Dog aDog{};
55: 
56:     animals.addAnimal(aCow);
57:     animals.addAnimal(aPig);
58:     animals.addAnimal(aDog);
59: 
60:     animals.print();
61: }
```

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp) &ndash; Zusammenfassung aller Quellcode-Beispiel aus dem Text.

---

#### 'Real-World' Beispiel:

In der C++-Standardklassenbibliothek (STL) finden wir zwei Anwendungen des *Type Erasure* Idioms vor:

  * Realisierung von `std::function<>` &ndash; Polymorphe Hülle für unterschiedliche Funktionen.
  * Realisierung von `std::any<T>` &ndash; Typsicherer Container für einzelne Werte.

Eine Realisierung von `std::any<T>` kann
man bei [Vishal Chovatiya](https://vishalchovatiya.com/posts/7-advance-cpp-concepts-idiom-examples-you-should-know/) 
und auch bei [Debby Nirwan](https://towardsdatascience.com/c-type-erasure-wrapping-any-type-7f8511634849) 
nachlesen.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[C++ 'Type Erasure' Explained](https://davekilian.com/cpp-type-erasure.html)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
