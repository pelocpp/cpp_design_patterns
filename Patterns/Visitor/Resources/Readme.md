# Visitor Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_visitorpattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Hinzuf�gen einer neuen Operation f�r eine Gruppe �hnlicher Objekte oder Hierarchien.&rdquo;

Das *Visitor Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
das eine Menge strukturierter Daten von den Funktionen trennt,
die auf den Daten ausgef�hrt werden. Dies unterst�tzt zum einen das Prinzip der "losen Kopplung"
und es erm�glicht zum anderen das Hinzuf�gen zus�tzlicher Operationen, ohne an den Datenklassen �nderungen vornehmen zu m�ssen.

Im Kern geht es darum, eine Hierarchie von Klassen und Operationen auf diesen Klassen voneinander zu trennen.

#### Prinzip:

Das Muster definiert eine Art Infrastruktur f�r den Zugriff auf komplexe dynamische Daten- und Objektstrukturen.
Dabei wird der dynamischen Struktur eine Methodenschnittstelle gegeben, die ein sogenanntes &bdquo;Besucher&rdquo;-Objekt entgegennimmt
und �ber alle Daten der Struktur schleust. Das &bdquo;Besucher&rdquo;-Objekt l�uft also an allen Elementen der Struktur entlang
und wird von den Elementen �ber eine Methode &bdquo;akzeptiert&rdquo;.
Die Konvention besteht darin, diese Methode `accept` zu nennen.
Dabei ruft das Strukturelement eine Methode im &bdquo;Besucher&rdquo;-Objekt auf,
die speziell f�r den Typ des Strukturelements geschrieben wurde und eine Referenz oder einen Zeiger
auf das Strukturelement in ihrer Parameterliste hat.
Damit hat der Visitor wiederum die Chance, eine Operation auf dem Strukturelement auszuf�hren
und dabei auf dessen Typ zu reagieren.

Der Sinn des Visitors besteht darin, die eigentliche Operation auf den Daten von der Traver�sierung
der Verwaltungs�struktur zu trennen. Aus der Entkopplung dieser beiden Aspekte entstehen
Freiheitsgrade f�r Variationen dieses Entwurfsmusters.

---

### Eine didaktische Herleitung in 4 Schritten:

