# Abstrakte Klassen versus Interfaces

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

#### Quelltext

[ConceptualExample.cpp](../ConceptualExample.cpp)<br />
[GuidelinesInterfaces](../GuidelinesInterfaces.cpp)

---

## Inhalt

  * [Wesentliche Merkmale von Abstrakte Klassen und Interfaces](#link1)
    * [Grundlagen](#link2)
    * [Umsetzung in C++](#link3)
  * [Regeln für die Definition von Schnittstellen](#link4)
    * [Regel &bdquo;Gestalte Schnittstellen präzise und stark typisiert&rdquo;](#link5)
    * [Regel &bdquo;Vorbedingungen angeben&rdquo;](#link6)
    * [Regel &bdquo;Nachbedingungen angeben&rdquo;](#link7)
    * [Regel &bdquo;Virtueller Basisklassendestruktor&rdquo;](#link8)
    * [Regel &bdquo;Non-Virtual Interface (NVI) Pattern&rdquo;](#link9)
    * [Regel &bdquo;*Interface Segregation Principle* (ISP)&rdquo;](#link10)
    * [Regel &bdquo;Verwenden Sie Ausnahmen, um das Fehlschlagen einer Methode zu signalisieren&rdquo;](#link11)
    * [Regel &bdquo;Dokumentieren Sie die Parameter eines Funktions-/Methodentemplates mit *Concepts*&rdquo;](#link12)
    * [Regel &bdquo;Übertrage niemals die *Ownership* (Eigentümerschaft) durch einen *Raw Pointer* (`T*`)&rdquo;](#link13)
    * [Regel &bdquo;Übergebe kein Array durch einen einzelnen Zeiger.&rdquo;](#link14)
    * [Regel &bdquo;Halte die Anzahl der Funktionsargumente gering&rdquo;](#link15)
  * [Literaturhinweise](#link16)

---

## Wesentliche Merkmale von Abstrakte Klassen und Interfaces <a name="link1"></a>

### Grundlagen <a name="link2"></a>

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

### Umsetzung in C++ <a name="link3"></a>

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

## Regeln für die Definition von Schnittstellen <a name="link4"></a>

### Regel &bdquo;Gestalte Schnittstellen präzise und stark typisiert&rdquo; <a name="link5"></a>

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

Es kann leicht passieren, die Funktion `draw_rect` falsch zu verwenden!

Vergleiche die Funktion mit der Funktion `draw_rectangle`:
Der Compiler sichert zu, dass diese nur mit `Point`- oder `Size`-Objekten verwendet werden kann.

*Hinweis*:<br />
Suche im Quellcode nach Funktionen, die viele elementare Datentypen als Argument verwenden:
Diese kann man möglicherweise mit einfachen Strukturen zusammenfassen und auf diese Weise besser typisieren.

Weitere Aspekte, die zur Definition einer Schnittstelle zählen:

Ein Interface ist ein Versprechen. Es ist daher genau zu überlegen, wie die Methoden definiert werden:

  * Darf die Methode nullptr zurückgeben?
  * Welche Exceptions sind erlaubt?
  * Ist die Methode `const`? Interfaces sollten so oft wie möglich `const` sein, auf diese Weise können Seiteneffekte minimiert werden.

---

### Regel &bdquo;Vorbedingungen angeben&rdquo; <a name="link6"></a>

Wenn möglich, sollten Vorbedingungen, wie etwa dass `x` in `double sqrt(double x)` nicht negativ sein darf,
als Aussage formuliert werden:

```cpp
double sqrt(double x) { expects(x >= 0); /* ... */ }
```

Das letzte Fragment ist &ndash; noch &ndash; nicht übersetzungsfähig,
mit `assert` bekommt man es aber hin:

```cpp
01: double sqrt(double x) {
02:     assert(x >= 0);  //  "x may not be negative"
03:     return 0.0;
04: };
```

Verträge (*Contracts*), bestehend aus Vorbedingungen (*Preconditions*), Nachbedingungen (*Postconditions*) und Zusicherungen (*Assertions*)
sind Teil des nächsten C++26-Standards.

---

### Regel &bdquo;Nachbedingungen angeben&rdquo; <a name="link7"></a>

Entsprechend den Argumenten einer Funktion muss man auch über deren mögliche Ergebnisse nachdenken.
In ähnlicher Weise zur Überprüfung der Vorbedingungen sollte man auch Vorkehrungen treffen,
die den Werten eines Ergebnisses einer Funktion gelten.
Es sind geeignete &bdquo;Nachbedingungen&rdquo; zu formulieren.

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
  * Was das Ergebnis darstellt (den Wert des letzten Elements)
  * Worauf sich der Aufrufer anschließend verlassen kann

---


### Regel &bdquo;Virtueller Basisklassendestruktor&rdquo; <a name="link8"></a>

Das ist eine der wichtigsten Regel: Ein Interface benötigt immer einen Eintrag

```cpp
virtual ~IMyInterface() = default;
```

Ohne diesen Eintrag riskiert man Memory Leaks, wenn ein Objekt über einen Interface-Zeiger gelöscht wird.

Wir betrachten das folgende Beispiel:

```cpp
01: class Base
02: {
03: public:
04:     ~Base()
05:     {
06:         // do some important cleanup in class Base
07:         std::println("d'tor Base");
08:     }
09: 
10:     // some virtual methods
11:     virtual void doSomething() {}
12: };
```

und eine davon abgeleitete Klasse `Derived`:

```cpp
01: class Derived : public Base
02: {
03: public:
04:     ~Derived()
05:     {
06:         // do some important cleanup in class Derived
07:         std::println("d'tor Derived");
08:     }
09: };
```

Wir verwenden beide Klassen `Base` und `Derived` nun wie folgt:

```cpp
Base* b = new Derived();
delete b; // here's the problem!
```

Welche Ausgaben in der Konsole erwarten Sie? Sie werden überrascht sein:

```
d'tor Base
```

Da der Destruktor von `Base` nicht virtuell ist und `b` ein `Base*`-Zeiger ist,
der auf ein von `Base` abgeleitetes Objekt zeigt, hat die Anweisung `delete b` ein undefiniertes Verhalten.

In den meisten Implementierungen wird der Aufruf des Destruktors wie jeder nicht virtuelle Code aufgelöst,
was bedeutet, dass der Destruktor der Basisklasse aufgerufen wird,
jedoch nicht der der abgeleiteten Klasse, was zu Ressourcenleaks führen kann!

Zusammenfassend lässt sich sagen, dass Destruktoren einer Basisklasse immer virtuell deklariert sein sollten,
wenn sie auf Grund eines polymorphen Szenarios aufgerufen werden sollten.

Wenn Sie in unserem Beispiel den Destruktor von `Base` in 

```
01: virtual ~Base()
02: {
03:     // do some important cleanup in class Base
04:     std::println("d'tor Base");
05: }
```

abändern, also nur das Schlüsselwort `virtual` hinzufügen, lautet die Programmausgabe wie gewünscht

```
d'tor Derived
d'tor Base
```

---

### Regel &bdquo;*Non-Virtual Interface* (NVI) Pattern&rdquo; <a name="link9"></a>

Anstatt virtuelle Methoden direkt public zu machen, nutze das Non-Virtual Interface (NVI) Pattern.

  * Public Methode: Ist nicht virtuell. Hier werden Pre-Conditions, z. B. `assert(ptr != nullptr)` und Post-Conditions, überprüft.
  * Private/Protected Methode: Ist rein virtuell (*pure virtua*l). Hier implementieren Erben die Logik.


Wir betrachten zum *Non-Virtual Interface* (NVI) Pattern ein konkretes Beispiel.

Dabei trennen wir die Schnittstelle (was aufgerufen wird) von der Implementierung (was überschrieben wird).

Das erlaubt es, Pre- und Post-Conditions an einer zentralen Stelle zu erzwingen, ohne dass jede abgeleitete Klasse diese neu implementieren muss.

```cpp
01: class LoggerInterface {
02: public:
03:     // 1. Virtual Destructor: Required for interfaces
04:     virtual ~LoggerInterface() = default;
05: 
06:     // 2. Public API (Non-virtual): This is where the pre/post conditions reside
07:     void log(const std::string& message)
08:     {
09:         // Pre-Condition: Message must not be empty
10:         assert(!message.empty() && "Log-Message must not be empty!");
11: 
12:         // Call the actual logic
13:         do_log(message);
14: 
15:         // Post-Condition (Example): Increment counter or check status
16:         std::println("[Audit: Log entry processed]");
17:     }
18: 
19: protected:
20:     // 3. Private/Protected Implementation (Purely Virtual)
21:     // Derived classes only override this part.
22:     virtual void do_log(const std::string& message) = 0;
23: };
24: 
25: // A Concrete Implementation
26: class ConsoleLogger : public LoggerInterface {
27: protected:
28:     void do_log(const std::string& message) override
29:     {
30:         std::println("Console: {}", message);
31:     }
32: };
33: 
34: static void guideline_non_virtual_interface_pattern()
35: {
36:     ConsoleLogger myLogger;
37: 
38:     LoggerInterface* interface = &myLogger;
39: 
40:     // The call goes through the base class:
41:     // Within the base class call, the overridden methods are dispatched
42:     interface->log("System gestartet");
43:     // interface->log(""); // Would trigger the assert
44: }
```

---

### Regel &bdquo;*Interface Segregation Principle* (ISP)&rdquo; <a name="link10"></a>

Halten Sie die Anzahl der Methoden in einem Interfaces klein.
Anstatt ein "*God-Interface*" mit 20 Methoden zu bauen, erstellen Sie lieber drei oder mehrere kleinere Schnittstellen.

Klassen können in C++ problemlos von mehreren Interfaces erben. Das hält den Code entkoppelt.

---

### Regel &bdquo;Verwenden Sie Ausnahmen, um das Fehlschlagen einer Methode zu signalisieren&rdquo; <a name="link11"></a>

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

---

### Regel &bdquo;Dokumentieren Sie die Parameter eines Funktions-/Methodentemplates mit *Concepts*&rdquo; <a name="link12"></a>

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

---

### Regel &bdquo;Übertrage niemals die *Ownership* (Eigentümerschaft) durch einen *Raw Pointer* (`T*`)&rdquo; <a name="link13"></a>

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
10: static void guideline_transferring_ownership()
11: {
12:     X* result = compute(123);
13: }
```

Wer löscht den Zeiger auf `X`? Es gibt mindestens zwei Alternativen,
um das Besitzproblem zu lösen:

  * Den Wert zurückgeben, falls möglich (Wertsemantik).
  * Einen Smartpointer verwenden.


Wenn Smart Pointer in der Methodensignatur verwendet werden, ist klargestellt, wer den Speicher verwaltet.

*Beispiel*:

```cpp
virtual void process(std::unique_ptr<Data> data) = 0;
```

Besitz geht an die Methode `process` über.


*Beispiel*:

```cpp
virtual void observe(const Data& data) = 0;
```

Die Methode `observe` hat nur einen lesender Zugriff auf die Daten.


---

### Regel &bdquo;Übergebe kein Array durch einen einzelnen Zeiger.&rdquo; <a name="link14"></a>

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


### Regel &bdquo;Halte die Anzahl der Funktionsargumente gering&rdquo; <a name="link15"></a>

Die Anzahl der Funktionsargumente sollte gering gehalten werden.
Es gilt eine einfache Regel: Eine Funktion sollte genau eine Aufgabe erfüllen (*Single Responsibility Rule*).
In diesem Fall reduziert sich die Anzahl der Funktionsargumente automatisch,
was die Verwendung der Funktion vereinfacht.

*Bemerkung*:<br />
Nicht immer wird sich auch von professionellen Entwicklern an diese Regel gehalten.
Die neuen parallelen Algorithmen der Standard Template Library, wie beispielsweise `std::transform_reduce`,
verstoßen häufig gegen diese Regel.

---

## Literaturhinweise <a name="link16"></a>

Einige der Anregungen zur Gestaltung der Definition von Schnittstellen stammen aus

[C++ Core Guidelines: Interfaces I](https://www.modernescpp.com/index.php/c-core-guidelines-interfaces/).

oder

[C++ Core Guidelines: Interfaces II](https://www.modernescpp.com/index.php/c-core-guidelines-interfaces-ii/).

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
