# Dependency Inversion Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

  * &bdquo;High-Level&rdquo;-Module sollten nicht von &bdquo;Low-Level&rdquo;-Modulen abhängen. Beide sollten von Abstraktionen abhängen.
  * Abstraktionen sollten nicht von Details abhängen. Details sollten von Abstraktionen abhängen.

Die obigen Zeilen mögen zunächst kryptisch erscheinen, wir versuchen sie anhand eines Beispiels zu erläutern.

Was versteht man eigentlich unter &bdquo;High-Level&rdquo;- und &bdquo;Low-Level&rdquo;-Modulen?

  * &bdquo;High-Level&rdquo;-Module &ndash; Beschreiben Operationen, die abstrakterer Natur sind und komplexere Logik enthalten. Diese
    Module orchestrieren typischerweise die &bdquo;Low-Level&rdquo;-Module in einer Anwendung.

  * &bdquo;Low-Level&rdquo;-Module &ndash; Beschreiben Implementierungen in einer spezifischeren und individuelleren
    Art und Weise und legen den Fokus mehr auf die Details in einer Anwendung.
    Diese Module werden von den &bdquo;High-Level&rdquo;-Modulen verwendet.

#### Beispiel: Violating the Dependency Inversion Principle

```cpp
01: enum class Relationship { Parent, Child, Sibling };
02: 
03: struct Person
04: {
05:     std::string m_name;
06: };
07: 
08: // low-level <<<<<<<<< -------------------
09: class Relationships
10: {
11: public:
12:     std::vector<std::tuple<Person, Relationship, Person>> m_relations;
13: 
14:     void addParentAndChild(const Person& parent, const Person& child)
15:     {
16:         m_relations.push_back({ parent, Relationship::Parent, child });
17:         m_relations.push_back({ child, Relationship::Child, parent });
18:     }
19: };
20: 
21: // high-level <<<<<<<<< -------------------
22: class FamilyTree
23: {
24: private:
25:     const Relationships& m_relationships;
26: 
27: public:
28:     FamilyTree(const Relationships& relationships) 
29:         : m_relationships{ relationships }
30:     {}
31: 
32:     void showChildrenOfJohn()
33:     {
34:         // using structured binding (C++ 17) and range-based for loop (C++ 11)
35:         for (const auto& [first, relation, second] : m_relationships.m_relations)
36:         {
37:             if (first.m_name == "John" && relation == Relationship::Parent) {
38:                 std::cout << "John has a child called " << second.m_name << std::endl;
39:             }
40:         }
41:     }
42: };
```

Erkennen Sie die Nachteile dieser Implementierung?

  * Wenn zu einem späteren Zeitpunkt in der Klasse `Relationships` der Container der Beziehungen von `std::vector`
    zu `std::set` oder einen anderen Container geändert wird, kann dies Auswirkungen auf die Klasse `FamilyTree` haben:
    Dies stellt definitiv kein gutes Design dar!

  * &bdquo;Low-Level&rdquo;-Module, z.B. Klasse `Relationships` hängen direkt vom &bdquo;High-Level&rdquo;-Modul ab (hier: Klasse `FamilyTree`).
    Dies stellt eine Verletzung des *Dependency Inversion Prinzips* dar.

Stattdessen sollten wir vom &bdquo;Low-Level&rdquo;-Modul eine Abstraktion erstellen und &bdquo;Low-Level&rdquo;- und &bdquo;High-Level&rdquo;-Module an diese Abstraktion binden.
Betrachten Sie den folgenden Vorschlag:

#### Beispiel: Respecting the Dependency Inversion Principle

```cpp
01: enum class Relationship { Parent, Child, Sibling };
02: 
03: struct Person
04: {
05:     std::string m_name;
06: };
07: 
08: // low-level <<<<<<<<< -------------------
09: class Relationships : public IRelationshipBrowser
10: {
11: private:
12:     std::vector<std::tuple<Person, Relationship, Person>> m_relations;
13: 
14: public:
15:     void addParentAndChild(const Person& parent, const Person& child) {
16:         m_relations.push_back({ parent, Relationship::Parent, child });
17:         m_relations.push_back({ child, Relationship::Child, parent });
18:     }
19: 
20:     std::vector<Person> findAllChildrenOf(const std::string& name) const override {
21: 
22:         std::vector<Person> result;
23:         for (const auto& [first, rel, second] : m_relations) {
24:             if (first.m_name == name && rel == Relationship::Parent) {
25:                 result.push_back(second);
26:             }
27:         }
28:         return result;
29:     }
30: };
31: 
32: // high-level <<<<<<<<< -------------------
33: class FamilyTree
34: {
35: private:
36:     const IRelationshipBrowser& m_browser;
37: 
38: public:
39:     FamilyTree(const IRelationshipBrowser& browser) 
40:         : m_browser { browser } 
41:     {}
42: 
43:     void showChildrenOfJohn() {
44: 
45:         std::vector<Person> children{ m_browser.findAllChildrenOf("John") };
46: 
47:         for (const auto& child : children) {
48:             std::cout << "John has a child called " << child.m_name << std::endl;
49:         }
50:     }
51: };
```

Wir betrachten das Redesign in *Abbildung* 1:

<img src="./dp_dependency_inversion.svg" width="800">

*Abbildung* 1: Anwendung des *Dependency Inversion* Prinzips.


##### Beachten Sie an dem Quellcode:

  * Egal, ob sich nun innerhalb des &bdquo;Low-Level&rdquo;-Moduls eine Änderung ergibt (z.B. Austausch eines verwendeten STL-Containers),
  das &bdquo;High-Level&rdquo;-Modul oder andere Quellcode-Anteile, die dem *Dependency Inversion Prinzip* folgen, bleiben intakt!

#### Vorteile des *Dependency-Inversion-Prinzips*

  * Effektiv gesehen reduziert das *Dependency Inversion Prinzip* (DIP) die Kopplung zwischen verschiedenen Codeteilen.
  Wir erhalten auf diese Weise wiederverwendbaren Code.

  * Das *Dependency Inversion Prinzip* (DIP) legt nahe, dass die flexibelsten Systeme diejenigen sind, in denen sich Quellcodeabhängigkeiten
  nur auf Abstraktionen, nicht auf Konkretisierungen beziehen!

---

## Literaturhinweise

Die Anregungen zu diesem Beispiel finden Sie in

[Dependency Inversion Principle in C++](https://vishalchovatiya.com/posts//single-responsibility-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