#### Schritt 1: Ein &bdquo;aufdringlicher&rdquo; Besucher (*intrusive Visitor*)

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
09: private:
10:     std::string m_start;
11:     std::list<std::string> m_content;
12: 
13: public:
14:     Markdown() : m_start{ "* " } {}
15: 
16:     virtual void addToList(const std::string& line) override {
17:         m_content.push_back(line);
18:     }
19: };
20: 
21: class HTML : public Document
22: {
23: private:
24:     std::string m_start;
25:     std::string m_end;
26:     std::list<std::string> m_content;
27: 
28: public:
29:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
30: 
31:     virtual void addToList(const std::string& line) override {
32:         m_content.push_back(line);
33:     }
34: };
```

Und nehmen wir nun ferner an,
dass wir einige neue Operationen auf dieser bestehenden Infrastruktur definieren m�ssen.
Zum Beispiel haben wir eine `Document`-Klasse wie oben gezeigt
und m�chten jetzt, dass verschiedene Dokumente (z.B. `HTML` und `Markdown`) druckbar sind,
also eine Methode `print` bekommen.

Es gibt also eine neue Anforderung (*Concern*) 
und wir m�ssen diese auf irgendeine Weise durch die gesamte Klassenhierarchie propagieren,
indem wir jede einzelne `Document`-Klasse irgendwie unabh�ngig um eine `print`-Methode
erg�nzen.

Was wir jetzt nicht tun wollen, ist, dass wir jedes Mal, wenn wir eine neue Anforderung (*Concern*) erhalten,
in den vorhandenen Code eingreifen und jede Klasse in der Hierarchie (mit zus�tzlichen virtuellen Funktionen) �ndern.

Dies w�rde einen Versto� gegen das *Open*-*Closed*-Prinzip darstellen!
Zum Zweiten gibt es auch noch das *Single*-*Responsibility*-Prinzip, an das wir uns halten wollen.
Kurz gesagt besagt dies, dass wir f�r eine neue Anforderung eine separate Klasse zu erstellen haben.

W�rden wir das jetzt alles Mal f�r einen kurzen Moment au�er Acht lassen,
k�nnten wir folgende Realisierung betrachten:

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
51: static void clientCode()
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

Wie wir sehen, ist diese Vorgehensweise f�r zwei bis drei Klassen mit Schmerzen machbar,
auch wenn wir dabei gegen einige SOLID-Prinzipien versto�en.
Aber stellen Sie sich vor, Sie haben es mit 20 oder mehr Klassen als Teil einer ganzen Hierarchie zu tun,
dann versagt diese Strategie.

Dar�ber hinaus wird dieser Ansatz umst�ndlich, wenn es um mehr als ein *Concern* wie z.B.
Speichern (`save`), Verarbeiten (`process`) usw. geht.
Jedes *Concern* sollte in einer separaten Klasse abgehandelt werden,
um vor allem das *Single*-*Responsibility*-Prinzips zu beachten.


#### Schritt 2: Ein &bdquo;reflektierender&rdquo; Besucher (*reflective Visitor*)

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
58: static void clientCode() {
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

Wie bereits erw�hnt, haben wir nun eine separate Klasse `DocumentPrinter` mit Druckfunktionalit�t
f�r die gesamte Klassenhierarchie erstellt.
Das *Single*-*Responsibility*-Prinzip wird so ber�cksichtigt.

Aber bei diesem Ansatz m�ssen wir Typen bestimmter Klassen identifizieren
(unter Verwendung von `dynamic_cast<>()`),
da wir unabh�ngig voneinander mit einzelnen Objekten in der Hierarchie arbeiten m�ssen.

Dies ist kein Ansatz, der sich effizient skalieren l�sst.
Wenn Sie vor allem den Satz von Klassen erweitern wollen,
um deren Verarbeitung es geht, werden Sie am Ende eine lange Kaskade von `if`/`else`-`if`-Konstrukten
und unn�tige Performanceaufwendungen f�r *RTTI* haben.


#### Schritt 3: Ein &bdquo;klassischer&rdquo; Besucher (*classic Visitor*)

Damit kommen wir nun auf die klassische Umsetzung des *Visitor* Patterns zu sprechen.
Diese wird weiter unten noch n�her erl�utert werden (begleitender Text und UML-Diagramm):

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
33:     std::string m_start;
34:     std::list<std::string> m_content;
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
50:     std::string m_start;
51:     std::string m_end;
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
76: static void clientCode() {
77:     DocumentVisitor* dp = new DocumentPrinter();
78: 
79:     Document* d1 = new HTML;
80:     d1->addToList("This is line");
81:     d1->accept(dp);
82: 
83:     Document* d2 = new Markdown;
84:     d2->addToList("This is another line");
85:     d2->accept(dp);
86: 
87:     delete d1;
88:     delete d2;
89:     delete dp;
90: }
```

Wie Sie sehen k�nnen, haben wir es nun mit zwei Ebenen der Indirektion zu tun.
Damit wurde vor allem vermieden, die zwei Prinzipien
*Open*-*Closed-Principle* und *Single*-*Responsibility-Principle* zu verletzen.

Hierf�r gibt es ein spezielles Schlagwort: *Double Dispatch*, siehe dazu auch *Abbildung* 1:

<img src="dp_visitor_double_dispatch.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Double Dispatch*&ndash;Idioms.

�ber das Objekt `doc` rufen wir die Methode `accept()` auf:

```cpp
doc -> accept (new DocumentPrinter());
```

Diese delegiert auf Grund des virtuellen Methodenaufrufmechanismus den Aufruf an die Methode `HTML::accept`.
Im Kontext dieser Methode finden wir wiederum einen Aufruf

```cpp
dv->visit(this);
```

