# Single-Responsibility-Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

&ldquo;Eine Klasse sollte nur einen Grund haben, geändert zu werden&rdquo;

In anderen Worten:
Das *Single-Responsibility-Prinzip* besagt, dass Klassen bis zu dem Punkt &ldquo;kohärent&rdquo; (semantisch zusammenhängend) sein sollten,
dass sie eine einzige Verantwortung haben, wobei Verantwortung als &ldquo;ein Grund für die Änderung&rdquo; definiert wird.

#### Example violating the Single Responsibility Principle

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

// ===============================================

http://www.vishalchovatiya.com/single-responsibility-principle-in-cpp-solid-as-a-rock/


ALT

#### Problem:

Das *Bridge Pattern* genießt einen guten Ruf,
da sich mit ihm die abstrakten Elemente der Klasse von den Implementierungsdetails trennen lassen.
Dieses Muster ist vor allem dann zu empfehlen,
wenn die betrachteten Klassen häufig variieren,
da sich dann Änderungen an der Codebasis bei minimalem Wissen über das Programm leicht durchführen lassen.

Betrachten wir ein Beispiel, in dem eine Implementierung auf zwei oder mehreren Realisierungen fußt.
Zum Beispiel ein Programm, das die Persistenz von Objekten auf verschiedenen Plattformen (Betriebssystemen) realisiert.
Einige Objekte sollen in einer Datenbank und andere Objekte wiederum im Dateisystem des unterlagerten
Betriebssystems gespeichert werden. 
Wird das Programm um diese Funktionalität &ldquo;straight forward&rdquo; erweitert,
sind Probleme vorprogrammiert, da die Abstraktion mit der Implementierung verknüpft wird.
In diesem Fall ist es besser, das *Bridge Pattern*  zu verwenden und die Abstraktion von der Implementierung zu trennen.
Wird dieses Muster nicht verwendet, kann man die Beobachtung machen,
dass Implementierungsdetails in einer Abstraktion enthalten sind.

Ein weiterer Vorteil des *Bridge Patterns* ist die Möglichkeit, Implementierungsdetails zur Laufzeit zu ändern.
Dies ermöglicht es dem Benutzer, Implementierungen zu wechseln, um auf diese Weise zu bestimmen,
wie die Software mit anderen Systemen zusammenarbeitet.

#### Lösung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Bridge Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Abstraction**: Definiert eine Abstraktionsschnittstelle. Sie fungiert als Basisklasse für andere verfeinerte Abstraktionsklassen.
    Sie bezieht sich auch auf eine bestimmte Implementierung, die für plattformspezifische Funktionen verwendet wird.
  * **RefinedAbstraction**: Stellt eine verfeinerte Variation einer Abstraktionsschnittstelle dar,
    enthält jedoch keine Implementierungsdetails. *De facto* erweitert sie nur die Abstraktion.
  * **Implementor**: Definiert die Schnittstelle für Implementierungsklassen.
  * **ConcreteImplementor**: Diese Klasse erbt von der Klasse `Implementor`. Es kann mehr als eine Instanz von `Implementor`-Klassen geben,
    die dieselbe Schnittstelle unterstützen, aber plattformspezifische Funktionen bereitstellen.

<img src="dp_bridge_pattern_01.svg" width="600">

*Abbildung* 1: Schematische Darstellung des *Bridge Patterns*.


#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Ein etwas ausführlicheres Beispiel

---

#### 'Real-World' Beispiel:

Bei diesem Muster steht eine Schnittstelle im Mittelpunkt,
die als Brücke fungiert, die die Funktionalität konkreter Klassen unabhängig
von den Schnittstellenimplementierungsklassen macht.
Beide Klassentypen können strukturell verändert werden, ohne sich gegenseitig zu beeinflussen.

Wir demonstrieren die Verwendung des Bridge-Entwurfsmusters anhand des folgenden Beispiels,
in dem ein Kreis in verschiedenen Farben mit derselben abstrakten Basisklassenmethode,
aber unterschiedlichen Bridge-Implementiererungsklassen gezeichnet werden kann.

In *Abbildung* 2 finden Sie eine `IDrawAPI`-Schnittstelle vor, die als Bridge-Schnittstellenklasse fungiert,
und zwei konkrete Klassen `RedCircleDrawer` und `GreenCircleDrawer`,
die die `IDrawAPI`-Schnittstelle implementieren.

`Shape` ist eine abstrakte Klasse und besitzt einen `IDrawAPI`-Schnittstellenzeiger
(*Raw*-Pointer oder Smart-Pointer). In der Anwendung finden Sie ein Beispiel, in dem ein Kreis mit zwei verschiedenen Farben 
gezeichnet wird:

<img src="dp_bridge_pattern_02.svg" width="600">

*Abbildung* 2: Ein Anwendungsbeispiel des *Bridge Patterns*.

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/bridge/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Bridge)

vor.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
