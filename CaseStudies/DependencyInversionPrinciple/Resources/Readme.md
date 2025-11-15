# Dependency Inversion Principle

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

#### Motivation

Das &ldquo;Dependency Inversion Principle&rdquo; beschreibt ein Idiom, das zum Entkoppeln von Abhängigkeiten nützlich ist.
Im Wesentlichen bedeutet es, dass auf einem höheren Level angesiedelte
Module nicht von untergeordneten Modulen abhängen sollten.
Stattdessen sollten beide von Abstraktionen abhängen.

C++ bietet zwei Möglichkeiten, die Abhängigkeiten zwischen Klassen umzukehren. Die erste ist der
klassische, polymorphe Ansatz und der zweite verwendet Templates.


#### Aufgabe

Nehmen wir an, Sie modellieren ein Softwareentwicklungsprojekt, das Frontend- und Backend-Entwickler mit einbezieht.
Betrachten Sie zu diesem Zweck das folgende Code-Fragment:


```cpp
01: class FrontEndDeveloper
02: {
03: public:
04:     void developFrontEnd() {
05:         std::cout << "implementing front end ..." << std::endl;
06:     }
07: };
08: 
09: class BackEndDeveloper
10: {
11: public:
12:     void developBackEnd() {
13:         std::cout << "implementing back end ..." << std::endl;
14:     }
15: };
16: 
17: class Project
18: {
19: private:
20:     FrontEndDeveloper m_fed;
21:     BackEndDeveloper m_bed;
22: 
23: public:
24:     void develop() {
25:         m_fed.developFrontEnd();
26:         m_bed.developBackEnd();
27:     }
28: };
29: 
30: void test() {
31: 
32:     Project project{};
33:     project.develop();
34: }
```

  * Welchen Verstoß gegen das &ldquo;Dependency Inversion Principle&rdquo; können Sie erkennen?

  * Wie könnten Sie eine Umkehr der Abhängigkeiten erzielen?


#### Zusatzaufgabe:

Der Einsatz des &ldquo;Dependency Inversion Principles&rdquo;
mit dem virtuellen Methodenaufrufmechnismus ist zur Laufzeit mit Kosten verbunden.

Es gibt eine andere Möglichkeit, Abhängigkeiten umzukehren, die diese Nachteile nicht hat.
Diese Variante verwendet variadische Templates, generische Lambdas (oder Funktoren) sowie `std::variant` und `std::visit`.

---

#### Lösung

[Siehe hier](Solution.md)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