vor. Dieses Mal wird &ndash; auf Grund des virtuellen Methodenaufrufmechanismus &ndash; 
der Aufruf an die Methode `DocumentPrinter::visit(HTML*)` delegiert (unter Ber�cksichtigung
des Zeigertyps `HTML*`).

#### Schritt 4: Alternativer Ansatz f�r *Double Dispatch* in Modern C++ (`std::variant` und `std::visit`)

Man beachte vorab, dass die Dokumente Klassen `Markdown` und `HTML` nicht mehr einer Klassenhierarchie angeh�ren:


```cpp
01: /* ------ Document Classes -------- */
02: class Markdown
03: {
04: private:
05:     std::string m_start;
06:     std::list<std::string> m_content;
07: 
08: public:
09:     Markdown() : m_start{ "* " } {}
10: 
11:     void addToList(const std::string& line) {
12:         m_content.push_back(line); 
13:     }
14: 
15:     std::string getStart() const { return m_start; }
16:     std::list<std::string> getContent() const { return m_content; }
17: };
18: 
19: class HTML
20: {
21: private:
22:     std::string m_start;
23:     std::string m_end;
24:     std::list<std::string> m_content;
25: 
26: public:
27:     HTML() : m_start{ "<li>" }, m_end{ "</li>" } {}
28: 
29:     void addToList(const std::string& line) {
30:         m_content.push_back(line); 
31:     }
32: 
33:     std::string getStart() const { return m_start; }
34:     std::string getEnd() const { return m_end; }
35:     std::list<std::string> getContent() const { return m_content; }
36: };
37: 
38: /* ------ Specific Printer Visitor Class -------- */
39: class DocumentPrinter
40: {
41: public:
42:     void operator() (const Markdown& md) {
43:         for (const std::string& item : md.getContent()) {
44:             std::cout << md.getStart() << item << std::endl;
45:         }
46:     }
47: 
48:     void operator() (const HTML& hd) {
49:         std::cout << "<ul>" << std::endl;
50:         for (const std::string& item : hd.getContent()) {
51:             std::cout << "    " << hd.getStart() << item << hd.getEnd() << std::endl;
52:         }
53:         std::cout << "</ul>" << std::endl;
54:     }
55: };
56: 
57: /* ------ std::variant & std::visit -------- */
58: static void clientCode() {
59:     HTML hd;
60:     hd.addToList("This is line");
61:     std::variant<Markdown, HTML> doc = hd;
62:     DocumentPrinter dp;
63:     std::visit(dp, doc);
64: 
65:     Markdown md;
66:     md.addToList("This is another line");
67:     doc = md;
68:     std::visit(dp, doc);
69: }
```

Wir setzen nun die *Modern C++* Klasse `std::variant` und die Funktion `std::visit` ein.

Die Zeile

```cpp
std::variant<Markdown, HTML> document;
```

besagt, dass wir der Variablen `document` entweder ein `Markdown`- oder ein `HTML`-Objekt
zuweisen k�nnen. 

Die `std::visit`-Methode wiederum akzeptiert ein *Callable*-Objekt,
d.h. in unserem Beispiel ein `DocumentPrinter`-Objekt,
das f�r alle m�glichen Typen einen �berladenen Funktionsoperator `operator()` &ndash;
auch als *Funktor* bezeichnet &ndash; bereitstellt.

#### Schritt 5: Noch einmal der alternative Ansatz: `std::variant`, `std::visit` und ein generisches Lambdaobjekt 

Der letzte Schritt aus dieser Betrachtung ist sehr �hnlich zu Schritt 4.

Die beiden Klassen `HTML` und `Markdown` sind unver�ndert.

An die Stelle eines aufrufbaren Objekts (Klasse mit �berladenem Operator `operator()`)
tritt nun ein generisches Lambdaobjekt.

Techniken aus dem Modern C++ Umfeld wie `decltype`, `std::remove_reference`, `std::is_same`
und `if constexpr` kommen jetzt zum Einsatz:

