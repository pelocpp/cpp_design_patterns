# Visitor Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_visitorpattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Hinzufügen einer neuen Operation für eine Gruppe ähnlicher Objekte oder Hierarchien.&rdquo;

Das *Visitor Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
das eine Menge strukturierter Daten von den Funktionen trennt,
die auf ihr ausgeführt werden. Dies unterstützt zum einen das Prinzip der "losen Kopplung"
und es ermöglicht zum anderen das Hinzufügen zusätzlicher Operationen, ohne an den Datenklassen Änderungen vornehmen zu müssen.

Im Kern geht es darum, eine Hierarchie von Klassen und Operationen auf diesen Klassen voneinander zu trennen.

#### Prinzip:

Das Muster definiert eine Art Infrastruktur für den Zugriff auf komplexe dynamische Daten- und Objektstrukturen.
Dabei wird der dynamischen Struktur eine Methodenschnittstelle gegeben, die ein sogenanntes &ldquo;Besucher&rdquo;-Objekt entgegennimmt
und über alle Daten der Struktur schleust. Das &ldquo;Besucher&rdquo;-Objekt läuft also an allen Elementen der Struktur entlang
und wird von den Elementen über eine Methode &ldquo;akzeptiert&rdquo;.
Die Konvention besteht darin, diese Methode `accept` zu nennen.
Dabei ruft das Strukturelement eine Methode im &ldquo;Besucher&rdquo;-Objekt auf,
die speziell für den Typ des Strukturelements geschrieben wurde und eine Referenz oder einen Zeiger
auf das Strukturelement in ihrer Parameterliste hat.
Damit hat der Visitor wiederum die Chance, eine Operation auf dem Strukturelement auszuführen
und dabei auf dessen Typ zu reagieren.

Der Sinn des Visitors besteht darin, die eigentliche Operation auf den Daten von der Traver­sierung
der Verwaltungs­struktur zu trennen. Aus der Entkopplung dieser beiden Aspekte entstehen
Freiheitsgrade für Variationen dieses Entwurfsmusters.

#### Eine didaktische Herleitung in 4 Schritten:

##### Schritt 1: Ein &ldquo;aufdringlicher&rdquo; Besucher (*intrusive Visitor*)

Nehmen wir an, wir haben eine Hierarchie von Dokumentenobjekten der folgenden Gestalt:

```cpp
01: class Document
02: {
03: public:
04:     virtual void addToList(const std::string& line) = 0;
05: };
06: 
07: class Markdown : public Document
08: {
09: public:
10:     Markdown() : m_start{ "* " } {}
11: 
12:     void add_to_list(const std::string& line) {
13:         m_content.push_back(line);
14:     }
15: 
16:     std::string            m_start;
17:     std::list<std::string> m_content;
18: };
19: 
20: class HTML : public Document
21: {
22: public:
23:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
24: 
25:     virtual void addToList(const std::string& line) override {
26:         m_content.push_back(line);
27:     }
28: 
29: private:
30:     std::string             m_start;
31:     std::string             m_end;
32:     std::list<std::string>  m_content;
33: };
```

Und nehmen wir nun ferner an,
dass wir einige neue Operationen auf dieser bestehenden Infrastruktur definieren müssen.
Zum Beispiel haben wir eine `Document`-Klasse wie oben gezeigt
und möchten jetzt, dass verschiedene Dokumente (z.B. `HTML` und `Markdown`) druckbar sind,
also eine Methode `print` bekommen.

Es gibt also eine neue Anforderung (*Concern*) 
und wir müssen diese auf irgendeine Weise durch die gesamte Klassenhierarchie propagieren,
indem wir im Wesentlichen jede einzelne Dokument-Klasse irgendwie unabhängig um eine `print`-Methode
ergänzen.

