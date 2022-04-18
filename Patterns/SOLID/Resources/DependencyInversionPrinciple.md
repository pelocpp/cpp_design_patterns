# Dependency Inversion Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

  * &ldquo;High-Level&rdquo;-Module sollten nicht von &ldquo;Low-Level&rdquo;-Modulen abhängen. Beide sollten von Abstraktionen abhängen.
  * Abstraktionen sollten nicht von Details abhängen. Details sollten von Abstraktionen abhängen.

Die obigen Zeilen mögen zunächst kryptisch erscheinen, wir versuchen sie anhand eines Beispiels zu erläutern.

Was versteht man eigentlich unter &ldquo;High-Level&rdquo;- und &ldquo;Low-Level&rdquo;-Modulen?

  * &ldquo;High-Level&rdquo;-Module &ndash; Beschreiben Operationen, die abstrakter Natur sind und komplexere Logik enthalten. Diese
    Module orchestrieren typischerweise die &ldquo;Low-Level&rdquo;-Module in einer Anwendung.

  * &ldquo;Low-Level&rdquo;-Module &ndash; Beschreiben Implementierungen in einer spezifischeren und individuelleren
    Art und Weise und legen den Fokus mehr auf die Details in einer Anwendung.
    Diese Module werden von den &ldquo;High-Level&rdquo;-Modulen verwendet.

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
09: struct Relationships
10: {
11:     std::vector<std::tuple<Person, Relationship, Person>> m_relations;
12: 
13:     void add_parent_and_child(const Person& parent, const Person& child)
14:     {
15:         m_relations.push_back({ parent, Relationship::Parent, child });
16:         m_relations.push_back({ child, Relationship::Child, parent });
17:     }
18: };
19: 
20: // high-level <<<<<<<<< -------------------
21: struct FamilyTree
22: {
23:     FamilyTree(const Relationships& relationships)
24:     {
25:         for (const auto& [first, relation, second] : relationships.m_relations)
26:         {
27:             if (first.m_name == "John" && relation == Relationship::Parent) {
28:                 std::cout << "John has a child called " << second.m_name << std::endl;
29:             }
30:         }
31:     }
32: };
```

Erkennen Sie die Nachteile dieser Implementierung?

  * Wenn zu einem späteren Zeitpunkt in der Klasse `Relationships` der Container der Beziehungen von `std::vector`
    zu `std::set` oder einem anderen Container geändert wird, kann dies Auswirkungen auf die Klasse `FamilyTree` haben:
    Dies stellt definitiv kein gutes Design dar!

  * &ldquo;Low-Level&rdquo;-Module, z.B. Klasse `Relationships` hängen direkt vom &ldquo;High-Level&rdquo;-Modul ab (hier: Klasse `FamilyTree`).
    Dies stellt eine Verletzung des *Dependency Inversion Prinzips* dar.

Stattdessen sollten wir vom &ldquo;Low-Level&rdquo;-Modul eine Abstraktion erstellen und &ldquo;Low-Level&rdquo;- und &ldquo;High-Level&rdquo;-Module an diese Abstraktion binden.
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
08: // abstraction
09: struct RelationshipBrowser
10: {
11:     virtual std::vector<Person> findAllChildrenOf(const std::string& name) const = 0;
12: };
13: 
14: // low-level <<<<<<<<< -------------------
15: struct Relationships : public RelationshipBrowser
16: {
17:     std::vector<std::tuple<Person, Relationship, Person>> m_relations;
18: 
19:     void add_parent_and_child(const Person& parent, const Person& child) {
20:         m_relations.push_back({ parent, Relationship::Parent, child });
21:         m_relations.push_back({ child, Relationship::Child, parent });
22:     }
23: 
24:     virtual std::vector<Person> findAllChildrenOf(const std::string& name) const override {
25: 
26:         std::vector<Person> result;
27:         for (const auto& [first, rel, second] : m_relations) {
28:             if (first.m_name == name && rel == Relationship::Parent) {
29:                 result.push_back(second);
30:             }
31:         }
32:         return result;
33:     }
34: };
35: 
36: // high-level <<<<<<<<< -------------------
37: struct FamilyTree
38: {
39:     FamilyTree(const RelationshipBrowser& browser) {
40: 
41:         for (const auto& child : browser.findAllChildrenOf("John")) {
42:             std::cout << "John has a child called " << child.m_name << std::endl;
43:         }
44:     }
45: };
```

##### Beachten Sie an dem Quellcode:

  * Egal, ob der Name des &ldquo;Low-Level&rdquo;-Moduls oder eines in diesem Modul enthaltenen Sub-Containers selbst sich ändert,
  das &ldquo;High-Level&rdquo;-Modul oder andere Quellcode-Anteile, die dem *Dependency Inversion Prinzip* folgen, bleiben intakt!

#### Vorteile des *Dependency-Inversion-Prinzips*

  * Effektiv gesehen reduziert das *Dependency Inversion Prinzip* (DIP) die Kopplung zwischen verschiedenen Codeteilen.
  Wir erhalten auf diese Weise wiederverwendbaren Code.

  * Das *Dependency Inversion Prinzip* (DIP) legt nahe, dass die flexibelsten Systeme diejenigen sind, in denen sich Quellecodeabhängigkeiten
  nur auf Abstraktionen, nicht auf Konkretisierungen beziehen!

---

Die Anregungen zu diesem Beispiel finden Sie in

[Open Closed Principle in C++](http://www.vishalchovatiya.com/open-closed-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
