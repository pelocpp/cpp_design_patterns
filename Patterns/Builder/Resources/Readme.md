# Builder Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_builder_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*


###### In einem Satz:

&bdquo;Um komplexe und komplizierte Objekte st�ckweise und intuitiver erstellen zu k�nnen.&rdquo;


#### Ziel / Absicht:

Das *Builder Pattern* ist ein Entwurfsmuster, mit dem schrittweise komplexe Objekte mit der richtigen Reihenfolge von Aktionen erstellt werden k�nnen.
Die Konstruktion wird von einem *Director*-Objekt gesteuert,
das nur den Objekttyp kennen muss, den es erstellen soll.

#### L�sung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Builder Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Product**: Klasse, die das komplexe Objekt repr�sentiert, das zu erstellen ist.
  * **Builder**: Abstrakte Basisklasse (oder Schnittstelle) f�r `Builder`-Objekte. Es werden die Schritte definiert,
    die ausgef�hrt werden m�ssen, um ein komplexes Objekt (Produkt) korrekt zu erstellen.
    Typischerweise ist jeder Schritt eine abstrakte Methode, die durch eine konkrete Implementierung �berschrieben wird.
  * **ConcreteBuilder**: Stellt eine Implementierung der `Builder`-Schnittstelle bereit. Ein `Builder`-Objekt ist ein Objekt,
    das andere komplexe Objekte ("Produkte") erstellen kann.
  * **Director**: Stellt die Klasse dar, die den Algorithmus steuert, der zum Erstellen des komplexen Objekts verwendet wird.

<img src="dp_builder_pattern.svg" width="550">

*Abbildung* 1: Schematische Darstellung des *Builder Patterns*.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Ein etwas ausf�hrlicheres Beispiel

Die Ausgaben des konzeptionellen Beispiels lauten:

```
Standard basic product:
Product parts: Part A1

Standard full featured product:
Product parts: Part A1, Part B1, Part C1

Custom product:
Product parts: Part A1, Part C1
```

---

#### Ein erstes &bdquo;Real-World&rdquo; Beispiel:

Das &bdquo;Real-World&rdquo; Beispiel zu diesem Entwurfsmuster orientiert sich an den UI-Bibliotheken von Java.
Wir implementieren - nat�rlich stark vereinfacht - einen Layoutmanager.
Das Ergebnis k�nnten Java-Containerobjekte sein, oder - etwas einfacher gestrickt - in unserem Fall HTML-Code.

Folgende Klassen sind an dem Beispiel beteiligt:

###### Klasse `HtmlPage`

Die Klasse `HtmlPage` steht f�r das *Produkt* des Entwurfsmusters, in unserem Fall die zu erstellende HTML-Seite.
Das Produkt enth�lt einer Reihe von UI-Steuerelementen, wir f�hren zu diesem Zweck eine
weitere (Hilfs-)Klasse `Widget` ein. Ein `HtmlPage`-Objekt besitzt eine Liste mit `Widget`-Objekten.
Wesentlich bei dieser Klasse ist, dass sie den fertig generierten HTML-Code, der durch einen Layoutmanager erzeugt wird,
enth�lt. �ber eine *getter*-Methode `getHtmlCode` ist dieser verf�gbar.

###### Abstrakte Klasse `LayoutManager`

Diese Klasse entspricht der abstrakten Klasse *Builder*.
Die Methode `buildPart` aus dem allgemeinen UML-Diagramm findet ihre Entsprechung in der Methode `addWidget`.
Der wiederholte Aufruf der `addWidget`-Methode "konfiguriert" gewisserma�en das Produkt.

Die `getProduct`-Methode aus dem allgemeinen UML-Diagramm entspricht der Methode `getHtmlPage`.
Etwas abweichend vom allgemeinen UML-Diagramm ist hierzu noch ein vorgelagerter Aufruf der `render`-Methode,
die das eigentliche Ergebnis berechnet.

###### Konkrete Klassen `FlowLayoutManager`, `BorderLayoutManager` und `BoxLayoutManager`