Was wir jetzt nicht tun wollen, ist, dass wir jedes Mal, wenn wir eine neue Anforderung (*Concern*) erhalten,
in den vorhandenen Code zurückkehren und jede Klasse in der Hierarchie (mit zusätzlichen virtuellen Funktionen) ändern.

Dies würde einen Verstoß des *Open*-*Closed*-Prinzips darstellen!
Zum Zweiten gibt es auch noch das *Single*-*Responsibility*-Prinzip, an das wir uns halten wollen.
Kurz gesagt besagt dieses, dass wir für eine neue Anforderung eine separate Klasse zu erstellen haben.

Würden wir das jetzt alles für einen kurzen Moment außer Acht lassen,
könnten wir folgende Realisierung betrachten:

```cpp
01: class Document
02: {
03: public:
04:     virtual void addToList(const std::string& line) = 0;
05:     virtual void print() = 0;
06: };
07: 
08: class Markdown : public Document
09: {
10: public:
11:     Markdown() : m_start{ "* " } {}
12: 
13:     virtual void addToList(const std::string& line) override {
14:         m_content.push_back(line);
15:     }
16: 
17:     virtual void print() override {
18:         for (const std::string& item : m_content) {
19:             std::cout << m_start << item << std::endl;
20:         }
21:     }
22: 
23: private:
24:     std::string            m_start;
25:     std::list<std::string> m_content;
26: };
27: 
28: class HTML : public Document
29: {
30: public:
31:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
32: 
33:     virtual void addToList(const std::string& line) override {
34:         m_content.push_back(line);
35:     }
36: 
37:     virtual void print() override {
38:         std::cout << "<ul>" << std::endl;
39:         for (const std::string& item : m_content) {
40:             std::cout << "    " << m_start << item << m_end << std::endl;
41:         }
42:         std::cout << "</ul>" << std::endl;
43:     }
44: 
45: private:
46:     std::string             m_start;
47:     std::string             m_end;
48:     std::list<std::string>  m_content;
49: };
50: 
51: void clientCode02()
52: {
53:     Document* d1 = new HTML;
54:     d1->addToList("This is line");
55:     d1->print();
56: 
57:     Document* d2 = new Markdown;
58:     d2->addToList("This is another line");
59:     d2->print();
60: 
61:     delete d1;
62:     delete d2;
63: }
```

Wie wir sehen, ist diese Vorgehensweise für zwei bis drei Klassen mit Schmerzen machbar,
auch wenn wir dabei gegen einige SOLID-Prinzipien verstoßen.
Aber stellen Sie sich vor, Sie haben es mit 20 oder mehr Klassen als Teil einer ganzen Hierarchie zu tun,
dann versagt diese Strategie.

Darüber hinaus wird dieser Ansatz umständlich, wenn es um mehr als ein *Concern* wie z.B.
Speichern (`save`), Verarbeiten (`process`) usw. geht.
Jedes *Concern* sollte in einer separaten Klasse abgehandelt werden,
um vor allem das *Single*-*Responsibility*-Prinzips zu beachten.


##### Schritt 2: Ein &ldquo;reflektierender&rdquo; Besucher (*reflective Visitor*)