```cpp
01: static void clientCode06() {
02: 
03:     auto genericVisitor = [](const auto& doc) {
04: 
05:         using DocumentType = decltype (doc);
06: 
07:         using DocumentTypeWithoutRef = std::remove_reference<DocumentType>::type;
08: 
09:         using DocumentTypeWithoutRefAndConst
10:             = std::remove_const<DocumentTypeWithoutRef>::type;
11: 
12:         if constexpr (std::is_same<DocumentTypeWithoutRefAndConst, HTML>::value == true)
13:         {
14:             std::cout << "<ul>" << std::endl;
15:             for (const std::string& item : doc.getContent()) {
16:                 std::cout << "    " << doc.getStart() << item << doc.getEnd() << std::endl;
17:             }
18:             std::cout << "</ul>" << std::endl;
19:         }
20:         else if constexpr (std::is_same<DocumentTypeWithoutRefAndConst, Markdown>::value == true)
21:         {
22:             for (const std::string& item : doc.getContent()) {
23:                 std::cout << doc.getStart() << item << std::endl;
24:             }
25:         }
26:         else
27:         {
28:             std::cout << "Unknown Document Format! " << std::endl;
29:         }
30:     };
31: 
32:     HTML hd;
33:     hd.addToList("This is line");
34:     std::variant<Markdown, HTML> var{ hd };
35:     std::visit(genericVisitor, var);
36: 
37:     Markdown md;
38:     md.addToList("This is another line");
39:     var = md;
40:     std::visit(genericVisitor, var);
41: }
```

#### Zusammenfassung:

Die Traver�sierung wird durch die erw�hnte Infra�struktur aus Methoden �bernommen.
Die durch den Visitor transpor�tierte Operation wird in einer Kindklasse der Visitor�schnitt�stelle implementiert.
Damit lassen sich beliebige Operationen definieren
und durch den allgemeinen Traversierungs�mechanismus in die Objekt�struktur tragen.
Mit dem Namen des Visitors wird das Verhalten des Musters gew�rdigt.
Das Visitor�objekt geht die Objekte in der Objekt�struktur &bdquo;besuchen&rdquo;.