Diese Klassen sind Ableitungen von der abstrakten Basisklasse `LayoutManager`.
In ihrem Aufbau sind sie sehr �hnlich,
sie unterscheiden sich lediglich in der Generierung des HTML-Codes.
Je nach der Funktionsweise des Layouts sind die Widgets in einer Reihe, in einer Spalte
und bzw. oder mit einer entsprechenden Kopf- und Fu�zeile anzuzeigen.

Zentral in diesen Klassen ist nat�rlich die konkrete Realisierung der beiden Methoden
`render` und `addWidget`.

###### Klasse `Layouter`

Die `Layouter`-Klasse �bernimmt die Funktion der *Director*-Klasse.
Das Pendant zur `construct`-Methode ist hier die `doLayout`-Methode.

###### Klasse `Widget`

Die Klasse `Widget` ist eine Hilfsklasse und verwaltet den erzeugten HTML-Code.

Einen �berblick �ber die beteiligten Klassen und ihren Zusammenhang mit dem *Builder Pattern*
entnehmen Sie *Abbildung* 2:

<img src="dp_builder_pattern_layoutmanager.svg" width="750">

*Abbildung* 2: Implementierung eines LayoutManagers mit dem *Builder Pattern*.

Weitere Details zur Umsetzung des Beispiels entnehmen Sie bitte dem [Quellcode](../LayoutManagerExample.cpp).
Die Ausgaben des &bdquo;Real-World&rdquo;-Beispiels lauten:

```
HTML: HTML-Code for BorderLayoutManager
HTML: HTML-Code for BoxLayoutManager
HTML: HTML-Code for FlowLayout
```

---

#### Ein zweites &bdquo;Real-World&rdquo; Beispiel: Fluent Builder

*Bemerkung*:<br />
Diese Anwendung des Builder Patterns wird auch als &bdquo;Named Arguments in C++&rdquo; bezeichnet.

Wir betrachten nun ein Beispiel, in dem eine Klasse (Klasse `Person`)
viele Daten (hier: zur Person und zum Beruf) haben kann.

Nat�rlich k�nnte man dies alles mit einer einzigen Klasse (hier: `Person`)
�ber unterschiedliche Konstruktoren und *setter*-Methoden abhandeln.
Bei einer Klasse mit sehr vielen Instanzvariablen kann dies bisweilen 
un�bersichtlich werden:

```cpp
01: class Person
02: {
03: private:
04:     // personal details
05:     std::string m_name;     
06:     std::string m_street_address;
07:     std::string m_post_code;
08:     std::string m_city;
09:     std::string m_country;
10: 
11:     // employment details
12:     std::string m_sector;
13:     std::string m_company_name;
14:     std::string m_position;
15: 
16:     Person(std::string name) : m_name{ name } {}
17: };
```

Anstatt all diese konstruktionsbezogenen Methoden (Konstruktoren, *setter*-Methoden)
der Klasse `Person` hinzuzuf�gen,
delegieren wir diese Aufgabe an eine separate Klasse &ndash; wir nennen sie `PersonBuilder`.

Studieren Sie den Quellcode der Klasse `PersonBuilder` genau:
Indem der Konstruktor der Klasse `Person` privat deklariert ist,
zwingen wir Benutzer der Klasse `Person`, die
`PersonBuilder`-Klasse zu verwenden.
Es ist nur die `create(std::string name)`-Schnittstellenmethode an der Klasse
`Person` verf�gbar.

Betrachten Sie den folgenden Quellcode:
Es wird der so genannte &bdquo;*Fluent Builder*&rdquo; Programmierstil demonstriert:

```cpp
Person p{ Person::create("Jack")
    .lives("Great Britain")
    .at("17 Sloane Street")
    .with_postcode("SW1X 9NU")
    .in("London")
    .works("Information Technology")
    .with("Software Manufactur")
    .as_a("Consultant")
};
```

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/builder/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Builder)

vor.

Das &bdquo;Real-World&rdquo;-Beispiel ist eine Portierung eines entsprechenden C#-Beispiels aus dem Buch von Matthias Geirhos,
siehe dazu das [Literaturverzeichnis](../../../Resources/Readme_07_Literature.md).

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