```cpp
01: class Document
02: {
03: public:
04:     virtual void addToList(const std::string& line) = 0;
05: };
06: 
07: class Markdown : public Document
08: {
09: friend class DocumentPrinter;
10: 
11: public:
12:     Markdown() : m_start{ "* " } {}
13: 
14:     virtual void addToList(const std::string& line) override {
15:         m_content.push_back(line);
16:     }
17: 
18: private:
19:     std::string            m_start;
20:     std::list<std::string> m_content;
21: };
22: 
23: class HTML : public Document
24: {
25: friend class DocumentPrinter;
26: 
27: public:
28:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
29: 
30:     virtual void addToList(const std::string& line) override {
31:         m_content.push_back(line);
32:     }
33: 
34: private:
35:     std::string             m_start;
36:     std::string             m_end;
37:     std::list<std::string>  m_content;
38: };
39: 
40: class DocumentPrinter
41: {
42: public:
43:     static void print(Document* e) {
44:         if (auto md = dynamic_cast<Markdown*>(e)) {
45:             for (const std::string& item : md->m_content)
46:                 std::cout << md->m_start << item << std::endl;
47:         }
48:         else if (auto hd = dynamic_cast<HTML*>(e)) {
49:             std::cout << "<ul>" << std::endl;
50:             for (const std::string& item : hd->m_content) {
51:                 std::cout << "    " << hd->m_start << item << hd->m_end << std::endl;
52:             }
53:             std::cout << "</ul>" << std::endl;
54:         }
55:     }
56: };
57: 
58: void clientCode03() {
59:     Document* d1 = new HTML;
60:     d1->addToList("This is line");
61:     DocumentPrinter::print(d1);
62: 
63:     Document* d2 = new Markdown;
64:     d2->addToList("This is another line");
65:     DocumentPrinter::print(d2);
66: 
67:     delete d1;
68:     delete d2;
69: }
```

Wie bereits erwähnt, haben wir nun eine separate Klasse `DocumentPrinter` mit Druckfunktionalität
für die gesamte Klassenhierarchie erstell.
Das *Single*-*Responsibility*-Prinzip wird so berücksichtigt.

Aber bei diesem Ansatz müssen wir Typen bestimmter Klassen identifizieren
(unter Verwendung von `dynamic_cast<>()`),
da wir unabhängig voneinander mit einzelnen Objekten in der Hierarchie arbeiten müssen.

Dies ist kein Ansatz, der sich effizient skalieren lässt.
Wenn Sie vor allem den Satz von Klassen erweitern wollen,
um deren Verarbeitung es geht, werden Sie am Ende eine lange Liste von `if`/`else`-`if`-Konstrukten
und unnötige Performanceaufwendungen für *RTTI* haben.


##### Schritt 3: Ein &ldquo;klassischer&rdquo; Besucher (*classic Visitor*)

Damit kommen wir nun auf die klassische Umsetzung des *Visitor* Patterns zu sprechen.
Diese wird weiter unten noch näher erläutert (begleitender Text und UML-Diagramm):

```cpp
01: /* --------- Generic Visitor Class ----------- */
02: class Markdown;
03: class HTML;
04: 
05: class DocumentVisitor
06: {
07: public:
08:     virtual void visit(Markdown*) = 0;
09:     virtual void visit(HTML*) = 0;
10: };
11: 
12: /* -------- Document Classes Hierarchy ---------- */
13: class Document
14: {
15: public:
16:     virtual void addToList(const std::string& line) = 0;
17:     virtual void accept(DocumentVisitor*) = 0;    // <<<<<
18: };
19: 
20: class Markdown : public Document
21: {
22: public:
23:     Markdown() : m_start{ "* " } {}
24: 
25:     virtual void addToList(const std::string& line) override { 
26:         m_content.push_back(line);
27:     }
28: 
29:     virtual void accept(DocumentVisitor* dv) override {  // <<<<<
30:         dv->visit(this);
31:     } 
32: 
33:     std::string             m_start;
34:     std::list<std::string>  m_content;
35: };
36: 
37: class HTML : public Document
38: {
39: public:
40:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
41: 
42:     virtual void addToList(const std::string& line) override {
43:         m_content.push_back(line);
44:     }
45: 
46:     virtual void accept(DocumentVisitor* dv) override {    // <<<<<
47:         dv->visit(this);
48:     } 
49: 
50:     std::string            m_start;
51:     std::string            m_end;
52:     std::list<std::string> m_content;
53: };
54: 
55: /* ------ Specific Printer Visitor Class -------- */
56: 
57: class DocumentPrinter : public DocumentVisitor
58: {
59: public:
60:     virtual void visit(Markdown* md) override;
61:     virtual void visit(HTML* hd) override;
62: };
63: 
64: void DocumentPrinter::visit(Markdown* md) {
65:     for (const std::string& item : md->m_content)
66:         std::cout << md->m_start << item << std::endl;
67: }
68: 
69: void DocumentPrinter::visit(HTML* hd) {
70:     std::cout << "<ul>" << std::endl;
71:     for (const std::string& item : hd->m_content)
72:         std::cout << "    " << hd->m_start << item << hd->m_end << std::endl;
73:     std::cout << "</ul>" << std::endl;
74: }
75: 
76: void clientCode04() {
77:     DocumentPrinter* dp = new DocumentPrinter();
78: 
79:     Document* d1 = new HTML;
80:     d1->addToList("This is line");
81:     d1->accept(dp);
82: 
83:     Document* d2 = new HTML;
84:     d2->addToList("This is another line");
85:     d2->accept(dp);
86: 
87:     delete d1;
88:     delete d2;
89:     delete dp;
90: }
```

