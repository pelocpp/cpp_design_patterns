# Abstrakte Klassen versus Interfaces

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

#### Grundlagen

Vergleichen wir zunächst die beiden Konzepte von *abstrakten Klassen* und *Schnittstellen*:

  * Eine *Schnittstelle* (*Interface*) besitzt keine Implementierung von Methoden,
  sie besteht ausschließlich aus Methodendeklarationen.
  Natürlich benötigt es Klassen, die eine Schnittstelle implementieren, was wiederum bedeutet,
  das die Methoden der Schnittstelle dann eine Realisierung erhalten.

  * Ein Interface (Schnittstelle) enthält keine Variablen.
  Es gibt von dieser Regel einige Ausnahmen, wie beispielsweise möglicherweise
  die Definition von Konstanten.

  * Eine Klasse, die eine Schnittstelle implementiert,
  muss alle Methoden der Schnittstelle implementieren.

  * *Abstrakte Klassen* können Variablendeklarationen und Methodenimplementierungen und Methodendeklarationen haben.
  Man kann von einer abstrakten Klasse erben, ohne die abstrakten Methoden implementieren zu müssen.
  Im Regelfall implementiert eine abstrakte Klasse einige der Methoden einer Schnittstelle,
  aber nicht alle.

  * Eine abstrakte Klasse kann nicht instanziiert werden.
  Im Regelfall leitet man eine andere Klasse von einer abstrakten Klasse ab.

  * Auch kann man eine Schnittstelle nicht instanziieren.
  Wie beim Versuch, eine abstrakte Klasse zu instanziieren,
  erhält man einen Übersetzungsfehler.

##### Umsetzung in C++

Bevor wir uns ansehen, wie wir die Features *abstract* und *interface* in C++
definieren können, betrachten wir *virtuelle* und *rein virtuelle* Methoden in C++:

  * Eine *virtuelle* Methode in C++ ist eine Methode,
  die in der abgeleiteten Klasse neu definiert werden kann (Vorgang des *Überschreibens*),
  wobei die Verwendung des Schlüsselworts `virtual` bedeutet,
  eine so genannte *späte Bindung* (*late-binding*) an der Methode durchzuführen.

  * Eine *rein virtuelle* Methode in C++ ist eine virtuelle Methode,
  die nicht definiert, sondern nur deklariert wird, also keine Realisierung besitzt.
  Syntaktisch wird der Methodendeklaration am Ende `= 0`  hinzugefügt.

---

Eine **abstrakte Klasse** in C++
  1. muss mindestens eine rein virtuelle Methode haben,
  2. kann implementierte Methoden haben und
  3. kann Variablendeklaration haben.


Eine **Schnittstelle** (*interface*) in C++
  1. hat alle Methoden als rein virtuelle Methoden deklariert,
  2. hat keine Variablendeklarationen.

Siehe Beispiele im Quelltext hierzu.

---

## C++ Core Guidelines: Regeln für die Definition von Schnittstellen

### Regel &bdquo;Definiere eine Schnittstelle exakt&rdquo;

In dieser Regel geht es das Verständnis und damit um die Korrektheit einer Schnittstelle.
Annahmen &ndash; damit sind Vorraussetzungen gemeint &ndash; über die Funktionalität einer Funktion in einer Schnittstelle
müssen zum Ausdruck gebracht werden.

Falls das nicht geschieht, können diese Vorraussetzungen leicht übersehen werden.

*Beispiel*:

```cpp
01: class IMath
02: {
03: public:
04:     virtual ~IMath() = default;
05: 
06:     virtual double round(double d) = 0;
07: };
```

Wie arbeitet die Funktion `round`? Mit Auf- und abrunden oder mit abschneiden?
Bessere Namen für die Funktion `round` wären dann `roundUp`, `roundDown` oder `truncate`.



### Regel &bdquo;Gestalte Schnittstellen präzise und stark typisiert&rdquo;

Datentypen sind die einfachste und expliziteste Dokumentation,
besitzen eine wohldefinierte Semantik und werden durch den Compiler automatisch geprüft.


