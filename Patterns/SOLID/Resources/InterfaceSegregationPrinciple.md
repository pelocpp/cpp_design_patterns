# Interface Segregation Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

&ldquo;Clients sollen nicht gezwungen werden, sich auf Schnittstellen zu verlassen, die sie nicht verwenden&rdquo;.

In anderen Worten:
  * Das *Interface-Segregationsprinzip* ist eng mit dem *Single-Responsibility-Prinzip* verwandt.
  Es bedeutet, dass man Abstraktionen immer so gestalten sollte,
  dass Clients, die exponierte Methoden verwenden, stattdessen nicht die gesamte Abstraktion betrachten müssen.
  * Das würde einem Client die Last auferlegen, Methoden implementieren zu müssen,
  die er gar nicht benötigt.

#### Beispiel: Violating the Interface Segregation Principle

```cpp
01: class Document;
02: 
03: class IMachine {
04: public:
05:     virtual void print(Document& doc) = 0;
06:     virtual void fax(Document& doc) = 0;
07:     virtual void scan(Document& doc) = 0;
08: };
09: 
10: // ok
11: class MultiFunctionPrinter : public IMachine {
12: public:
13:     void print(Document& doc) override {
14:         // do printing ...
15:     }
16:     void fax(Document& doc) override {
17:         // do faxing ...
18:     }
19:     void scan(Document& doc) override {
20:         // do scanning ...
21:     }
22: };
23: 
24: // Not ok
25: class Scanner : public IMachine {
26: public:
27:     void print(Document& doc) override {
28:         throw std::runtime_error("printing not supported");
29:     }
30:     void fax(Document& doc) override {
31:         throw std::runtime_error("faxing not supported");
32:     }
33:     void scan(Document& doc) override {
34:         // do scanning ...
35:     }
36: };
```

Wie man erkennen kann, ist es für die Klasse `MultiFunctionPrinter` in Ordnung,
die Methoden `print`, `fax` und `scan` zu implementieren,
die von der `IMachine`-Schnittstelle erzwungen werden.

Aber was ist, wenn wir nur einen Scanner oder Drucker benötigen?
In diesem Fall von der Schnittstelle `IMachine` zu erben
und unnötige Methoden leer zu lassen oder eine `NotImplemented`-Ausnahme auszulösen,
ist kein guter Ansatz.

#### Beispiel: Respecting the Interface Segregation Principle

```cpp
01: class Document;
02: 
03: /* ---------------------- Interfaces ------------------- */
04: class IPrinter {
05: public:
06:     virtual void print(Document& doc) = 0;
07: };
08: 
09: class IScanner {
10: public:
11:     virtual void scan(Document& doc) = 0;
12: };
13: 
14: class IMachine : public IPrinter, public IScanner {};
15: 
16: /*  ---------------------- Implementation ------------------- */
17: class Printer : public IPrinter {
18: public:
19:     void print(Document& doc) override { };
20: };
21: 
22: class Scanner : public IScanner {
23: public:
24:     void scan(Document& doc) override { };
25: };
26: 
27: class Machine : public IMachine {
28: public:
29:     IPrinter& m_printer;
30:     IScanner& m_scanner;
31: 
32:     Machine(IPrinter& printer, IScanner& scanner)
33:         : m_printer{ printer }, m_scanner{ scanner } {}
34: 
35:     void print(Document& doc) override {
36:         m_printer.print(doc);
37:     }
38:     void scan(Document& doc) override {
39:         m_scanner.scan(doc);
40:     }
41: };
```

Jetzt haben wir eine Flexibilität erzielt,
Abstraktionen nach Belieben zu kombinieren und Implementierungen ohne unnötigen Ballast bereitzustellen.

  * Wie bereits im *Single-Responsibility-Prinzip* erläutert:
    Vermeiden Sie Klassen und Schnittstellen mit mehreren Verantwortlichkeiten.
    Sie ändern sich häufig und erschweren die Wartung der Software.

  * Versuchen Sie, Schnittstellen basierend auf einer bestimmten Rolle
    in mehrere Schnittstellen aufzuteilen.

#### Beispiel

Vergleichen Sie

<pre>
class MyMachine : public IMachine
</pre>

mit

<pre>
class MyMachine : public IPrinter, public IScanner, public IFaxer
</pre>

Die zweite Variante sagt viel aus, die erste Variante stößt bestenfalls zum Raten an.

Das Beantworten einer einzigen Frage zur Entwurfszeit kann helfen,
ein Design zu korrigieren:

*Benötige ich alle Methoden einer Schnittstelle, die ich verwende?*

---

Die Anregungen zu diesem Beispiel finden Sie in

[Interface Segregation Principle in C++](http://www.vishalchovatiya.com/interface-segregation-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