Wie Sie sehen können, haben wir es nun mit zwei Ebenen der Indirektion zu tun.
Damit wurden vor allem vermieden, die zwei Prinzipien
*Open*-*Closed*-Prinzip und *Single*-*Responsibility*-Prinzip zu verletzen.

Hierfür gibt es ein spezielles Schlagwort: *Double Dispatch*, siehe dazu *Abbildung* 1:

<img src="dp_visitor_double_dispatch.svg" width="700">

*Abbildung* 1: Schematische Darstellung von *Double Dispatch*.

Über das Objekt `doc` rufen wir die Methode `accept()` auf,
die auf Grund des virtuellen Methodenaufrufmechanismus den Aufruf an die Methode `HTML::accept`
delegiert.

Im Kontext dieser Methode wiederum finden wir einen Aufruf

```cpp
dv->visit(this);
```

vor. Dieses Mal wird &ndash; wiederum auf Grund des virtuellen Methodenaufrufmechanismus &ndash; 
der Aufruf an die Methode `DocumentPrinter::visit(HTML*)` delegiert (unter Berücksichtigung
des Zeigertyps `HTML*`).

##### Schritt 4: Alternativer Ansatz für *Double Dispatch* in Modern C++ mit `std::variant` und `std::visit`

```cpp
01: class Document
02: {
03: public:
04:     virtual void addToList(const std::string& line) = 0;
05: };
06: 
07: class Markdown : public Document
08: {
09: public:
10:     Markdown() : m_start{ "* " } {}
11: 
12:     virtual void addToList(const std::string& line) override {
13:         m_content.push_back(line); 
14:     }
15: 
16:     std::string             m_start;
17:     std::list<std::string>  m_content;
18: };
19: 
20: class HTML : public Document
21: {
22: public:
23:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
24: 
25:     virtual void addToList(const std::string& line) override {
26:         m_content.push_back(line); 
27:     }
28: 
29:     std::string             m_start;
30:     std::string             m_end;
31:     std::list<std::string>  m_content;
32: };
33: 
34: /* ------ Specific Printer Visitor Class -------- */
35: class DocumentPrinter
36: {
37: public:
38:     void operator()(const Markdown& md) {
39:         for (const std::string& item : md.m_content) {
40:             std::cout << md.m_start << item << std::endl;
41:         }
42:     }
43: 
44:     void operator()(const HTML& hd) {
45:         std::cout << "<ul>" << std::endl;
46:         for (const std::string& item : hd.m_content) {
47:             std::cout << "    " << hd.m_start << item << hd.m_end << std::endl;
48:         }
49:         std::cout << "</ul>" << std::endl;
50:     }
51: };
52: 
53: /* ------ std::variant & std::visit -------- */
54: void clientCode05() {
55:     HTML hd;
56:     hd.addToList("This is line");
57:     std::variant<Markdown, HTML> doc = hd;
58:     DocumentPrinter dp;
59:     std::visit(dp, doc);
60: 
61:     Markdown md;
62:     md.addToList("This is another line");
63:     doc = md;
64:     std::visit(dp, doc);
65: }
```

