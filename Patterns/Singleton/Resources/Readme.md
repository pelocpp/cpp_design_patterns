# Singleton Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_singleton_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Das *Singleton Pattern* ist ein Entwurfsmuster, mit dem sichergestellt wird, dass es zu einer Klasse nur eine einzige Instanz gibt.&rdquo;

Immer wenn neue Objekte einer Singleton-Klasse ben�tigt werden, wird die zuvor erstellte Einzelinstanz bereitgestellt.

#### Problem:

In einigen F�llen ist es wichtig, zu einer konkreten Klasse maximal nur eine Instanz zu haben.
Zum Beispiel dann, wenn man nur einen einzigen globalen Zugriffspunkt
auf eine begrenzte Ressource ben�tigt. 

W�rde man eine derartige globale Variable erstellen, die kopiert wird,
w�rde dies zu mehreren Zugriffspunkten f�hren und damit zu m�glichen Dateninkonsistenzen.

*Beispiele*:
  * Stream Objekte von C++: `std::cout`, `std::cin` und `std::cerr`.
  * `HttpContext`-Klasse (Java, C# und andere).
 
Ein weiteres Beispiel f�r Singletons sind Klassen wie zum Beispiel `Color`.
W�rde man &ndash; beispielsweise bei jeder Notwendigkeit im Gebrauch einer Farbe wie *rot* &ndash;
ein entsprechendes `Color`-Objekt erzeugen, w�rde man die Speicherplatzanforderungen
dieser Anwendung nicht mehr in den Griff bekommen. 

Aus diesem Grund gibt es in den entsprechenden Frameworks (J2SE, .NET) f�r diesen
Anwendungsfall zugeschnittene (leicht
modifizierte `getSingleton`) Methoden, die f�r jeweils eine Farbe immer dasselbe Objekt
zur�ckliefern:

```c#
// C# / .NET Framework
public static Color FromArgb (byte a, byte r, byte g, byte b);
```

Nat�rlich setzt dies voraus, dass die Klasse `Color` in derartigen Anwendungsf�llen
*immutable*, also unver�nderbar ist. Andernfalls k�nnte zur Laufzeit aus einer
roten eine blaue Farbe werden, was so sicherlich nicht erw�nscht ist.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Singleton Patterns*.
Es besteht nur aus einer einzigen Klasse:

  * **Singleton**: Diese Klasse besitzt eine statische Methode `getInstance`,
    die pro Aufruf eine einzelne Instanz zur�ckgibt (Referenz, Zeiger),
    die in einer privaten Variablen residiert.

<img src="dp_singleton_pattern_01.svg" width="400">

*Abbildung* 1: Schematische Darstellung des *Singleton Patterns*.

#### Double-Checked Locking / Doppelt �berpr�fte Sperrung:

Eine *doppelt �berpr�fte Sperrung* (englisch *double-checked locking*) ist ein Muster in der Softwareentwicklung,
welches dazu dient, den Zugriff auf ein gemeinsames Objekt durch mehrere gleichzeitig laufende Threads zu regeln.

Die klassische Realisierung der `getInstance`-Methode weist einen kleinen Sch�nheitsfehler auf:

```cpp
01: Singleton* Singleton::getInstance()
02: {
03:     {
04:         std::lock_guard<std::mutex> lock{ m_mutex };
05:         if (m_instance == nullptr) {
06:             m_instance = new Singleton();
07:         }
08:     }
09: 
10:     return m_instance;
11: }
```

Das Erzeugen des (einzigen) Objekts erfolgt thread-sicher, so weit, so gut. Der Sch�nheitsfehler dabei ist,
dass der Zugriff auf das Objekt (pr�ziser: der lesende Zugriff zum Erlangen einer Zeigervariablen, die auf das Objekt zeigt)
�ber dieselbe Methode (!) sehr oft geschehen kann und damit auch
die lesenden Zugriffe auf das Singleton-Objekt thread-sicher ausgef�hrt werden, was �berfl�ssig ist und
unn�tige Rechenzeit beansprucht.

Die `getInstance`-Methode sollte deshalb mit einer so genannten *doppelt �berpr�ften Sperrung*
realisiert werden. Hier wird nur das Erzeugen des Singleton-Objekts thread-sicher ausgef�hrt,
der (lesende) Zugriff auf die Zeigervariable des Objekts wird ohne Sperre durchgef�hrt:

```cpp
01: Singleton* Singleton::getInstance()
02: {
03:     if (m_instance == nullptr)
04:     {
05:         std::lock_guard<std::mutex> lock{ m_mutex };
06:         if (m_instance == nullptr)  // <= NOTE: double-check of m_instance being nullptr
07:         {
08:             m_instance = new Singleton(value);
09:         }
10:     }
11: 
12:     return m_instance;
13: }
```

---

#### Kritik am Singleton Pattern

Aufgrund der globalen Sichtbarkeit und des �ffentlichen Zugriffs k�nnen Singleton-Objekte
�berall in der Implementierung anderer Klassen / im gesamten Programm verwendet werden.

*Mit anderen Worten*:<br />
Ein Singleton ist in der objektorientierten Programmierung wie eine **globale Variable**
in der prozeduralen Programmierung.

Sie k�nnen derartige globale Objekt �berall und jederzeit verwenden:


<img src="dp_singleton_pattern_02_critics.svg" width="700">

*Abbildung* 2: Ein Singleton verh�lt sich wie eine globale Variable!


---

#### Eine Alternative zum Singleton Pattern: *Dependency Injection*

Kurze Wiederholung zur *Dependency Injection*:

> &bdquo;Entkopplung von Komponenten und ihren ben�tigten Diensten auf eine Weise,
  dass die Komponenten weder die Namen dieser Dienste kennen noch wissen,
  wie diese erworben werden k�nnen&rdquo;.


Wir betrachten zun�chst ein Negativbeispiel an Hand einer *Logger*-Klasse.

*Logger*-Klassen stehen exemplarisch f�r 
Service-Klassen, die die M�glichkeit bieten, Log-Eintr�ge zu schreiben.

Solche *Logger*-Klassen werden oft als Singletons implementiert:

```cpp
01: class Logger final
02: {
03: private:
04:     Logger() = default;
05: 
06:     // no copying or moving
07:     Logger(const Logger&) = delete;
08:     Logger(Logger&&) noexcept = delete;
09:     Logger& operator=(const Logger&) = delete;
10:     Logger& operator=(Logger&&) noexcept = delete;
11: 
12: public:
13:     static Logger& getInstance()
14:     {
15:         static Logger theLogger{};
16:         return theLogger;
17:     }
18: 
19:     void writeInfoEntry(std::string_view entry) {
20:         std::cout << "[INFO] " << entry << std::endl;
21:     }
22: 
23:     void writeWarnEntry(std::string_view entry) {
24:         std::cout << "[WARNING] " << entry << std::endl;
25:     }
26: 
27:     void writeErrorEntry(std::string_view entry) {
28:         std::cout << "[ERROR] " << entry << std::endl;
29:     }
30: };
;
```

Eine m�gliche Anwendung mit dieser *Logger*-Klasse k�nnte so aussehen:

```cpp
01: class CustomerRepository {
02: public:
03:     Customer findCustomerById(const Identifier& customerId)
04:     {
05:         Logger::getInstance().writeInfoEntry ("findCustomerById called ... ");
06:         // ...
07:         return {};
08:     }
09:     // ...
10: };
11: 
12: void test()
13: {
14:     CustomerRepository customerRepository{ };
15: 
16:     Identifier id{};
17: 
18:     customerRepository.findCustomerById(id);
19: }
```

Jedes Objekt, dass die Dienste eines Logging-Objekts in Anspruch nehmen m�chte,
muss auf dieses einmal existierende Logging-Objekt zugreifen:

<img src="dp_singleton_pattern_03_logger_singleton.svg" width="700">

*Abbildung* 3: Vier dom�nenspezifische Klassen eines E-Commerce Warenhauses h�ngen von einem `Logger`-Singleton Objekt ab.


Wie k�nnen wir uns nun von dem Singleton-Objekt befreien?

Wir wenden das *Dependency Inversion Prinzip* auf folgende Weise an:
Zun�chst f�hren wir eine Abstraktion ein &ndash; eine Schnittstelle `ILoggingFacility`:

```cpp
01: class ILoggingFacility
02: {
03: public:
04:     virtual ~ILoggingFacility() = default;
05:     virtual void writeInfoEntry(std::string_view entry) = 0;
06:     virtual void writeWarnEntry(std::string_view entry) = 0;
07:     virtual void writeErrorEntry(std::string_view entry) = 0;
08: };
```

Auf diese Weise machen wir dann sowohl die `CustomerRepository`-Klasse 
als auch den konkreten Logger von dieser Schnittstelle abh�ngig,
siehe dazu *Abbildung* 4:

<img src="dp_singleton_pattern_04_logger_di_01.svg" width="700">

*Abbildung* 4: Entkopplung der beiden Klassen `CustomerRepository` und `StandardOutputLogger`.

Damit wenden wir uns einer m�glichen Implementierung dieser Schnittstelle zu,
der Klasse `StandardOutputLogger`:

```cpp
01: class StandardOutputLogger : public ILoggingFacility
02: {
03: public:
04:     void writeInfoEntry(std::string_view entry) override {
05:         std::cout << "[INFO] " << entry << std::endl;
06:     }
07: 
08:     void writeWarnEntry(std::string_view entry) override {
09:         std::cout << "[WARNING] " << entry << std::endl;
10:     }
11: 
12:     void writeErrorEntry(std::string_view entry) override {
13:         std::cout << "[ERROR] " << entry << std::endl;
14:     }
15: };
```

Damit fehlt noch die `CustomerRepository`-Klasse. Wir �ndern die vorhandene Klasse wie folgt ab:

  * Zuerst erstellen wir eine neue Instanzvariable vom `std::shared_ptr`-Typ des Schnittstellentyps `ILoggingFacility`.

  * Eine entsprechende Variable wird �ber einen Initialisierungskonstruktor an die Klasse �bergeben.

  * Mit anderen Worten: Wir erlauben, dass eine Instanz einer Klasse, die die `ILoggingFacility`-Schnittstelle implementiert, w�hrend der Erstellung in das `CustomerRepository`-Objekt importiert wird,
    oder wie es im *Dependency Inversion*-Fachjargon hei�t: &bdquo;injiziert&rdquo;.

  * Wir l�schen auch den Standardkonstruktor, da wir nicht zulassen m�chten, dass ein `CustomerRepository`-Objekt ohne Logger erstellt wird.

  * Dar�ber hinaus entfernen wir die direkte Abh�ngigkeit in der Implementierung zum Singleton und verwenden stattdessen den Shared Pointer `m_logger` zum Schreiben von Protokolleintr�gen.



```cpp
01: class CustomerRepository
02: {
03: public:
04:     CustomerRepository() = delete;
05: 
06:     explicit CustomerRepository(const std::shared_ptr<ILoggingFacility>& logger)
07:         : m_logger{ logger }
08:     {}
09:         
10:     Customer findCustomerById(const Identifier& customerId)
11:     {
12:         m_logger->writeInfoEntry("findCustomerById called ... ");
13:         // ...
14:         return {};
15:     }
16: 
17: private:
18:     std::shared_ptr<ILoggingFacility> m_logger;
19: };
```

Betrachten Sie an der letzten Realisierung der Klasse `CustomerRepository`
die Folge dieser Umgestaltung: Die `CustomerRepository`-Klasse ist nicht mehr von einem bestimmten Logger abh�ngig!

Stattdessen ist ein `CustomerRepository`-Objekt nur von einer Abstraktion (Schnittstelle) abh�ngig,
die nun explizit in der Klasse und ihrer Schnittstelle sichtbar ist
(auf Grund der Instanzvariable `m_logger` des Typs `std::shared_ptr<ILoggingFacility>` und auf Grund des Konstruktors, der wiederum eine `std::shared_ptr<ILoggingFacility>`-Variable �bergeben bekommt).

Das bedeutet, dass die `CustomerRepository`-Klasse nun Service-Objekte f�r Protokollierungszwecke akzeptiert, die von *au�en* �bergeben werden.

Wir haben in der Realisierung der `CustomerRepository`-Klasse damit keinen Zugriff auf
ein Singleton-Objekt von *innen* verankert!

<img src="dp_singleton_pattern_05_logger_di_02.svg" width="800">

*Abbildung* 5: `CustomerRepository`-Objekten k�nnen �ber ihren Konstruktor unterschiedliche Logger-Implementierungen zur Verf�gung gestellt werden.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Mit *Double-Checked Locking*

[Quellcode 3](../Singleton_vs_Dependency_Injection.cpp) &ndash; Eine Alternative zum Singleton Pattern: *Dependency Injection*

---

## Weiterarbeit:

Ein seht guter Aufsatz, wie `std::shared_ptr`-, `std::weak_ptr`- und Singleton-Objekte zusammenarbeiten,
kann unter

[Shared Singleton's](http://btorpey.github.io/blog/2014/02/12/shared-singletons/)

nachgelesen werden.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/singleton/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Singleton)

vor.

Die Anregungen zur Betrachtung &bdquo;Eine Alternative zum Singleton Pattern: *Dependency Injection*&rdquo;
stammen aus dem Buch &bdquo;Hands-On Design Patterns with C++&rdquo; von Stephan Roth,
siehe hierzu auch das [Literaturverzeichnis](../../../Resources/Readme_07_Literature.md).

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
