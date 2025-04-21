# RAII Idiom

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Ziel / Absicht

**RAII** (*Resource Acquisition Is Initialization*) ist ein Programmieridiom (Paradigma), das auf 
Bjarne Stroustrup und Andrew Koenig zurückzuführen ist. Die Idee ist, eine Ressource
(Speicherbereich auf der Halde (*Heap Memory*), Datei, Socket, Mutex, ...) an ein Objekt zu binden
und den Mechanismus der Objektkonstruktion und -destruktion  (Konstruktor, Destruktor) zu nutzen,
um  Ressourcen in einem Programm automatisch zu verwalten.

#### Prinzip

Jedes Mal, wenn wir eine Ressource erwerben wollen, tun wir dies, indem wir ein Objekt erstellen,
das diese Ressource besitzt. Wann immer das Objekt den Gültigkeitsbereich verlässt, wird die Ressource
automatisch freigegeben.

#### Zur Namensgebung

&bdquo;RAII&rdquo; steht für &bdquo;**Resource Acquisition is Initialization**&rdquo;
und ist aus meiner Sicht eine Fehlbezeichnung:
Es geht bei diesem Idiom weder um die Beschaffung von Ressourcen
noch um die Initialisierung eines Objekts.

Im Mittelpunkt steht die deterministische Freigabe der Ressource &ndash; und damit 
in C++ die Destruktion eines Hüllenobjekts (Freigabe des dazugehörigen Speicherbereichs und Aufruf eines Destruktors).

Eine bessere, verständlichere Bezeichnung für das Idiom
wäre zum Beispiel &bdquo;**Scope-Bound Resource Management**&rdquo;.

Der Name RAII ist allerdings gesetzt, es macht wenig Sinn,
sich hierüber zu viele Gedanken zu machen.


#### Lösung

Wir betrachten das Prinzip einer RAII-verwalteten Ressource an Hand einer Folge von Code-Beispielen:

##### 1. Eine RAII-konforme Klasse

```cpp
01: template <class TFinalizer>
02: class RAII {
03: public:
04:     // c'tor
05:     explicit RAII(TFinalizer finalizer)
06:         : m_finalizer{ finalizer }
07:     {}
08: 
09:     // d'tor
10:     ~RAII() {
11:         m_finalizer();
12:     }
13: 
14:     // prevent copy semantics
15:     RAII(const RAII&) = delete;
16:     RAII& operator= (const RAII&) = delete;
17: 
18: private:
19:     TFinalizer m_finalizer;
20: };
```

---

##### 2. Einfache Anwendung eines RAII-Objekts (*Compound-Statement* / *Block*)

```cpp
01: void test()
02: {
03:     {
04:         Dummy* ptr = new Dummy{ 1 };
05:         if (ptr == nullptr) {
06:             return;
07:         }
08: 
09:         RAII raii{ [&] () { delete ptr; } };
10:     }
11: 
12:     std::cout << "Done." << std::endl;
13: }
```

###### Ausgabe

```
c'tor Dummy [1]
d'tor Dummy [1]
Done.
```

---

##### 3. Vorzeitiges Verlassen einer Wiederholungsschleife

```cpp
01: void test()
02: {
03:     // test RAII idiom upon a loop break
04:     do {
05:         Dummy* ptr = new Dummy{ 1 };
06:         if (ptr == nullptr) {
07:             break;
08:         }
09: 
10:         RAII raii{ [&] () { delete ptr; } };
11:         break;
12:     }
13:     while (false);
14: 
15:     std::cout << "Done." << std::endl;
16: }
```

###### Ausgabe

```
c'tor Dummy [1]
d'tor Dummy [1]
Done.
```

---

##### 4. Verhalten des RAII-Idioms bei Eintreten einer Ausnahme (*Exception*)

```cpp
01: void test()
02: {
03:     // test RAII idiom upon exception being thrown
04:     try {
05:         Dummy* ptr = new Dummy{ 1 };
06:         if (ptr == nullptr) {
07:             return;
08:         }
09: 
10:         RAII raii{ [&]() { delete ptr; } };
11:         throw 99;
12:     }
13:     catch (int n) {
14:         std::cout << "Exception " << n << " occurred!" << std::endl;
15:     }
16: 
17:     std::cout << "Done." << std::endl;
18: }
```

###### Ausgabe

```
c'tor Dummy [1]
d'tor Dummy [1]
Exception 99 occurred!
Done.
```

---

##### 5. Reihenfolge bei der Freigabe mehrere RAII-verwalteter Ressourcen

