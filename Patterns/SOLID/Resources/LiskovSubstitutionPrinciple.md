# Liskovsches Substitutionsprinzip

[Zur�ck](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

&bdquo;Abgeleitete Typen m�ssen durch ihre Basistypen ersetzbar sein, ohne die Korrektheit des Programms zu ver�ndern&rdquo;.

In anderen Worten:
  * Im Zusammenhang mit C++ bedeutet dies, dass Funktionen/Methoden, die Zeiger/Referenzen auf Basisklassen verwenden,
  ohne Nebenwirkungen durch ihre abgeleiteten Klassen ersetzt werden k�nnen.
  * Vereinfacht formuliert kann man sagen, dass das Liskov-Substitutionsprinzip sicherstellt,
  dass der Gebrauch von Vererbung korrekt angewendet wird.


#### Beispiel: Violating the Liskov�s Substitution Principle

Wir betrachten das Liskov-Substitutionsprinzip an einem seiner ber�hmtesten Beispiele.
In der Mathematik ist ein Quadrat ein Rechteck.
Also haben wir es hier mit der &bdquo;ist-ein&rdquo;-Beziehung
(&bdquo;is-a&rdquo;-Relationship) zu tun.

Dies wollen wir nun mit dem Prinzip der *Vererbung* modellieren.
Wenn wir im nachfolgenden Beispiel die Klasse `Square` von `Rectangle` ableiten,
sollte �berall dort ein Quadrat verwendbar sein, wo wir ein Rechteck erwarten.
Dies ist aber so nicht der Fall, wie wir am folgenden Beispiel
erkennen k�nnen:

```cpp
01: struct Rectangle
02: {
03: protected:
04:     size_t m_width;
05:     size_t m_height;
06: 
07: public:
08:     Rectangle(size_t width, size_t height)
09:         : m_width{ width }, m_height{ height } {}
10: 
11:     // getter / setter
12:     size_t getWidth() const { return m_width; }
13:     size_t getHeight() const { return m_height; }
14:     virtual void setWidth(size_t width) { m_width = width; }
15:     virtual void setHeight(size_t height) { m_height = height; }
16: 
17:     // public interface
18:     size_t area() const { return m_width * m_height; }
19: };
20: 
21: struct Square : public Rectangle
22: {
23:     Square(size_t size) : Rectangle{ size, size } {}
24: 
25:     // getter / setter
26:     virtual void setWidth(size_t width) override {
27:         m_width = m_height = width;
28:     }
29: 
30:     virtual void setHeight(size_t height) override {
31:         m_height = m_width = height;
32:     }
33: };
34: 
35: void process(Rectangle& r) {
36:     size_t w = r.getWidth();
37:     r.setHeight(10);
38:     assert((w * 10) == r.area());  // fails for Square <-- !!!
39: }
```

Wie wir sehen k�nnen, haben wir das Liskov-Substitutionsprinzip
in der Funktion `prozess` verletzt.
Daher ist Klasse `Square` kein g�ltiger Ersatz f�r Klasse `Rectangle`.

Aus konzeptioneller Sicht ist der Ansatz, Klasse `Square` von Klasse `Rectangle`
abzuleiten, nicht gut. Selbst wenn dies einer gewissen Anschauung entspricht.
Aber ein Quadrat hat eben keine H�he und keine Breite, sondern eine (Seiten-)L�nge.
Und dies ist genau das Problem, das in dem Beispiel zum Ausdruck kommt.

Eine m�gliche Verbesserung der Funktion `prozess` k�nnte so aussehen:

```cpp
01: void process(Rectangle& r) {
02:     size_t w = r.getWidth();
03:     r.setHeight(10);
04:     if (dynamic_cast<Square*>(&r) != nullptr)
05:         assert((r.getWidth() * r.getWidth()) == r.area());
06:     else
07:         assert((w * 10) == r.area());
08: }
```

Aber auch diesem Code-Fragment haftet ein gewisser &bdquo;unangenehmer Geruch&rdquo; an,
oder wie es im Fachjargon hei�t: *there is a code smell ...*

Wenn in polymorphem Code Anweisungen zur Typpr�fung vorhanden sind
(hier: `dynamic_cast`), dann ist dies mit ziemlicher Sicherheit 
ein Versto� gegen das Liskov-Substitutionsprinzip.
In gutem Quellcode sind derartige �berpr�fungen nicht vorhanden!


#### Beispiel: Respecting the Liskov�s Substitution Principle

```cpp
01: struct Shape
02: {
03:     virtual size_t area() const = 0;
04: };
05: 
06: struct Rectangle : public Shape
07: {
08: private:
09:     size_t m_width;
10:     size_t m_height;
11: 
12: public:
13:     Rectangle(size_t width, size_t height)
14:         : m_width{ width }, m_height{ height } {}
15: 
16:     // getter / setter
17:     size_t getWidth() const { return m_width; }
18:     size_t getWeight() const { return m_height; }
19:     virtual void setWidth(size_t width) { m_width = width; }
20:     virtual void setHeight(size_t height) { m_height = height; }
21: 
22:     // public interface
23:     size_t area() const override { return m_width * m_height; }
24: };
25: 
26: struct Square : public Shape
27: {
28: private:
29:     size_t m_size;
30: 
31: public:
32:     Square(size_t size) : m_size{ size } {}
33: 
34:     // getter / setter
35:     size_t getSize() const { return m_size; }
36:     void setSize(size_t size) { m_size = size; }
37: 
38:     // public interface
39:     virtual size_t area() const override { return m_size * m_size; }
40: };
41: 
42: void process(Shape& s)
43: {
44:     // use polymorphic behaviour only, e.g. area()
45: }
```

In den meisten Einf�hrungen �ber objektorientierte Programmierung
wird Vererbung als &bdquo;ist-ein&rdquo;-Beziehung
mit dem abgeleiteten Objekt diskutiert bzw. angesehen.

Dies ist notwendig, muss aber nicht ausreichend sind.
Es ist passender zu sagen, dass eine Klasse so entworfen werden sollte,
dass sie von einer anderen Klasse erbt, wenn beteiligte Objekte
eine so genannte &bdquo;*is-substitutable-for*&rdquo;-Beziehung zum geerbten Objekt eingehen k�nnen.


#### Vorteile des *Liskovschen Substitutionsprinzips*

  * Code, der sich an das Liskov-Substitutionsprinzip h�lt, ist lose voneinander abh�ngig und f�rdert die Wiederverwendbarkeit von Code.

  * Code, der dem Liskov-Substitutionsprinzip entspricht, ist Code, der die richtigen Abstraktionen in Bezug auf das Prinzip der *Vererbung* vornimmt.

---

## Literaturhinweise

Die Anregungen zu diesem Beispiel finden Sie in

[Liskov�s Substitution Principle in C++](https://vishalchovatiya.com/posts//single-responsibility-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zur�ck](../../../Resources/Readme_03_Design_Principles.md)

---
