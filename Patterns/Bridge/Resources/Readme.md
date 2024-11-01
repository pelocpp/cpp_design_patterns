# Bridge Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_bridge_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Trennung der Schnittstelle von einer Implementierung.&rdquo;

Das *Bridge Pattern* ist ein strukturelles Entwurfsmuster,
mit dem sich eine gro�e Klasse oder eine Reihe eng verwandter Klassen in zwei separate Hierarchien aufteilen
lassen &ndash; Abstraktion und Implementierung &ndash;, die beide unabh�ngig voneinander entwickelt werden k�nnen.

#### Problem:

Das *Bridge Pattern* genie�t einen guten Ruf,
da sich mit ihm die abstrakten Elemente der Klasse von den Implementierungsdetails trennen lassen.
Dieses Muster ist vor allem dann zu empfehlen,
wenn die betrachteten Klassen h�ufig variieren,
da sich dann �nderungen an der Codebasis bei minimalem Wissen �ber das Programm leichter durchf�hren lassen.

Betrachten wir ein Beispiel, in dem eine Implementierung auf zwei oder mehreren Realisierungen fu�t.
Zum Beispiel ein Programm, das die Persistenz von Objekten auf verschiedenen Plattformen (Betriebssystemen) realisiert.
Einige Objekte sollen in einer Datenbank und andere Objekte wiederum im Dateisystem des unterlagerten
Betriebssystems gespeichert werden. 
Wird das Programm um diese Funktionalit�t &bdquo;straight forward&rdquo; erweitert,
sind Probleme vorprogrammiert, da die Abstraktion mit der Implementierung verkn�pft wird.
In diesem Fall ist es besser, das *Bridge Pattern*  zu verwenden und die Abstraktion von der Implementierung zu trennen.
Wird dieses Muster nicht verwendet, kann man die Beobachtung machen,
dass Implementierungsdetails in einer Abstraktion enthalten sind.

Ein weiterer Vorteil des *Bridge Patterns* ist die M�glichkeit, Implementierungsdetails zur Laufzeit zu ver�ndern.
Dies erm�glicht es dem Benutzer, Implementierungen zu wechseln, um auf diese Weise zu bestimmen,
wie die Software mit anderen Systemen zusammenarbeitet.

#### L�sung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Bridge Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Abstraction**: Definiert eine Abstraktionsschnittstelle. Sie fungiert als Basisklasse f�r andere verfeinerte Abstraktionsklassen.
    Sie bezieht sich auch auf eine bestimmte Implementierung, die f�r plattformspezifische Funktionen verwendet wird.
  * **RefinedAbstraction**: Stellt eine verfeinerte Variation einer Abstraktionsschnittstelle dar,
    enth�lt jedoch keine Implementierungsdetails. *De facto* erweitert sie nur die Abstraktion.
  * **Implementor**: Definiert die Schnittstelle f�r Implementierungsklassen.
  * **ConcreteImplementor**: Diese Klasse erbt von der Klasse `Implementor`. Es kann mehr als eine Instanz von `Implementor`-Klassen geben,
    die dieselbe Schnittstelle unterst�tzen, aber plattformspezifische Funktionen bereitstellen.

<img src="dp_bridge_pattern_01.svg" width="600">

*Abbildung* 1: Schematische Darstellung des *Bridge Patterns*.

---

#### Abgrenzung zu anderen Entwurfsmustern:


  * Das *Adapter Pattern* implementiert als Objektadapter �hnelt dem *Bridge Pattern*,
  hat jedoch eine andere Absicht.
  Der Zweck des *Bridge Patterns* besteht darin, die Schnittstelle von der Implementierung zu trennen.
  Der Zweck des *Adapter Patterns* besteht darin, eine vorhandene Schnittstelle zu modifizieren.

---


#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Ein etwas ausf�hrlicheres Beispiel

---

#### &bdquo;Real-World&rdquo; Beispiel:

Bei diesem Muster steht eine Schnittstelle im Mittelpunkt,
die als Br�cke fungiert, die die Funktionalit�t konkreter Klassen unabh�ngig
von den Schnittstellenimplementierungsklassen macht.
Beide Klassentypen k�nnen strukturell ver�ndert werden, ohne sich gegenseitig zu beeinflussen.

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

*Abbildung* 2: Ein Anwendungsbeispiel des *Bridge* Patterns.

---

#### Das *Pimpl* Pattern

Das *Pimpl* Pattern kann als ein Anwendungsfall des *Bridge* Patterns angesehen werden:
Bei diesem Pattern geht es darum, die Implementierungsdetails einer bestimmten Klasse zu verbergen,
indem diese in eine separate Implementierungsklasse ausgelagert werden, auf die ein Zeiger zeigt.
Weitere Details hierzu finden sich [hier](https://github.com/pelocpp/cpp_design_patterns/blob/master/Patterns/Pimpl/Resources/Readme.md).

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/bridge/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Bridge)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
