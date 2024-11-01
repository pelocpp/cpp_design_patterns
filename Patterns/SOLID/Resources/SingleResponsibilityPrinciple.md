# Single-Responsibility-Prinzip

[Zur�ck](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

#### Kategorie: Programmier-Idiom

#### Ziel / Absicht:

&bdquo;Eine Klasse sollte nur einen Grund haben, ge�ndert zu werden&rdquo;.

In anderen Worten:

  * Das Prinzip der &bdquo;Single Responsibility&rdquo; legt Wert auf Einfachheit, also &bdquo;ein Objekt, eine Aufgabe&rdquo;.

  * Es geht darum, die Funktionalit�t von Objekten und deren Beziehungskomplexit�t zu reduzieren.

  * Man hat Sorge daf�r zu tragen, dass jedes Objekt eine Verantwortung hat, auch wenn es nicht immer einfach ist,
ein komplexes Objekt in kleinere und einfachere Komponenten zu zerlegen.

  * Es geht folglich nicht darum, nur eine Methode in einer Klasse zu haben &ndash; es geht darum, eine Klasse f�r eine Sache verantwortlich zu machen.



#### Beispiel: Violating the Single Responsibility Principle

```cpp
01: class Journal
02: {
03: private:
04:     std::string              m_title;
05:     std::vector<std::string> m_entries;
06: 
07: public:
08:     Journal(const std::string& title) 
09:         : m_title{ title } 
10:     {}
11: 
12:     void addEntry(const std::string& entry) {
13:         static size_t count {};
14:         count++;
15:         std::string text { std::to_string(count) + ": " + entry };
16:         m_entries.push_back(text);
17:     }
18: 
19:     auto getEntries() const { return m_entries; }
20: 
21:     void save(const std::string& filename, std::ostream& os) {
22: 
23:         for (const auto& entry : m_entries) {
24:             os << entry << std::endl;
25:         }
26:     }
27: };
```

  * Das obige C++-Beispiel k�nnte in Ordnung zu sein, solange es nur eine einzige Dom�nenklasse gibt, hier die Klasse `Journal`.
    Dies ist jedoch in einer realen Anwendung normalerweise eher selten der Fall.
  * Wenn wir beginnen, weitere Dom�nenklassen wie `Book`, `File` usw. hinzuzuf�gen,
    ist die Speichermethode `save` f�r alle Dom�nenklassen separat zu implementieren.
  * Das eigentliche Problem entsteht, wenn die Funktionalit�t f�r die Datenablage ge�ndert werden soll.
    Zum Beispiel w�re es denkbar, dass die Daten an Stelle in Dateien in einer Datenbank abgelegt werden sollen.
    In diesem Fall m�sste man jede Dom�nenklassenimplementierung durchlaufen und den gesamten Code �ndern.
    Eine derartige Vorgehensweise ist nicht empehlenswert!
  * Der Versto� gegen das *Single-Responsibility-Prinzip* in diesem Beispiel ist offensichtlich:
    Die Klasse `Journal` besitzt zwei Gr�nde, um ge�ndert zu werden:
    * �nderungen im Zusammenhang mit der `Journal`-Klasse selbst.
    * �nderungen im Zusammenhang mit der Persistenz (Datenablage) der `Journal`-Klasse.


#### Beispiel: Respecting the Single Responsibility Principle

Wir betrachten eine �berarbeitung des letzten Beispiels.
Man k�nnte sie auch unter der Begrifflichkeit &bdquo;Separation of Concerns&rdquo; einordnen:

```cpp
01: class Journal 
02: {
03: private:
04:     std::string              m_title;
05:     std::vector<std::string> m_entries;
06: 
07: public:
08:     Journal(const std::string& title)
09:         : m_title{ title }
10:     {}
11: 
12:     void addEntry(const std::string& entry) {
13:         static size_t count {};
14:         count++;
15:         std::string text { std::to_string(count) + ": " + entry };
16:         m_entries.push_back(text);
17:     }
18: 
19:     auto get_entries() const { return m_entries; }
20: };
21: 
22: struct SavingManager
23: {
24:     static void save(const Journal& journal, const std::string& filename, std::ostream& os) {
25: 
26:         for (const auto& entry : journal.get_entries()) {
27:             os << entry << std::endl;
28:         }
29:     }
30: };
```

  * Die Klasse `Journal` k�mmert sich jetzt nur um ihre Daten und Funktionen, die mit dem Journal zusammenh�ngen.
  * Der Aspekt des Sicherns von Journaldaten ist an einer anderen, zentralen Stelle zusammengefasst: 
    Klasse `SavingManager`.
  * Wenn �nderungen an der Klasse `SavingManager` notwendig sind, ist ihr gesamter Code an einer Stelle vorhanden.

#### Vorteile des Single-Responsibility-Prinzips:

  * Expressiveness &ndash; Ausdruckskraft
  * Maintainability &ndash; Wartbarkeit
  * Reusability &ndash; Wiederverwendbarkeit

---

## Literaturhinweise

Die Anregungen zu diesem Beispiel finden Sie in

[Single Responsibility Principle in C++](https://vishalchovatiya.com/posts//single-responsibility-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zur�ck](../../../Resources/Readme_03_Design_Principles.md)

---
