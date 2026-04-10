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


Es kann leicht passieren, die Funktion `draw_rect` falsch zu verwenden?

Vergleiche die Funktion mit der Funktion `draw_rectangle`.
Der Compiler sichert zu, dass diese nur mit `Point`- oder `Size`-Objekten verwendet werden kann.

*Hinweis*:<br />
Suche im Quellcode nach Funktionen, die viele elementare Datentypen als Argument verwenden:
Diese kann man möglicherweise mit einfachen Strukturen zusammenfassen und auf diese Weise besser typisieren.


### Regel &bdquo;Vor- und Nachbedingungen angeben (falls möglich bzw. vorhanden)&rdquo;




### Regel &bdquo;Verwenden Sie Ausnahmen, um das Fehlschlagen einer Methode zu signalisieren&rdquo;


Warum? Es sollte nicht möglich sein, einen Fehler zu ignorieren,
da dies das Programm oder eine Berechnung in einen undefinierten (oder unerwarteten) Zustand versetzen könnte.

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

Wenn eine Methode ein Funktions- oder Methodentemplate ist, dokumentieren Sie ihre Parameter mit Hilfe von *Concepts*.

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

### Regel &bdquo;Übertrage niemals die *Ownership* (Eigentümerschaft) durch einen *Raw Pointer* (`T*`)&rdquo;


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
10: static void core_guideline_transferring_ownership()
11: {
12:     X* result = compute(123);
13: }
```

Wer löscht den Zeiger auf `X`? Es gibt mindestens zwei Alternativen,
um das Besitzproblem zu lösen:

  * Den Wert zurückgeben, falls möglich (Wertsemantik).
  * Einen Smartpointer verwenden.


### Regel &bdquo;Übergebe kein Array durch einen einzelnen Zeiger.&rdquo;

Das Übergeben von Arrays durch einen einzelnen Zeiger ist recht fehleranfällig:

```cpp
void copy_n(const T* from, T* to, int n);
```

Was passiert, wenn `n` zu groß ist? Undefined Behavior (UB).

Die Lösung für solche Probleme ist eine Utility-Klasse `std::span`:

```cpp
void copy(span<const T> r, span<T> r2);
```

Jedes `std::span` besitzt eine Längenangabe!

```cpp
01: void copy(std::span<const int> from, std::span<int> to) {
02: 
03:     // Safety check: Are both spans the same size?
04:     if (from.size() != to.size()) {
05:         throw std::invalid_argument("spans must be the same size!");
06:     }
07: 
08:     // Efficient data copying
09:     std::copy(from.begin(), from.end(), to.begin());
10: }
```



### Regel &bdquo;Halte die Anzahl der Funktionsargumente gering&rdquo;

Die Anzahl der Funktionsargumente sollte gering gehalten werden.
Es gilt eine einfache Regel: Eine Funktion sollte genau eine Aufgabe erfüllen (*Single Responsibility Rule*).
In diesem Fall reduziert sich die Anzahl der Funktionsargumente automatisch,
was die Verwendung der Funktion vereinfacht.

*Bemerkung*:<br />
Nicht immer wird sich auch von professionellen Entwicklern an diese Regel gehalten.
Die neuen parallelen Algorithmen der Standard Template Library, wie beispielsweise `std::transform_reduce`,
verstoßen häufig gegen diese Regel.


### Regel &bdquo;Vorbedingungen angeben&rdquo;

Wenn möglich, sollten Vorbedingungen, wie etwas dass `x` in `double sqrt(double x)` nicht negativ sein darf,
als Aussage formuliert werden:

```cpp
double sqrt(double x) { Expects(x >= 0); /* ... */ }
```

Das letzte Fragment ist &ndash; noch &ndash; nicht übersetzungsfähig,
mit `assert` bekommt man es hin:

```cpp
01: double sqrt(double x) {
02:     assert(x >= 0);  //  "x may not be negative"
03:     return 0.0;
04: };
```

Verträge (*Contracts*), bestehend aus Vorbedingungen (*Preconditions*), Nachbedingungen(*Postconditions*) und Zusicherungen(*Assertions*),
sind Teil des nächsten C++26-Standards.


### Regel &bdquo;Nachbedingungen angeben&rdquo;

Entsprechend den Argumenten einer Funktion muss man auch über deren mögliche Ergebnisse nachdenken.
Ich ähnlicher Weise zur Überprüfung der Vorbedingungen sollte man auch Vorkehrungen treffen,
die den Nachbedingungen eines Ergebnisses einer Funktion gelten.

*Beispiel*:

Ein schlechtes Interface:

```cpp
int pop(std::vector<int>& v);
```

Was ist unklar?

  * Was passiert, wenn `v` leer ist?
  * Wird das Element entfernt?
  * Welches Element (vorderes oder hinteres)?
  * Wird der Vektor verändert?
  * Ist der Rückgabewert in allen Fällen gültig?

Dies zwingt Benutzer zum Raten oder zum Lesen der Implementierung &RightArrow; schlechte Schnittstelle.

*Beispiel*:

Ein verbessertes Interface:

```cpp
// Removes and returns the last element of v.
// Precondition: !v.empty()
// Postconditions:
//   - The size of v is reduced by 1
//   - The returned value is equal to the previous last element of v

int pop_back(std::vector<int>& v);
```

Die Schnittstelle gibt nun klar an:

  * Was sich ändert (`v.size()` verringert sich)
  * Was das Ergebnis darstellt (letztes Element)
  * Worauf sich der Aufrufer anschließend verlassen kann


### Regel &bdquo;&rdquo;

### Regel &bdquo;&rdquo;


---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