Wir setzen nun die *Modern C++* Klasse `std::variant` und die Funktion `std::visit` ein.

Die Zeile

```cpp
std::variant<Markdown, HTML> document;
```

besagt, dass wir der Variablen `document` entweder ein `Markdown`- oder ein `HTML`-Objekt
zuweisen können. 

Die `std::visit`-Methode wiederum akzeptiert ein *Callable*-Objekt,
d.h. in unserem Beispiel ein `DocumentPrinter`-Objekt,
das für alle möglichen Typen einen überladenen Funktionsoperator `operator()` &ndash;
auch als *Funktor* bezeichnet &ndash; bereitstellt.

#### Lösung:

Die Traver­sierung wird durch die erwähnte Infra­struktur aus Methoden übernommen.
Die durch den Visitor transpor­tierte Operation wird in einer Kindklasse der Visitor­schnitt­stelle implementiert.
Damit lassen sich beliebige Operationen definieren
und durch den allgemeinen Traversierungs­mechanismus in die Objekt­struktur tragen.
Mit dem Namen des Visitors wird das Verhalten des Musters gewürdigt.
Das Visitor­objekt geht die Objekte in der Objekt­struktur &ldquo;besuchen&rdquo;.

Das Ergebnis der Trennung von Objektstruktur und Funktionen (Algorithmen) ist ein Datenmodell
mit eingeschränkter Funktionalität und einer Gruppe von &ldquo;*Besuchern*&rdquo;,
die Operationen auf den Daten ausführen.
Ein weiterer Vorteil ist die Möglichkeit, einen neuen *Besucher* hinzufügen zu können,
ohne dabei die vorhandene Struktur ändern zu müssen. 
Die Daten-Klassen sind mit Attributen (Eigenschaften, *getter*/*setter*-Methoden) so zu erstellen,
dass diese vom &ldquo;Besucher&rdquo;-Objekt geeignet verwendet werden können.
Typischerweise wird das Datenobjekt als Parameter an eine Methode des &ldquo;Besucher&rdquo;-Objekts übergeben
(die Konvention besteht darin, diese Methode `visit` zu nennen).

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Visitor Patterns*.
Es besteht im Wesentlichen aus sechs Teilen:

  * **Client**: Anwender des *Visitor Patterns*. Er verwaltet die Objektstruktur und weist die Objekte innerhalb der Struktur an,
    wann ein Besucher akzeptiert werden soll.
  * **ObjectStructure**: Dies ist eine Klasse, die alle Objekte enthält, die besucht werden können.
    Es bietet einen Mechanismus zum Traversieren aller Elemente.
    Diese Struktur muss nicht zwingend eine *Collection* sein, es kann irgend eine komplexe Struktur sein, beispielsweise ein *Composite Object*.
  * **ElementBase**: Stellt eine Abstraktionsschnittstelle dar, die die `accept`-Operation deklariert. Dies ist der Einstiegspunkt, an dem ein Objekt vom Besucherobjekt &ldquo;besucht&rdquo; werden kann.
    Jedes Objekt aus einer *Collection* sollte diese Abstraktionsschnittstelle implementieren, um besucht werden zu können.
  * **ConcreteElement**: Diese Klassen erben von der abstrakten Basisklasse `ElementBase` oder implementieren eine Schnittstelle
    und definieren eine `accept`-Operation. Das *Visitor*-Objekt wird durch die `accept`-Operation an dieses Objekt übergeben.
  * **VisitorBase**: Deklariert eine `visit`-Methode (Operation) für jede Klasse von `ConcreteElement` in der Objektstruktur.
    Der Name und die Signatur der Operation identifizieren die Klasse, die die Anforderung an den Visitor sendet.
    Auf diese Weise kann der Besucher die konkrete Klasse des besuchten Elements bestimmen.
    So kann der Besucher direkt über diese spezielle Schnittstelle auf die fraglichen Elemente zugreifen.
  * **ConcreteVisitor**: Implementiert jede von einem Visitor deklarierte Operation (Methode).
    Jede Operation implementiert ein Fragment eines Algorithmus, der für die entsprechende Klasse oder das entsprechende Objekt in der Objektstruktur definiert ist.
    `ConcreteVisitor` stellt den Kontext für den Algorithmus bereit und speichert seinen lokalen Status.
    Dieser Zustand sammelt häufig Ergebnisse während des Durchlaufens der Struktur.

<img src="dp_visitor_pattern.svg" width="600">

*Abbildung* 2: Schematische Darstellung des *Visitor Patterns*.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

*Hinweis*: Im konzeptionellen Beispiel ist der Aspekt `enable_shared_from_this` und `shared_from_this` 
mit abgehandelt.

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/visitor/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Visitor)

vor.

#### 'Real-World' Beispiel:

Im Buch [Entwurfsmuster: Das umfassende Handbuch](https://www.amazon.de/Entwurfsmuster-umfassende-Handbuch-Matthias-Geirhos/dp/3836227622)
von Matthias Geirhos findet sich zu diesem Entwurfsmuster ein Beispiel aus der Welt des Onlinehandels vor.
Sagen wir, ein Onlinehändler würde Bücher, Spiele und Videos verkaufen.
Das ist nichts Neues, und ein Warenkorb mit Büchern, Spielen und Videos stellt auch keine große Herausforderung dar.

Nun aber kommen die Methoden ins Spiel. Mit den Elementen eines Warenkorbs kann man sehr unterschiedliche Dinge anstellen wie zum Beispiel:

  * Berechnung des Gesamtpreises aller Artikel im Warenkorb,
  * Zusammenstellung des Inhalts des Warenkorbs als HTML für die Website des Onlinehandels,
  * Erstellung einer Rechnung zum Inhalt des Warenkorbs als PDF,
  * ...

Und natürlich gibt es noch viele Methoden, die nur einzelnen Klassen (`Buch`, `Spiel`, ...) vorbehalten sind.

Damit sind wir im Zentrum des Musters angekommen: Es trennt die Klassenhierarchie von den Operationen, die
stattdessen in eine zweite Hierarchie wandern. Und anstatt die Operation direkt aufzurufen,
erstellen wir ein Objekt für diese auszuführende Operation (den so genannten *Visitor*) und übergeben es
dem Objekt der fachlichen Hierarchie (der so genannten *ObjectStructure*),
die dann die Operation aufruft.

Studieren Sie den Beispielcode aus dem Buch und führen Sie diesen in ein C++-Programm über. Betrachten Sie hierzu auch *Abbildung* 2:

<img src="dp_visitor_pattern_onlineshop.svg" width="700">

*Abbildung* 3: Ein Onlinehandel modelliert mit dem *Visitor Pattern*.

Studieren Sie die Realisierung der zwei *Visitor*-Klassen, eine für die Berechnung des Gesamtpreises aller Artikel im Warenkorb und eine weitere
zur Darstellung des Inhalts des Warenkorbs in HTML.

Implementieren Sie zwei weitere *Visitor*-Klassen: Eine namens `CountVisitor`, die einfach die Anzahl aller Artikel im Warenkorb bestimmt.
Und eine zweite Klasse `TextVisitor`, die den Inhalt des Warenkorbs in textueller Form für eine Versandbestätigung zusammenstellt.


## Weiterarbeit:

Eng verwandt mit dem  *Visitor Pattern* ist das  *Double Dispatch* Pattern. Siehe hierzu

[Visitor and Double Dispatch](https://refactoring.guru/design-patterns/visitor-double-dispatch)

und 

[Double Dispatch in C++](http://www.vishalchovatiya.com/double-dispatch-in-cpp/)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
