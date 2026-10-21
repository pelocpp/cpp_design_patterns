# Dependency Inversion Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

#### Conceptual Example:

[Quellcode](../DIP.cpp)

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
05:     std::string name;
06: };
07: 
08: // low-level <<<<<<<<< -------------------
09: class Relationships
10: {
11: public:
12:     struct Relation
13:     {
14:         std::shared_ptr<const Person> parent;
15:         Relationship                  relation;
16:         std::shared_ptr<const Person> child;
17:     };
18: 
19:     std::vector<Relation> m_relations;
20: 
21:     void addParentAndChild(
22:         std::shared_ptr<const Person> parent,
23:         std::shared_ptr<const Person> child)
24:     {
25:         m_relations.push_back({ std::move(parent), Relationship::Parent, std::move(child) });
26:     }
27: };
28: 
29: // high-level <<<<<<<<< -------------------
30: class FamilyTree
31: {
32: private:
33:     const Relationships& m_relationships;
34: 
35: public:
36:     FamilyTree(const Relationships& relationships)
37:         : m_relationships{ relationships }
38:     {}
39: 
40:     void showChildrenOfJohn()
41:     {
42:         // using structured binding (C++ 17) and range-based for loop (C++ 11)
43:         for (const auto& [parent, relation, child] : m_relationships.m_relations)
44:         {
45:             if (parent->name == "John" && relation == Relationship::Parent) {
46:                 std::println("John has a child called {}", child->name);
47:             }
48:         }
49:     }
50: };
```

Erkennen Sie die Nachteile dieser Implementierung?

  * Wenn zu einem späteren Zeitpunkt in der Klasse `Relationships` der Container der Beziehungen von `std::vector`
    zu `std::set` oder einen anderen Container geändert wird, kann dies Auswirkungen auf die Klasse `FamilyTree` haben:
    Dies stellt definitiv kein gutes Design dar!

  * &bdquo;Low-Level&rdquo;-Module, z.B. Klasse `Relationships` sind direkt mit dem &bdquo;High-Level&rdquo;-Modul gekoppelt (hier: Klasse `FamilyTree`).
    Dies stellt eine Verletzung des *Dependency Inversion Prinzips* dar.

Stattdessen sollten wir vom &bdquo;Low-Level&rdquo;-Modul eine Abstraktion erstellen und &bdquo;Low-Level&rdquo;- und &bdquo;High-Level&rdquo;-Module an diese Abstraktion binden.
Betrachten Sie den folgenden Vorschlag:

#### Beispiel: Respecting the Dependency Inversion Principle

```cpp
01: enum class Relationship { Parent, Child, Sibling };
02: 
03: struct Person
04: {
05:     std::string name;
06: };
07: 
08: // abstraction
09: struct IRelationshipBrowser
10: {
11:     virtual ~IRelationshipBrowser() = default;
12:     virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
13: };
14: 
15: // low-level <<<<<<<<< -------------------
16: class Relationships : public IRelationshipBrowser
17: {
18: private:
19:     struct Relation
20:     {
21:         std::shared_ptr<const Person> parent;
22:         Relationship                  relation;
23:         std::shared_ptr<const Person> child;
24:     };
25: 
26:     std::vector<Relation> m_relations;
27: 
28: public:
29:     void addParentAndChild(
30:         std::shared_ptr<const Person> parent,
31:         std::shared_ptr<const Person> child)
32:     {
33:         m_relations.push_back({ std::move(parent), Relationship::Parent, std::move(child) });
34:     }
35: 
36:     std::vector<Person> findAllChildrenOf(const std::string& name) const override {
37: 
38:         std::vector<Person> result;
39:         for (const auto& [parent, relation, child] : m_relations) {
40:             if (parent->name == name && relation == Relationship::Parent)
41:                 result.push_back(*child);
42:         }
43:         return result;
44:     }
45: };
46: 
47: // high-level <<<<<<<<< -------------------
48: class FamilyTree
49: {
50: private:
51:     const IRelationshipBrowser& m_browser;
52: 
53: public:
54:     FamilyTree(const IRelationshipBrowser& browser)
55:         : m_browser{ browser }
56:     {}
57: 
58:     void showChildrenOfJohn() const {
59: 
60:         std::vector<Person> children{ m_browser.findAllChildrenOf("John") };
61: 
62:         for (const auto& child : children) {
63:             std::println("John has a child called {}", child.name);
64:         }
65:     }
66: };
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

## Zur Namensgebung des Idioms

Der Name &bdquo;*Dependency Inversion*&rdquo; wirkt zunächst widersprüchlich, ergibt aber Sinn, wenn man versteht,
welche Art von Abhängigkeiten &bdquo;umgedreht&rdquo; wird.

Normalerweise hängen in klassischen Programmen die so genannten *High-Level* Module (z.B. Geschäftslogik)
von den *Low-Level* Modulen (z.B. konkreten Implementierungen, Datenbanken, Dateisystemen) ab.

> **Traditionelle Richtung der Abhängigkeit**: *High-Level* &rightarrow; *Low-Level*

Das ist problematisch, weil es das System hart koppelt und Änderungen in Details Auswirkungen weiter &bdquo;oben&rdquo; haben.

*Dependency Inversion* kehrt diese Richtung um:

> **Neue Richtung**: *Low-Level* &rightarrow; *High-Level* (über gemeinsame Abstraktionen)

Das bedeutet:

  * *High-Level* Module hängen nicht mehr direkt von Details ab.
  * Sowohl die *high-level* als auch die *low-level* Module hängen von Abstraktionen (Interfaces, abstrakten Klassen) ab.
  * Die Details implementieren die Abstraktion &rightarrow; sie hängen also von der Abstraktion der höheren Logik ab, nicht umgekehrt.

Das ist die so genannte &bdquo;Inversion&rdquo; der Abhängigkeiten.

---

## Literaturhinweise

Die Anregungen zu diesem Beispiel finden Sie in

[Dependency Inversion Principle in C++](https://vishalchovatiya.com/posts//single-responsibility-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