*Beispiel*:

```cpp
01: // Bad design: what do these four parameters mean? Great opportunities for making mistakes
02: // What do 10, 20 mean?
03: Point p{};
04: void draw_rect(int, int, int, int);
05: draw_rect(p.m_x, p.m_y, 10, 20);
06: 
07: // --------------------------------------------------
08: 
09: // Better design:
10: void draw_rectangle(Point top_left, Point bottom_right);
11: void draw_rectangle(Point top_left, Size height_width);
12: 
13: draw_rectangle(p, Point{ 10, 20 });  // Two corners
14: draw_rectangle(p, Size{ 10, 20 });   // One corner and one size specification
```


Es kann leicht passieren, die Funktion draw_rect falsch zu verwenden?

Vergleiche die Funktion mit der Funktion draw_rectangle.
Der Compiler sichert zu, dass diese nur mit Point- oder Size-Objekten verwendet werden kann.

*Hinweis*:<br />
Suche im Quellcode nach Funktionen, die viele eingebaute Datentypen als Argument verwenden:
Diese kann man möglicherweise mit einfachen Strukturen zusammenfassen und auf diese Weise besser typisieren.


### Regel &bdquo;Vor- und Nachbedingungen angeben (falls möglich bzw. vorhanden)&rdquo;




### Regel &bdquo;Verwenden Sie Ausnahmen, um das Fehlschlagen einer Methode zu signalisieren&rdquo;


Warum? &bdquo;Es sollte nicht möglich sein, einen Fehler zu ignorieren,
da dies das Programm oder eine Berechnung in einen undefinierten (oder unerwarteten) Zustand versetzen könnte.&bdquo;

*Beispiel*:

```cpp
01: // Bad design: returns negative number if output fails.
02: // The return value can be ignored by the caller.
03: // Hint: Attribute [[nodiscard]] helps, but generates only a warning
04: static int someImportantMethod()
05: {
06:     // ...
07:     return -1;
08: }
```

*Beispiel*:

```cpp
01: // Good design:
02: // Throws std::system_error if the thread could not be started.
03: class thread
04: {
05:     template <typename TFunc, typename ... TArgs>
06:     explicit thread(TFunc&& func, TArgs&&... args) {};
07: };
```

### Regel &bdquo;Dokumentieren Sie die Parameter eines Funktions-/Methodentemplates mit *Concepts*&rdquo;

Wenn eine Methode ein Funktions-/Methodentemplate ist, dokumentieren Sie ihre Parameter mit der Hilfe von *Concepts*.

*Concepts* (Schlüsselwörter `concept` und `requires`) sind Prädikate für Templateparameter,
die zur Übersetzungszeit ausgewertet werden.

Ein *Concept* kann die Menge der als Templateparameter akzeptierten Argumente einschränken.

*Beispiel*:

```cpp
01: template<typename Iter, typename Val>
02: requires InputIterator<Iter> && EqualityComparable<ValueType<Iter>>, Val>
03: Iter find(Iter first, Iter last, Val v)
04: {
05:     // ...
06: }
```

### Regel &bdquo;Übertrage niemals die *Ownership* (Eigentümerschaft) durch einen *Raw Pointer* (T*).&rdquo;


Dieser Code weist ein konzeptionelles Problem auf.

```cpp
01: class X {};
02: 
03: static X* compute(int args)
04: {
05:     X* res = new X{};
06:     // ...
07:     return res;
08: }
09: 
10: static void core_guideline_use_exceptions()
11: {
12:     X* result = compute(123);
13: }
```

Wer löscht den Zeiger auf `X`? Es gibt mindestens zwei Alternativen,
um das Besitzproblem zu lösen:

  * Den Wert zurückgeben, falls möglich (Wertsemantik).
  * Einen Smartpointer verwenden.




### Regel &bdquo;&rdquo;

### Regel &bdquo;&rdquo;

### Regel &bdquo;&rdquo;

### Regel &bdquo;&rdquo;

### Regel &bdquo;&rdquo;

### Regel &bdquo;&rdquo;


---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