```cpp
01: void test()
02: {
03:     // test RAII idiom with two encapsulated resources:
04:     // Note order of destructor calls
05: 
06:     {
07:         Dummy* ptr1 = new Dummy{ 1 };
08:         Dummy* ptr2 = new Dummy{ 2 };
09: 
10:         RAII raii1{ [&]() { delete ptr1; } };
11:         RAII raii2{ [&]() { delete ptr2; } };
12:     }
13: 
14:     std::cout << "Done." << std::endl;
15: }
```

###### Ausgabe

```
c'tor Dummy [1]
c'tor Dummy [2]
d'tor Dummy [2]
d'tor Dummy [1]
Done.
```

---

##### 6. RAII-verwalteter Ressource als Instanzvariable eines Objekts

```cpp
01: template <class TFinalizer>
02: class RAIIContainer
03: {
04: public:
05:     RAIIContainer(TFinalizer&& finalizer) : m_raii{ finalizer } {}
06: 
07: private:
08:     RAII<TFinalizer> m_raii;
09: };
10: 
11: void test()
12: {
13:     Dummy* ptr = new Dummy{ 1 };
14:     if (ptr == nullptr) {
15:         return;
16:     }
17: 
18:     {
19:         RAIIContainer cont{ [&]() { delete ptr; } };
20:     }
21: 
22:     std::cout << "Done." << std::endl;
23: }

```

---

###### Ausgabe

```
c'tor Dummy [1]
d'tor Dummy [1]
Done.
```

#### Struktur

Die folgenden beiden Abbildungen beschreiben konzeptionell die Allokation
einer Ressource mit und ohne RAII-Idiom:

<img src="dp_raii_idiom_01.svg" width="700">

*Abbildung* 1: Klassische Anforderung für einen Speicherbereich.

Beachten Sie in *Abbildung* 1: Es ist offen bzw. Pflicht für den Verwender des Speicherbereichs,
diesen nach Gebrauch mit dem `delete`-Operator wieder freizugeben.

<img src="dp_raii_idiom_02.svg" width="700">

*Abbildung* 2: Anforderung eines Speicherbereichs mit dem RAII-Idiom.

In *Abbildung* 2 können Sie erkennen, dass der Destruktor des RAII-Objekts den allokierten Speicherbereich wieder freigibt.

---

#### &bdquo;Real-World&rdquo; Beispiel zu Windows Clipboard

In der Datei *Clipboard.cpp* finden Sie mehrere Klassen und Methoden vor,
die den schreibenden und lesenden Zugriff auf das Windows Clipboard in RAII-konformer Manier demonstrieren.

Windows-Resourcen werden in diesem Beispiel durch folgende Win32-API-Methoden in Anspruch genommen:

* `GlobalAlloc`
* `GlobalFree`
* `GlobalLock`
* `GlobalUnlock`

und

* `OpenClipboard`
* `EmptyClipboard`
* `SetClipboardData`
* `CloseClipboard`
* `GetClipboardData`


#### &bdquo;Real-World&rdquo; Beispiel zu `std::ofstream`

In der Datei *RAII_Ofstream.cpp* finden Sie eine Funktion `writeToFile` vor,
die das RAII-Idiom verwendet.

Es ist zu beachten, dass der Standard-C++-Klasse `std::ofstream` dieser Mechanismus ebenfalls zu Grunde liegt.
Diese Eigenschaft ist in der offiziellen Dokumentation leider nur sehr versteckt erwähnt:

In [std::basic_ofstream<CharT,Traits>::close](https://en.cppreference.com/w/cpp/io/basic_ofstream/close)
heißt es in den Erläuterungen zur Methode `close`:

*"This function is called by the destructor of basic_ofstream when the stream object goes out of scope
and is not usually invoked directly."*

und

*"Note that any open file is automatically closed when the ofstream object is destroyed."*

#### Weiterarbeit

Erstellen Sie eine RAII-konforme Klasse `RAIIFile`. Für den Anwender offenbart sich
diese Klasse mit einer einzigen Methode `write`, um eine Zeichenkette in einer Datei zu schreiben.

Zum Zwecke des Übens verwenden Sie intern in der Klasse `RAIIFile` die Funktionen
`fopen`, `fclose` und `fprintf` aus der *CRT* (*C-Runtime-Library*).
Sinn und Zweck der Übung ist, dass die Funktion `fclose` **immer** zur Ausführung gelangt, also auch für den Fall,
dass Fehlersituationen oder unerwartete Situationen eintreten.

###### Beispiel

```cpp
RAIIFile file("example.txt");
file.write("123\n");
```

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel sind teilweise entnommen aus

[Design Patterns with C++](https://www.amazon.de/-/en/Fedor-G-Pikus/dp/1788832566).

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
