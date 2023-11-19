# Policy-Based Design

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;*Policies* stellen Schnittstellen für konfigurierbare Belange einer Klasse dar.&rdquo;

#### Problem / Motivation

Wir bewegen uns im Problemfeld &ldquo;*Entwurfsentscheidungen*&rdquo; bei der Softwareentwicklung:

  * Stichwort:  &ldquo;*Wie man es macht, macht man es falsch*&rdquo; :).

  * Eine Strategie kann sein: Entscheidungen sollten nicht beim Entwickler einer Klasse liegen, sondern beim Anwender.


#### Lösung:

  * Ziel: Klassen konfigurierbar gestalten.

  * Schaffung einer Auswahlmöglichkeit für verschiedene Verhaltensweisen durch den Anwender.
   

Damit sind wir beim Begriff der &ldquo;Policy&rdquo; angekommen:

  * *Policies* sind Schnittstellen für konfigurierbare Belange einer Klasse.
  * Genauer: Eine *Policy* ist eine Klasse oder ein Klassentemplate, die eine Schnittstelle als Dienstleistung zu anderen Klassen definiert. 
  * Eine *Policy*-Klasse implementiert die von der *Policy* vorgegebene Schnittstelle.
  * *Policies* sind vom Benutzer der Klasse auswählbar: der Benutzer kann das Verhalten der *Host*-Klasse durch geeignete Auswahl von *Policy*-Klassen/*Policy*-Objekten anpassen.

Die Idee des *Policy-based* Designs kann nun so formuliert werden:

  * Klassen mit komplexem Verhalten werden in eine *Host*-Klasse und mehrere kleinere *Policy*-Klassen zerlegt.
  * Jede *Policy*-Klasse kapselt einen Belang der *Host*-Klasse.
  * Verbindungen der komplexen Klasse mit den *Policy*-Klassen beispielsweise über C++ Klassen Templates möglich.

  
Policies sind vom Benutzer der Klasse auswählbar:

  * Der Benutzer kann also das Verhalten der Host-Klasse durch geeignete Auswahl von *Policy*-Klassen anpassen

---

#### Beispiel: Violating the &ldquo;Deleting Destructor&rdquo; Issue

Dynamisch allokierte Speicherbereiche können in C++ mit den beiden Anweisungen
`new` oder `new[]` reserviert werden. Hieraus leitet sich für die Freigabe des allokierten Speichers
ein kleines Problem bzw. angenehmer formuliert, eine Anforderung an das Programm ab:

  * Speicher wurde mit `new` allokiert &Rightarrow;<br/>Der Speicherbereich ist mit einem Aufruf von `delete`, dem so genannten &ldquo;*Scalar Deleting Destructor*&ldquo; freizugeben.
  * Speicher wurde mit `new[]` allokiert &Rightarrow;<br/>Der Speicherbereich ist mit einem Aufruf von `delete[]`, dem so genannten &ldquo;*Vector Deleting Destructor*&ldquo; freizugeben.

Das ist leichter gesagt, als getan! Nicht immer lässt sich aus dem Programmcode ableiten,
welcher der beiden `delete`-Aufrufe abzusetzen ist, da man an Hand der Zeigervariablen nicht erkennen kann,
mit welchem `new`-Aufruf der dynamische Speicher angelegt wurde.
Die Konsequenz bei falschem Aufruf ist UB, also *Undefined Behaviour*!

Wir demonstrieren dies an einer ersten, trivialen und folglich auch fehlerhaften Realisierung
einer *Smart-Pointer* Klasse:

```cpp
01: template <typename T>
02: class SmartPtr
03: {
04: private:
05:     T* m_ptr;
06: 
07: public:
08:     // c'tor / d'tor
09:     explicit SmartPtr (T* ptr = nullptr) : m_ptr{ ptr } {}
10: 
11:     ~SmartPtr() {
12:         delete m_ptr;
13:     }
14: 
15:     // operators
16:     T* operator-> () { return m_ptr; }
17:     const T* operator-> () const { return m_ptr; }
18: 
19:     T& operator* () { return *m_ptr; }
20:     const T& operator* () const { return *m_ptr; }
21: 
22: private:
23:     // prevent copy semantics
24:     SmartPtr(const SmartPtr&) = delete;
25:     SmartPtr& operator=(const SmartPtr&) = delete;
26: };
```

Studieren Sie folgendes Anwendungsbeispiel: Erkennen Sie den Fehler im Programm?

```cpp
01: void test() {
02: 
03:     SmartPtr<int> sp1{ new int{ 123 } };
04:     SmartPtr<int> sp2{ new int[5] { 1, 2, 3, 4, 5 } };
08: }
```

Es wird der `new`-Operator zweimal aufgerufen: In der Variante `new` als auch `new[]`.
Welche Variante oder Varianten des `delete`-Operators kommen zur Ausführung?

---

#### Beispiel: Respecting the &ldquo;Deleting Destructor&rdquo; Issue

Wir erweitern die `SmartPtr`-Klasse aus dem letzen Beispiel um ein *Policy*-Objekt:

```cpp
01: template <typename T, typename DeletionPolicy>
02: class SmartPtr
03: {
04: private:
05:     T* m_ptr;
06:     DeletionPolicy m_deletionPolicy;
07: 
08: public:
09:     // c'tor / d'tor
10:     explicit SmartPtr(T* ptr = nullptr, const DeletionPolicy& policy = DeletionPolicy{})
11:         : m_ptr{ ptr }, m_deletionPolicy{ policy } {}
12: 
13:     ~SmartPtr() {
14:         m_deletionPolicy(m_ptr);
15:     }
16: 
17:     // operators
18:     T* operator->() { return m_ptr; }
19:     const T* operator->() const { return m_ptr; }
20: 
21:     T& operator*() { return *m_ptr; }
22:     const T& operator*() const { return *m_ptr; }
23: 
24: private:
25:     // prevent copy semantics
26:     SmartPtr(const SmartPtr&) = delete;
27:     SmartPtr& operator=(const SmartPtr&) = delete;
28: };
```

Wir finden einen zweiten Template-Parameter `DeletionPolicy` vor:
Zu diesem Klassentyp wird in Zeile 6 ein Objekt angelegt; in Zeile 14 wiederum
erfolgt im Aufruf des Destruktors *kein* direkter Aufruf des `delete`-Operators!
Wie denn auch, es ist ja nicht klar, welche der beiden Varianten aufzurufen ist!

Stattdessen wird der überladene Aufrufoperator `operator()` des 
*Policy*-Objekts mit der Zeigervariablen als Parameter aufgerufen.
Nun benötigen wir geeignete *Policy*-Klassen:

```cpp
01: template <typename T>
02: struct ScalarDeletePolicy {
03:     void operator()(T* ptr) const {
04:         delete ptr;
05:     }
06: };
07: 
08: template <typename T>
09: struct VectorDeletePolicy {
10:     void operator()(T* ptr) const {
11:         delete[] ptr;
12:     }
13: };
```

Schließlich betrachten wir das Hauptprogramm:

```cpp
01: void test()
02: {
03:     SmartPtr<int, ScalarDeletePolicy<int>> sp1{ new int{ 123 } };
04:     SmartPtr<int, VectorDeletePolicy<int>> sp2{ new int[5] { 1, 2, 3, 4, 5 } };
05: }
```

---

#### Beispiele zum Policy-Based Design in der STL:

Ein sehr populäres Beispiel für das Policy-Based Design in der STL sind die Speicherallokatoren
der Container-Klassen wie z.B. `std::vector`. Ein `std::vector`-Objekt benötigt dynamisch allokierten Speicher.
Es gibt jedoch viele Strategien zur Speicherallokation, von denen jede für eine bestimmte Situation am besten geeignet ist.
Wenn die Speicherallokation fest codiert wäre, wäre `std::vector` für eine Vielzahl leistungskritischer Anwendungen unbrauchbar.

In der Tat ist die Speicherallokation nicht fest codiert.
Stattdessen gibt es eine *Policy* &ndash; Standardklasse `std::allocator` &ndash; die steuert, wie der Speicher zugewiesen wird:

Siehe [cppreference.com](https://en.cppreference.com/w/cpp/memory/allocator)

Die Klasse `std::vector` (wie auch andere C++ Containerklassen) verfügt neben dem Elementtyp über einen zweiten Template-Parameter. 
Dieser beschreibt die *Policy* für die Speicherallokation.

Sie können Ihre eigene Klasse(n) mit bestimmten Member-Funktionen definieren,
so dass diese die Anforderungen an einen C++ Speicherallokator erfüllen.
Die C++ Standardklasse `std::vector` verwendet dann Ihre Vorstellungen
für die Allokation des Speichers.

---

#### Typische Realisierung von *Policy*-Klassen

Es gibt zwei typische Vorgehensweisen zur Implementierung von *Policy*-Klassen: Komposition und Vererbung.

#### Komposition

Wir stellen eine Klasse `Logger` vor, deren Ausgaben mit Hilfe einer *Policy*-Klasse in eine Datei oder auf die Konsole
gelenkt werden können.
Die `log`-Methode der `Logger`-Klasse greift für Ausgaben auf das *Policy*-Objekt zurück. Hierin
drückt sich die Konfigurierbarkeit der `Logger`-Klasse aus:

```cpp
01: class LogToConsole {
02: public:
03:     void write(const std::string& message) const {
04:         std::cout << message << std::endl;
05:     }
06: };
07: 
08: class LogToFile {
09: public:
10:     void write(const std::string& message) const {
11:         std::ofstream file;
12:         file.open("trace.txt");
13:         file << message << std::endl;
14:         file.close();
15:     }
16: };
17: 
18: template <typename TOutputPolicy>
19: class Logger {
20: public:
21:     void log(const std::string& message) const {
22:         m_policy.write(message);
23:     }
24: 
25: private:
26:     TOutputPolicy m_policy;
27: };
```

*Beispiel*:

```cpp
01: void test() {
02:     Logger<LogToConsole> consoleLogger{};
03:     consoleLogger.log("Important information");
04: 
05:     Logger<LogToFile> fileLogger{};
06:     fileLogger.log("Important information");
07: }
```

#### Vererbung

Wir müssen nur die Host-Klasse betrachten. Die beiden *Policy*-Klassen
sind identisch zum letzten Beispiel:


```cpp
01: template <typename TOutputPolicy>
02: class Logger : private TOutputPolicy {
03: public:
04:     void log(const std::string& mess) const {
05:         write(mess);
06:     }
07: private:
08:     using TOutputPolicy::write;
09: };
```

*Hinweis*: Die Zeile 8 aus dem letzten Code-Fragment ist wichtig, sie kann nicht weggelassen werden!
Klasse `Logger` ist ein Klassentemplate. Der Aufruf von `write` in Zeile 5
wird nicht mit der Vaterklasse `TOutputPolicy` in Verbindung gebracht!
Der Compiler unterscheidet beim &ndash; ersten  &ndash; Übersetzungsvorgang 
zwischen Bezeichnern, die von den Template Parametern abhängen oder nicht: 

```
'write': function declaration must be available as none of the arguments depend on a template parameter.
```

Dieses Problem muss man dadurch lösen, dass man dem Compiler explizit angibt,
in welcher Klasse die Methode `write` anzufinden ist. Oder in anderen Worten:
Der Name der `write`-Methode wird in den aktuellen Scope importiert!

Nun zu einem Beispiel dieser *Policy*-Klasse: Es ist offensichtlich identisch 
mit dem letzten Beispiel:

*Beispiel*:

```cpp
01: void test() {
02:     std::cout << sizeof(LogToConsole) << std::endl;
03:     std::cout << sizeof(LogToFile) << std::endl;
04:
05:     std::cout << sizeof(Logger<LogToConsole>) << std::endl;
06:     std::cout << sizeof(Logger<LogToFile>) << std::endl;
07: }
```

##### Komposition und Vererbung im Vergleich

Welchen Weg sollen wir einschlagen, wenn wir eine *Policy*-Klasse realisieren?
Dazu machen wir zunächst eine möglicherweise überraschende Aussage:
Die beiden Varianten unterscheiden sich in der Größe ihrer beteiligten Objekte (Anzahl Bytes im Speicher)!
Woran liegt das?

Die beiden soeben betrachteten *Policy*-Objekte haben keine Instanzvariablen.
Die Anzahl Bytes dieser Objekte ist jedoch nicht 0, wie man erwarten könnte, sondern 1!
Überprüfen können wir das mit Testbeispielen der Gestalt

```cpp
std::cout << sizeof(LogToConsole) << std::endl;
```

*Ausgabe*:

```
1
```

Diese Festlegung ist notwendig, da jedes Objekt in einem C++&ndash;Programm eine eindeutige Adresse haben muss:

```cpp
LogToConsole p1;      // & p1 = ...
LogToFile p2;         // & p2 may not be & p1 !!!!
```

Wenn zwei Objekte nacheinander im Speicher liegen, beträgt der Unterschied der beiden Adressen zwischen ihnen
die Größe des ersten Objekts (plus *Padding*, falls erforderlich). 
Um folglich zu verhindern, dass sich die beiden Objekte `p1` und `p2` an derselben Adresse befinden,
verlangt der C++ Standard, dass die Größe eines Objekts mindestens 1 Byte ist.

Im Umfeld der Vererbung kommt hier eine interessante Beobachtung ins Spiel:
Wenn beispielsweise die *Policy* `LogToConsole` keine Instanzvariablen besitzt, 
können wir von der sogenannten &ldquo;Empty Base Class Optimization&rdquo; profitieren.
Sie besagt, dass in diesem Fall eine *Policy*-Klasse *nicht* die Größe (Anzahl Bytes) des `Logger`-Objekts erhöht!

Bei der Komposition von Klassen ist dies eben nicht der Fall,
da `LogToConsole` mindestens ein Byte zur Größe des `Logger`-Objekts hinzufügt.
Berücksichtigt man noch *Padding* und Ausrichtung (*Alignment*) im Speicher,
könnten hier gleich eine stattliche Anzahl von Bytes hinzugelangen.

Folglich ist bei vielen *Policy*-Objekten der Footprint einer Anwendung in der Variante mit Vererbung günstiger:


```cpp
template <typename TOutputPolicy>
class Logger : private TOutputPolicy
```
---

#### Abgrenzung zu anderen Entwurfsmustern / Programmier-Idiomen:

  * Das *Policy-Based Design* ist ein Programmier-Paradigma,
    das häufig als Compile-Time-Variante des *Strategy Patterns* angesehen wird.

---

## Literaturhinweise

Die Anregungen zum Beispiel mit der *SmartPointer*-Klasse sind dem Buch
&ldquo;*Hands-On Design Patterns with C++*&rdquo; von Fedor G. Pikus entnommen, 
siehe dazu auch das [Literaturverzeichnis](../../../Resources/Readme_07_Literature.md).

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
