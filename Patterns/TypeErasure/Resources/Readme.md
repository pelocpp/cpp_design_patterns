# Das *Type Erasure* Idiom

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Um einen generischen Container zu erstellen, der eine Vielzahl von konkreten Typen aufnehmen kann.&rdquo;

*Type Erasure* ermöglicht es, verschiedene Datentypen mit einem generischen Interface zu verwenden.

Das Idiom *Type Erasure* ist auch unter dem Namen &ldquo;*Duck Typing*&rdquo; bekannt.
Der Begriff geht auf ein Gedicht von [James Whitcomb Riley](https://de.wikipedia.org/wiki/James_Whitcomb_Riley) zurück:

  * &ldquo;*When I see a bird that walks like a duck and swims like a duck and quacks like a duck, I call that bird a duck.*&rdquo;

Was ist damit gemeint bzw. welchen Zusammenhang gibt es zur objekt-orientierten Programmierung?
Wir stellen uns eine Funktion

<pre>
void acceptsOnlyDucks(Duck& duck);
</pre>

vor, die nur Objekt des Types `Duck` akzeptiert.
In statisch typisierten Sprachen wie C++ kann diese Funktion mit Objekten aufgerufen werden,
deren Typ sich von `Duck`  abgeleitet.

Es gibt aber auch andere Programmiersprachen wir beispielsweise Python.
Hier könnten hingegen alle Datentypen verwendet werden, die sich wie ein Objekt des Typs `Duck` &ldquo;*verhalten*&rdquo;.

Dies soll heißen: Wenn ein Vogel sich wie eine Ente verhält, dann ist es eine Ente.
Ein Sprichwort in Python bringt das verschärft auf den Punkt: &ldquo;*Don't ask for permission, ask for forgiveness.*&rdquo;.

Etwas mehr vor einem programmiersprachlichen Hintergrund formuliert bedeutet das:
Wir rufen eine Funktion `acceptsOnlyDucks` mit einem Vogel auf und hoffen auf das Beste :)

Geht irgendetwas schief, dann gibt es immer noch die Möglichkeiten des Exception Handlings.
Sprachlich gibt es diese Vorgehensweise in Python &ndash; und mit etwas Aufwand auch in C++,
wie wir in den folgenden Beispielen sehen werden:

#### Motivation: *Polymorphismus mit Schnittstellen*
 
Wir betrachten zunächst den klassischen Weg des *Polymorphismus mit Schnittstellen*.
Zunächst definieren wir eine Schnittstelle, die ausschließlich aus rein virtuellen Methoden besteht.

Anschließend erstellen wir für jede Implementierung, die diese Schnittstelle verwenden möchte,
eine Unterklasse, die von der Basisklasse (Schnittstellenklasse) erbt und ihre Methoden implementiert.

```cpp
01: class Animal
02: {
03: public:
04:     virtual std::string see() const = 0;
05:     virtual std::string say() const = 0;
06: };
07: 
08: class Cow : public Animal
09: {
10: public:
11:     std::string see() const { return "cow"; }
12:     std::string say() const { return "moo"; }
13: };
14: 
15: class Pig : public Animal
16: {
17: public:
18:     std::string see() const { return "pig"; }
19:     std::string say() const { return "oink"; }
20: };
21: 
22: class Dog : public Animal
23: {
24: public:
25:     std::string see() const { return "dog"; }
26:     std::string say() const { return "woof"; }
27: };
28: 
29: void seeAndSay(const std::shared_ptr<Animal> animal)
30: {
31:     std::cout 
32:         << "The " << animal->see() << " says '"
33:         << animal->say() << "' :)." << std::endl;
34: }
35: 
36: void clientCode()
37: {
38:     std::shared_ptr<Animal> aCow = std::make_shared<Cow>();
39:     std::shared_ptr<Animal> aPig = std::make_shared<Pig>();
40:     std::shared_ptr<Animal> aDog = std::make_shared<Dog>();
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

Dies ist noch kein Hinderungsgrund, nicht auf eine andere Weise das Ziel zu erreichen.
Mit Templates lassen sich Datentypen *polymorph machen*:

```cpp
01: template <typename T>
02: void seeAndSay(const std::shared_ptr<T> animal)
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
08: void clientCode()
09: {
10:     std::shared_ptr<Dog> aDog = std::make_shared<Dog>();
11:     seeAndSay<Dog>(aDog);
12: }
```

#### Motivation: *Nachteile von Polymorphismus mit Templates*
 
Objekte unterschiedlichen Typs lassen sich nicht &ndash; ohne Weiteres &ndash; in einem Container / Array ablegen:

```cpp
std::shared_ptr<Animal> aCow = std::make_shared<Cow>();
std::shared_ptr<Animal> aPig = std::make_shared<Pig>();
std::shared_ptr<Animal> aDog = std::make_shared<Dog>();

