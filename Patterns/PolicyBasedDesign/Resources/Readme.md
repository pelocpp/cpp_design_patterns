# Policy-Based Design

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;*Policies* stellen Schnittstellen f�r konfigurierbare Belange einer Klasse dar.&rdquo;

#### Problem / Motivation

Wir bewegen uns im Problemfeld &bdquo;*Entwurfsentscheidungen*&rdquo; bei der Softwareentwicklung:

  * Stichwort:  &bdquo;*Wie man es macht, macht man es falsch*&rdquo; :).

  * Eine Strategie kann sein: Entscheidungen sollten nicht beim Entwickler einer Klasse liegen, sondern beim Anwender.


#### L�sung:

  * Ziel: Klassen konfigurierbar gestalten.

  * Schaffung einer Auswahlm�glichkeit f�r verschiedene Verhaltensweisen durch den Anwender.
   

Damit sind wir beim Begriff der &bdquo;Policy&rdquo; angekommen:

  * *Policies* sind Schnittstellen f�r konfigurierbare Belange einer Klasse.
  * Genauer: Eine *Policy* ist eine Klasse oder eine Klassenschablone (Template), die eine Schnittstelle als Dienstleistung zu anderen Klassen definiert. 
  * Eine *Policy*-Klasse implementiert die von der *Policy* vorgegebene Schnittstelle.
  * *Policies* sind vom Benutzer der Klasse ausw�hlbar: der Benutzer kann das Verhalten der *Host*-Klasse durch geeignete Auswahl von *Policy*-Klassen/*Policy*-Objekten anpassen.

Die Idee des *Policy-based* Designs kann nun so formuliert werden:

  * Klassen mit komplexem Verhalten werden in eine *Host*-Klasse und mehrere kleinere *Policy*-Klassen zerlegt.
  * Jede *Policy*-Klasse kapselt einen Belang der *Host*-Klasse.
  * Verbindungen der komplexen Klasse mit den *Policy*-Klassen beispielsweise �ber C++ Klassen Templates m�glich.

  
Policies sind vom Benutzer der Klasse ausw�hlbar:

  * Der Benutzer kann also das Verhalten der Host-Klasse durch geeignete Auswahl von *Policy*-Klassen anpassen

---

#### Beispiel: Violating the &bdquo;Deleting Destructor&rdquo; Issue

Dynamisch allokierte Speicherbereiche k�nnen in C++ mit den beiden Anweisungen
`new` oder `new[]` reserviert werden. Hieraus leitet sich f�r die Freigabe des allokierten Speichers
ein kleines Problem bzw. angenehmer formuliert, eine Anforderung an das Programm ab:

  * Speicher wurde mit `new` allokiert &Rightarrow;<br/>Der Speicherbereich ist mit einem Aufruf von `delete`, dem so genannten &bdquo;*Scalar Deleting Destructor*&rdquo; freizugeben.
  * Speicher wurde mit `new[]` allokiert &Rightarrow;<br/>Der Speicherbereich ist mit einem Aufruf von `delete[]`, dem so genannten &bdquo;*Vector Deleting Destructor*&rdquo; freizugeben.

Das ist leichter gesagt, als getan! Nicht immer l�sst sich aus dem Programmcode ableiten,
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
Welche Variante oder Varianten des `delete`-Operators kommen zur Ausf�hrung?

---

#### Beispiel: Respecting the &bdquo;Deleting Destructor&rdquo; Issue

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

Stattdessen wird der �berladene Aufrufoperator `operator()` des 
*Policy*-Objekts mit der Zeigervariablen als Parameter aufgerufen.
Nun ben�tigen wir geeignete *Policy*-Klassen:

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

Schlie�lich betrachten wir das Hauptprogramm:

```cpp
01: void test()
02: {
03:     SmartPtr<int, ScalarDeletePolicy<int>> sp1{ new int{ 123 } };
04:     SmartPtr<int, VectorDeletePolicy<int>> sp2{ new int[5] { 1, 2, 3, 4, 5 } };
05: }
```

---

#### Beispiele zum Policy-Based Design in der STL:

Ein sehr popul�res Beispiel f�r das Policy-Based Design in der STL sind die Speicherallokatoren
der Container-Klassen wie z.B. `std::vector<T>`. Ein `std::vector<T>`-Objekt ben�tigt dynamisch allokierten Speicher.
Es gibt jedoch viele Strategien zur Speicherallokation, von denen jede f�r eine bestimmte Situation am besten geeignet ist.
Wenn die Speicherallokation fest codiert w�re, w�re `std::vector<T>` f�r eine Vielzahl leistungskritischer Anwendungen unbrauchbar.

In der Tat ist die Speicherallokation nicht fest codiert.
Stattdessen gibt es eine *Policy* &ndash; Standardklasse `std::allocator` &ndash; die steuert, wie der Speicher zugewiesen wird:

Siehe [cppreference.com](https://en.cppreference.com/w/cpp/memory/allocator)

Die Klasse `std::vector<T>` (wie auch andere C++ Containerklassen) verf�gt neben dem Elementtyp �ber einen zweiten Template-Parameter. 
Dieser beschreibt die *Policy* f�r die Speicherallokation.

Sie k�nnen Ihre eigene Klasse(n) mit bestimmten Member-Funktionen definieren,
so dass diese die Anforderungen an einen C++ Speicherallokator erf�llen.
Die C++ Standardklasse `std::vector<T>` verwendet dann Ihre Vorstellungen
f�r die Allokation des Speichers.

---

#### Typische Realisierung von *Policy*-Klassen

Es gibt zwei typische Vorgehensweisen zur Implementierung von *Policy*-Klassen: Komposition und Vererbung.

#### Komposition

Wir stellen eine Klasse `Logger` vor, deren Ausgaben mit Hilfe einer *Policy*-Klasse in eine Datei oder auf die Konsole
gelenkt werden k�nnen.
Die `log`-Methode der `Logger`-Klasse greift f�r Ausgaben auf das *Policy*-Objekt zur�ck. Hierin
dr�ckt sich die Konfigurierbarkeit der `Logger`-Klasse aus:

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

Wir m�ssen nur die Host-Klasse betrachten. Die beiden *Policy*-Klassen
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
Der Compiler unterscheidet beim &ndash; ersten  &ndash; �bersetzungsvorgang 
zwischen Bezeichnern, die von den Template Parametern abh�ngen oder nicht: 

```
'write': function declaration must be available as none of the arguments depend on a template parameter.
```

Dieses Problem muss man dadurch l�sen, dass man dem Compiler explizit angibt,
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
Dazu machen wir zun�chst eine m�glicherweise �berraschende Aussage:
Die beiden Varianten unterscheiden sich in der Gr��e ihrer beteiligten Objekte (Anzahl Bytes im Speicher)!
Woran liegt das?

Die beiden soeben betrachteten *Policy*-Objekte haben keine Instanzvariablen.
Die Anzahl Bytes dieser Objekte ist jedoch nicht 0, wie man erwarten k�nnte, sondern 1!
�berpr�fen k�nnen wir das mit Testbeispielen der Gestalt

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

Wenn zwei Objekte nacheinander im Speicher liegen, betr�gt der Unterschied der beiden Adressen zwischen ihnen
die Gr��e des ersten Objekts (plus *Padding*, falls erforderlich). 
Um folglich zu verhindern, dass sich die beiden Objekte `p1` und `p2` an derselben Adresse befinden,
verlangt der C++ Standard, dass die Gr��e eines Objekts mindestens 1 Byte ist.

Im Umfeld der Vererbung kommt hier eine interessante Beobachtung ins Spiel:
Wenn beispielsweise die *Policy* `LogToConsole` keine Instanzvariablen besitzt, 
k�nnen wir von der sogenannten &bdquo;Empty Base Class Optimization&rdquo; profitieren.
Sie besagt, dass in diesem Fall eine *Policy*-Klasse *nicht* die Gr��e (Anzahl Bytes) des `Logger`-Objekts erh�ht!

Bei der Komposition von Klassen ist dies eben nicht der Fall,
da `LogToConsole` mindestens ein Byte zur Gr��e des `Logger`-Objekts hinzuf�gt.
Ber�cksichtigt man noch *Padding* und Ausrichtung (*Alignment*) im Speicher,
k�nnten hier gleich eine stattliche Anzahl von Bytes hinzugelangen.

Folglich ist bei vielen *Policy*-Objekten der Footprint einer Anwendung in der Variante mit Vererbung g�nstiger:


```cpp
template <typename TOutputPolicy>
class Logger : private TOutputPolicy
```
---

#### Abgrenzung zu anderen Entwurfsmustern / Programmier-Idiomen:

  * Das *Policy-Based Design* ist ein Programmier-Paradigma,
    das h�ufig als Compile-Time-Variante des *Strategy Patterns* angesehen wird.

---

## Literaturhinweise

Die Anregungen zum Beispiel mit der *SmartPointer*-Klasse sind dem Buch
&bdquo;*Hands-On Design Patterns with C++*&rdquo; von Fedor G. Pikus entnommen, 
siehe dazu auch das [Literaturverzeichnis](../../../Resources/Readme_07_Literature.md).

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
