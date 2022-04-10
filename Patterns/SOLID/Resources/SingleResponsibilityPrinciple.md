# Single-Responsibility-Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

&ldquo;Eine Klasse sollte nur einen Grund haben, geändert zu werden&rdquo;

In anderen Worten:
Das *Single-Responsibility-Prinzip* besagt, dass Klassen bis zu dem Punkt &ldquo;kohärent&rdquo; (semantisch zusammenhängend) sein sollten,
dass sie eine einzige Verantwortung haben, wobei Verantwortung als &ldquo;ein Grund für die Änderung&rdquo; definiert wird.

#### Example: Violating the Single Responsibility Principle

```cpp
01: class Journal
02: {
03:     std::string               m_title;
04:     std::vector<std::string>  m_entries;
05: 
06: public:
07:     explicit Journal(const std::string& title) : m_title{ title } {}
08: 
09:     void addEntries(const std::string& entry) {
10:         static uint32_t count = 0;
11:         count++;
12:         std::string text = std::to_string(count) + ": " + entry;
13:         m_entries.push_back(text);
14:     }
15: 
16:     auto getEntries() const { return m_entries; }
17: 
18:     void save(const std::string& filename, std::ostream& os) {
19: 
20:         for (auto& s : m_entries) {
21:             os << s << std::endl;
22:         }
23:     }
24: };
```

  * Das obige C++-Beispiel könnte in Ordnung zu sein, solange es nur eine einzelne Domänenklasse gibt, z. B. `Journal`.
    Dies ist jedoch in einer realen Anwendung normalerweise nicht der Fall.
  * Wenn wir beginnen, weitere Domänenklassen wie `Book`, `File` usw. hinzuzufügen,
    ist die Speichermethode `save` für alle Domänenklassen separat zu implementieren.
  * Das eigentliche Problem entsteht, wenn die Speicherfunktionalität geändert werden soll.
    Zum Beispiel wäre es denbkbar, dass eines Tages die Daten an Stelle in Dateien in einer Datenbank abgelegt werden sollen.
    In diesem Fall müsste man jede Domänenklassenimplementierung durchlaufen und den gesamten Code ändern,
    was natürlich völlig sinnlos ist.
  * Der Verstoß gegen das Single-Responsibility-Prinzip in diesem Beispiel ist offensichtlich:
    Die Klasse `Journal` besitzt zwei Gründe, um geändert zu werden:
    * Änderungen im Zusammenhang mit der `Journal` Klasse
    * Änderungen im Zusammenhang mit der Persistenz (Datenablage) der `Journal` Klasse


#### Example: Respecting the Single Responsibility Principle

Als Lösung stellen wir das vor, was man auch unter
der Begrifflichkeit &ldquo;Separation of Concerns&rdquo; versteht:

```cpp
01: class Journal 
02: {
03:     std::string               m_title;
04:     std::vector<std::string>  m_entries;
05: 
06: public:
07:     explicit Journal(const std::string& title) : m_title{ title } {}
08: 
09:     void addEntries(const std::string& entry) {
10:         static uint32_t count = 0;
11:         count++;
12:         std::string text = std::to_string(count) + ": " + entry;
13:         m_entries.push_back(text);
14:     }
15: 
16:     auto get_entries() const { return m_entries; }
17: };
18: 
19: struct SavingManager
20: {
21:     static void save(const Journal& journal, const std::string& filename, std::ostream& os) {
22: 
23:         for (auto& entry : journal.get_entries()) {
24:             os << entry << std::endl;
25:         }
26:     }
27: };
```

  * Klasse `Journal` kümmert sich nur um Daten und Funktionalitäten, die mit dem Journal zusammenhängen.
  * Das Aspekt des Sichern von Journaldaten ist an einer anderen zentralen Stelle zusammengefasst: 
    Klasse `SavingManager`.
  * Wenn Klasse `SavingManager` wächst oder Änderungen bedarf, ist ihr gesamter Code an einer Stelle.

#### Vorteile des Single-Responsibility-Prinzips

  * Expressiveness &ndash; Ausdruckskraft
  * Maintainability &ndash; Wartbarkeit
  * Reusability &ndash; Wiederverwendbarkeit

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