??? animals[] = { aCow, aPig, aDog };
```

Mit dem Ansatz des *Polymorphismus mit Templates* lässt ein solches Array nicht erstellen,
da es keinen gemeinsamen Basisklassentyp für das Array gibt.

#### Skizzierung eines Lösungsansatzes:

Wenn wir für die vorliegenden Objekt nicht die gewünschte Vererbungshierarchie haben
und wenn wir die Datentypen der Objekte nicht ändern können,
dann könnten wir zumindest eine eigene Vererbungshierarchie
bestehend aus Wrapper-Objekten (Hüllenobjekte) aufbauen.

Das heißt, wir definieren unsere eigene Schnittstelle (hier: `MyAnimal`) und implementieren sie mehrfach.

Jede Implementierung der Schnittstelle umschließt eine Klasse `Cow`, eine Klasse `Pig` oder eine Klasse `Dog`
und ruft diese für alle virtuellen Methoden auf.

Dann erstellen wir Wrapper-Objekte, die von `MyAnimal` erben.
Jeder Wrapper tut nichts weiter als das &ldquo;echte&rdquo; zugrunde liegende Objekt aufzurufen:

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
31:     Cow m_cow;
32: 
33: public:
34:     std::string see() const { return m_cow.see(); }
35:     std::string say() const { return m_cow.say(); }
36: };
37: 
38: class MyPig : public MyAnimal
39: {
40:     Pig m_pig;
41: 
42: public:
43:     std::string see() const { return m_pig.see(); }
44:     std::string say() const { return m_pig.say(); }
45: };
46: 
47: class MyDog : public MyAnimal
48: {
49:     Dog m_dog;
50: 
51: public:
52:     std::string see() const { return m_dog.see(); }
53:     std::string say() const { return m_dog.say(); }
54: };
55: 
56: void seeAndSay(const std::shared_ptr<MyAnimal> animal)
57: {
58:     std::cout
59:         << "The " << animal->see() << " says '"
60:         << animal->say() << "' :)." << std::endl;
61: }
62: 
63: void clientCode()
64: {
65:     std::shared_ptr<MyAnimal> aCow = std::make_shared<MyCow>();
66:     std::shared_ptr<MyAnimal> aPig = std::make_shared<MyPig>();
67:     std::shared_ptr<MyAnimal> aDog = std::make_shared<MyDog>();
68: 
69:     std::vector<std::shared_ptr<MyAnimal>> animals = { aCow , aPig , aDog };
70: 
71:     for (const auto& animal : animals) {
72:         seeAndSay(animal);
73:     }
74: }
```

Das funktioniert, aber es gibt einen eklatanten Nachteil: Wir müssen eine Wrapper-Klasse (wie Klasse `MyCow`)
für jeden konkreten Typ definieren, den wir verpacken möchten (zum Beispiel Klasse `Cow`).

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
10:     std::string see() const { return m_animal.see(); }
11:     std::string say() const { return m_animal.say(); }
12: };
```

#### Das *Type Erasure* Idiom

Das, was wir im letzten Abschnitt gebaut haben, ist die Grundlage des &ldquo;*Type Erasure*&rdquo; Idioms.
Alles, was noch zu erledigen ist, ist, all diese Maschinerie hinter einer anderen Klasse zu verstecken,
damit ein Aufrufer sich nicht mit diesen benutzerdefinierten Schnittstellen und Vorlagen befassen muss:

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
21:         std::string see() const { return m_animal->see(); }
22:         std::string say() const { return m_animal->say(); }
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
35:     void seeAndSay(const std::shared_ptr<MyAnimal> animal) {
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
48: void clientCode()
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

#### *Type Erasure* Nomenklatur

Die im letzten Abschnitt verwendeten Bezeichner `MyAnimal` und `AnimalWrapper` haben Standardnamen:

  * `MyAnimal` ist ein Beispiel eines *Type Erasure* **Konzepts**: Klasse `Concept`
  * `AnimalWrapper` ist ein Beispiel eines *Type Erasure* **Modells**: Klasse `Model`

Ein **Konzept** beschreibt die Schnittstelle, gegen die wir in der Hüllenklasse programmieren müssen.

Ein **Modell** ist ein auf Templates basierendes Wrapper-Objekt, das die **Konzept**-Schnittstelle implementiert
und alle Konzept-Methoden an den zugrunde liegenden konkreten Typ weiterleitet.

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
21:         std::string see() const { return m_animal->see(); }
22:         std::string say() const { return m_animal->say(); }
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
35:     void seeAndSay(const std::shared_ptr<AnimalConcept> animal) {
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
48: void clientCode()
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

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp) &ndash; Sehr einfaches Beispiel

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[C++ 'Type Erasure' Explained](https://davekilian.com/cpp-type-erasure.html)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---