Das Ergebnis der Trennung von Objektstruktur und Funktionen (Algorithmen) ist ein Datenmodell
mit eingeschr�nkter Funktionalit�t und einer Gruppe von &bdquo;*Besuchern*&rdquo;,
die Operationen auf den Daten ausf�hren.
Ein weiterer Vorteil ist die M�glichkeit, einen neuen *Besucher* hinzuf�gen zu k�nnen,
ohne dabei die vorhandene Struktur �ndern zu m�ssen. 
Die Daten-Klassen sind mit Attributen (Eigenschaften, *getter*/*setter*-Methoden) so zu erstellen,
dass diese vom &bdquo;Besucher&rdquo;-Objekt geeignet verwendet werden k�nnen.
Typischerweise wird das Datenobjekt als Parameter an eine Methode des &bdquo;Besucher&rdquo;-Objekts �bergeben
(die Konvention besteht darin, diese Methode `visit` zu nennen).

---

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Visitor Patterns*.
Es besteht im Wesentlichen aus sechs Teilen:

  * **Client**: Anwender des *Visitor Patterns*. Er verwaltet die Objektstruktur und weist die Objekte innerhalb der Struktur an,
    wann ein Besucher akzeptiert werden soll.
  * **ObjectStructure**: Dies ist eine Klasse, die alle Objekte enth�lt, die besucht werden k�nnen.
    Es bietet einen Mechanismus zum Traversieren aller Elemente.
    Diese Struktur muss nicht zwingend eine *Collection* sein, es kann irgend eine komplexe Struktur sein, beispielsweise ein *Composite Object*.
  * **ElementBase**: Stellt eine Abstraktionsschnittstelle dar, die die `accept`-Operation deklariert. Dies ist der Einstiegspunkt, an dem ein Objekt vom Besucherobjekt &bdquo;besucht&rdquo; werden kann.
    Jedes Objekt aus einer *Collection* sollte diese Abstraktionsschnittstelle implementieren, um besucht werden zu k�nnen.
  * **ConcreteElement**: Diese Klassen erben von der abstrakten Basisklasse `ElementBase` oder implementieren eine Schnittstelle
    und definieren eine `accept`-Operation. Das *Visitor*-Objekt wird durch die `accept`-Operation an dieses Objekt �bergeben.
  * **VisitorBase**: Deklariert eine `visit`-Methode (Operation) f�r jede Klasse von `ConcreteElement` in der Objektstruktur.
    Der Name und die Signatur der Operation identifizieren die Klasse, die die Anforderung an den Visitor sendet.
    Auf diese Weise kann der Besucher die konkrete Klasse des besuchten Elements bestimmen.
    So kann der Besucher direkt �ber diese spezielle Schnittstelle auf die fraglichen Elemente zugreifen.
  * **ConcreteVisitor**: Implementiert jede von einem Visitor deklarierte Operation (Methode).
    Jede Operation implementiert ein Fragment eines Algorithmus, der f�r die entsprechende Klasse oder das entsprechende Objekt in der Objektstruktur definiert ist.
    `ConcreteVisitor` stellt den Kontext f�r den Algorithmus bereit und speichert seinen lokalen Status.
    Dieser Zustand sammelt h�ufig Ergebnisse w�hrend des Durchlaufens der Struktur.

<img src="dp_visitor_pattern.svg" width="600">

*Abbildung* 2: Schematische Darstellung des *Visitor Patterns*.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

*Hinweis*: Im konzeptionellen Beispiel ist der Aspekt `enable_shared_from_this` und `shared_from_this` 
mit abgehandelt.

---

#### Erstes &bdquo;Real-World&rdquo; Beispiel:

Das *Visitor*-Entwurfsmuster l�sst sich in *Modern C++* mit `std::variant` und `std::visit` sehr einfach umsetzen.

Hierbei gilt es eine Besonderheit zu betrachten:
Wir k�nnen mit der C++-Template-Technik die Realisierung so gestalten,
dass wir auf den virtuellen Methodenaufrufmechanismus **nicht** angewiesen sind!
Bei der klassischen Umsetzung des Musters ist dieser vorhanden.

Wir betrachten eine Buchhandlung (Klasse `Bookstore`), die B�cher und DVDs (Klassen `Book` und `Movie`) verkauft. 

```cpp
class Book
{
  ...
};

class Movie
{
  ...
};
```

1. *Frage*:
Wie ist die Schnittstelle eines Konstruktors f�r die `Bookstore`-Klasse zu definieren,
wenn dieser `Book`- und `Movie`-Objekte gemischt in einem `std::vector`-Objekt aufnehmen kann?

```cpp
Book cBook { "C", "Dennis Ritchie", 11.99, 12 };
Book javaBook{"Java", "James Gosling", 17.99, 21 };
Book cppBook{"C++", "Bjarne Stroustrup", 16.99, 4 };
Book csharpBook{"C#", "Anders Hejlsberg", 21.99, 8 };

Movie movieTarantino{ "Once upon a time in Hollywood", "Quentin Tarantino", 6.99, 3 };
Movie movieBond{ "Spectre", "Sam Mendes", 8.99, 6 };

using MyBookstore = Bookstore<Book, Movie>;

MyBookstore bookstore = MyBookstore {
    cBook, movieBond, javaBook, cppBook, csharpBook, movieTarantino
};
```

Entwerfen Sie drei rudiment�re Klassen `Book`, `Movie` und `Bookstore`,
um das gezeigte Code-Fragment �bersetzen zu k�nnen.


2. *Frage*:
Wie ist in der Klasse `Bookstore` eine Methode `totalBalance` zu implementieren, um den Gesamtwert des Warenbestands in
der Buchhandlung zu berechnen? Hier k�nnten `std::variant` und `std::visit` zum Einsatz gelangen.

```cpp
double balance = bookstore.totalBalance();
std::cout << "Total value of Bookstore: " << balance << std::endl;
```

Noch ein Hinweis:

Die `std::visit`-Funktion hat als ersten Parameter ein *Callable* (Funktor, generisches Lambda),
um auf das `std::variant`-Objekt zugreifen zu k�nnen. Im `std::variant`-Objekt wiederum kann &ndash; in unserer Betrachtung &ndash;
ein `Book`- oder ein `Movie`-Objekt enthalten sein. Wenn diese Klassen
eine Methode desselben Namens (derselben Schnittstelle) enthalten,
wie zum Beispiel `getPrice` oder `getCount`, dann haben Sie das Ziel fast schon erreicht.

*Zusatzaufgabe*:
Realisieren Sie eine Methode `addMedia`, die ein beliebiges &bdquo;Media&rdquo;-Objekt einem `Bookstore`-Objekt hinzuf�gen kann.
Nat�rlich muss der Datentyp des &bdquo;Media&rdquo;-Objekts (also z.B. `Book` oder `Movie`) f�r das `Bookstore`-Objekt
bereits bekannt sein:

```cpp
Book csharpBook{ "C#", "Anders Hejlsberg", 21.99, 1 };
bookstore.addMedia(csharpBook);
```

---

#### Zweites &bdquo;Real-World&rdquo; Beispiel:

Im Buch [Entwurfsmuster: Das umfassende Handbuch](https://www.amazon.de/Entwurfsmuster-umfassende-Handbuch-Matthias-Geirhos/dp/3836227622)
von Matthias Geirhos findet sich zu diesem Entwurfsmuster ein Beispiel aus der Welt des Onlinehandels vor.
Sagen wir, ein Onlineh�ndler w�rde B�cher, Spiele und Videos verkaufen.
Das ist nichts Neues, und ein Warenkorb mit B�chern, Spielen und Videos stellt auch keine gro�e Herausforderung dar.

Nun aber kommen die Methoden ins Spiel. Mit den Elementen eines Warenkorbs kann man sehr unterschiedliche Dinge anstellen wie zum Beispiel:

  * Berechnung des Gesamtpreises aller Artikel im Warenkorb,
  * Zusammenstellung des Inhalts des Warenkorbs als HTML f�r die Website des Onlinehandels,
  * Erstellung einer Rechnung zum Inhalt des Warenkorbs als PDF,
  * ...

Und nat�rlich gibt es noch viele Methoden, die nur einzelnen Klassen (`Buch`, `Spiel`, ...) vorbehalten sind.

Damit sind wir im Zentrum des Musters angekommen: Es trennt die Klassenhierarchie von den Operationen, die
stattdessen in eine zweite Hierarchie wandern. Und anstatt die Operation direkt aufzurufen,
erstellen wir ein Objekt f�r diese auszuf�hrende Operation (den so genannten *Visitor*) und �bergeben es
dem Objekt der fachlichen Hierarchie (der so genannten *ObjectStructure*),
die dann die Operation aufruft.

Studieren Sie den Beispielcode aus dem Buch und f�hren Sie diesen in ein C++-Programm �ber. Betrachten Sie hierzu auch *Abbildung* 2:

<img src="dp_visitor_pattern_onlineshop.svg" width="700">

*Abbildung* 3: Ein Onlinehandel modelliert mit dem *Visitor Pattern*.

Studieren Sie die Realisierung der zwei *Visitor*-Klassen, eine f�r die Berechnung des Gesamtpreises aller Artikel im Warenkorb und eine weitere
zur Darstellung des Inhalts des Warenkorbs in HTML.

Implementieren Sie zwei weitere *Visitor*-Klassen: Eine namens `CountVisitor`, die einfach die Anzahl aller Artikel im Warenkorb bestimmt.
Und eine zweite Klasse `TextVisitor`, die den Inhalt des Warenkorbs in textueller Form f�r eine Versandbest�tigung zusammenstellt.

---

## Weiterarbeit:

Eng verwandt mit dem  *Visitor Pattern* ist das  *Double Dispatch* Pattern. Siehe hierzu

[Visitor and Double Dispatch](https://refactoring.guru/design-patterns/visitor-double-dispatch)

und 

[Double Dispatch in C++](https://vishalchovatiya.com/posts/double-dispatch-in-cpp/)

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/visitor/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Visitor)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
