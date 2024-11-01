# Decorator Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_decorator_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Erleichtert das Hinzuf�gen zus�tzlicher Funktionalit�t zu Objekten.&rdquo;

Das *Decorator Pattern* ist ein strukturelles Entwurfsmuster, das die Funktionalit�t eines Objekts erweitert,
indem es dieses mit einer oder mehreren Dekorationsklassen &bdquo;umh�llt&rdquo;, oder gewisserma�en &bdquo;dekoriert&rdquo;.
*Decorator* Klassen k�nnen vorhandene Elemente �ndern und zur Laufzeit neue Methoden und Eigenschaften hinzuf�gen.

##### Hinweis:

Das Spezialisieren (Vererbung) einer Klasse ist typischerweise das Erste, was einem einf�llt,
wenn man das Verhalten eines Objekts �ndern (erweitern) m�chte.
Die Vererbung weist jedoch einige schwerwiegende Einschr�nkungen auf, die es zu beachten gilt:

  * Die Vererbung ist ein statisches Konzept, also etwas, was zur �bersetzungszeit festgelegt sein muss.
    Zur Laufzeit l�sst sich das Verhalten eines bestimmten Objekts nicht �ndern.
    Ferner kann man nur ein ganzes Objekt durch ein anderes Objekt ersetzen, das aus einer anderen Unterklasse erstellt wurde.
    Das *Decorator Pattern* zielt auf das �ndern von Verhaltensweisen bestimmter Methoden ab.
  * Unterklassen k�nnen nur eine �bergeordnete Klasse haben. In den meisten Sprachen l�sst das Prinzip der Vererbung nicht zu,
    dass eine Klasse das Verhalten mehrerer Klassen gleichzeitig erbt (Prinzip der *Mehrfachvererbung*, in C++ allerdings m�glich).

Eine M�glichkeit, diese Einschr�nkungen zu �berwinden, ist die Verwendung von
*Aggregation* oder *Komposition* anstelle von Vererbung.
Beide Alternativen funktionieren fast gleich: Ein Objekt hat einen Verweis (Referenz, Zeiger) 
auf ein anderes Objekt und *delegiert* ihm dadurch T�tigkeiten.
Bei der Vererbung kann das Objekt diese Arbeit *selbst* ausf�hren,
es *erbt* das Verhalten von seiner Oberklasse.

Mit diesem Ansatz (Gebrauch eines Verweises) k�nnen Sie das verkn�pfte &bdquo;Hilfs&rdquo;-Objekt leicht durch ein
anderes ersetzen und so das Verhalten des Containers zur Laufzeit �ndern.
Ein Objekt kann das Verhalten mehrerer Klassen verwenden,
indem es Verweise auf mehrere Objekte verwaltet.

<img src="dp_decorator_01.svg" width="550">

*Abbildung* 1: Vererbung versus Aggregation.

#### Problem:

Das Objekt, das Sie verwenden m�chten, f�hrt die grundlegenden Funktionen aus, die Sie ben�tigen.
M�glicherweise m�ssen Sie dem Objekt jedoch noch einige zus�tzliche Funktionalit�ten hinzuf�gen,
die vor oder nach der Basisfunktionalit�t des betrachteten Objekts auszuf�hren sind.

#### L�sung:

*Wrapper* oder H�lle ist der alternative Kurzname f�r das Decorator-Pattern,
der die Hauptidee des Musters klarer zum Ausdruck bringt. Ein &bdquo;Wrapper&rdquo; ist ein Objekt,
das mit einem &bdquo;Ziel&rdquo;-Objekt verkn�pft werden kann. Das Wrapper-Objekt enth�lt die gleichen Methoden
wie das Ziel und delegiert alle eingehenden Requests an es.
Der Wrapper kann das Verhalten jedoch �ndern,
indem er entweder vor oder nach dem Weiterleiten der Anforderung an das Ziel
zus�tzliches Verhalten hinzuf�gt.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Decorator Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Component**: Abstrakte Basisklasse f�r alle konkreten Komponenten und Decorator-Klassen.
    Diese Klasse definiert diejenigen Klassenelemente, die standardm��ig von diesen Klassentypen implementiert werden m�ssen.
  * **ConcreteComponent**: Diese Klasse erbt von der Klasse `Component`. Es kann diese Klasse mehrfach geben.
    Es wird damit jeweils ein Objekttyp definiert, der von einer Decorator-Klasse umh�llt werden kann.
  * **DecoratorBase**: Stellt die abstrakte Basisklasse f�r alle Decorator-Klassen dar. Es wird ein Konstruktor hinzugef�gt,
    der ein `Component-Objekt` als Parameter akzeptiert. Das �bergebene Objekt ist die Komponente, die umh�llt wird.
    Da das umh�llte Objekt von `Component` erben muss, kann es sich um ein `ConcreteComponent`-Objekt
    oder ein anderes Decorator-Objekt handeln. Auf diese Weise k�nnen mehrere Decorator-Objekte auf ein einzelnes Objekt angewendet werden.
  * **ConcreteDecorator**: Diese Klasse repr�sentiert ein konkretes Decorator-Objekt f�r eine Komponente.
    Es kann einige zus�tzliche Methoden enthalten, die die Funktionalit�t der Komponente erweitern.
    Die `operation`-Methoden k�nnen auf zwei Arten verwendet werden:
    Sie k�nnen unver�ndert bleiben und in diesem Fall wird die Basisklassenmethode der Komponente aufgerufen
    oder die `operation`-Methode kann ge�ndert werden oder vollst�ndig durch eine neue Implementierung ersetzt werden.

<img src="dp_decorator_02.svg" width="750">

*Abbildung* 2: Schematische Darstellung des *Decorator* Patterns.


##### Hinweis:

W�hrend ein Dekorateur seine Funktionalit�t vor oder nach Weiterleiten der Anforderung an das Objekt,
was es dekoriert, hinzuf�gen kann, sollte die Kette der Instanziierung immer mit dem `ConcreteComponent`-Objekt enden.

#### Implementierung:

Erstellen Sie eine abstrakte Klasse, die sowohl die urspr�ngliche Klasse darstellt
als auch die neuen Methoden besitzt, die der Klasse hinzugef�gt werden sollen.
Platzieren Sie in den Dekoratoren die neuen Methoden-Anrufe
vor oder nach den Anrufen an das eingeh�llte Objekt, um die richtige Reihenfolge zu erhalten.

---

## Pro / Kontra:

###### Pros:

  * Das Verhalten eines Objekts kann erweitert werden, ohne eine neue Unterklasse erstellen zu m�ssen.
  * Einem Objekt k�nnen zur Laufzeit Verantwortlichkeiten hinzugef�gt oder daraus entfernt werden.
  * Es k�nnen mehrere Verhaltensweisen kombiniert werden, indem man ein Objekt in mehrere Dekoratoren einh�llt.
  * *Single Responsibility Principle*: Eine monolithische Klasse,
    die viele m�gliche Verhaltensvarianten implementiert, kann so in mehrere kleinere Klassen unterteilt werden.

###### Kontras:

  * Es ist schwierig, einen bestimmten Wrapper vom Wrapper-Stapel zu entfernen.
  * Es ist schwierig, einen Dekorateur so zu implementieren, dass sein Verhalten nicht von der Reihenfolge im Dekorationsstapel abh�ngt.
  * Der anf�ngliche Konfigurationscode von Ebenen (H�llen) sieht m�glicherweise nicht sehr gut aus.

---

#### Abgrenzung zu anderen Entwurfsmustern:

  * Das *Composite Pattern* ist ein strukturelles Muster �hnlich dem Decorator.
  Der Hauptunterschied besteht darin, dass das *Decorator Muster* nur ein Kindobjekt hat.

  * Dar�ber hinaus f�gt das Decorator-Muster einem Objekt neue Verantwortlichkeiten hinzu,
  w�hrend das *Composite Pattern* die Ergebnisse seiner Kinder zusammenfasst.

  * Das *Adapter Pattern* �ndert die Schnittstelle eines Objekts,
  durch das *Decorator Muster* werden die Verantwortlichkeiten / wird die Funktionalit�t
  eines Objekts erweitert.

  * Das *Strategy Design Pattern* verwendet Objekte, um eine Implementierung zu �ndern.
  Der *Dekorateur* verwendet Objekte, um die Funktionalit�t eines Objekts zu erweitern.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

*Hinweis*: Man beachte in dem konzeptionellen Beispiel auch die Demonstration
der Deklaration zur Laufzeit:

```cpp
01: // component which is going to be decorated
02: std::shared_ptr<Component> component{ std::make_shared<ConcreteComponent>() };
03: 
04: // run-time dependent decorator
05: std::shared_ptr<Component> decorator;
06: 
07: if (true)   // <== change 'true' to 'false'
08: {
09:     std::shared_ptr<Component> decorator1{ std::make_shared<ConcreteDecoratorA>(component) };
10:     decorator = std::make_shared<ConcreteDecoratorB>(decorator1);
11: 
12:     std::cout << "Client: Now I've this decorated component (if):" << std::endl;
13: }
14: else {
15:     std::shared_ptr<Component> decorator1 {std::make_shared<ConcreteDecoratorB>(component)};
16:     decorator = std::make_shared<ConcreteDecoratorA>(decorator1);
17: 
18:     std::cout << "Client: Now I've that decorated component (else):" << std::endl;
19: }
```

---

#### &bdquo;Real-World&rdquo; Beispiel:

[Quellcode &bdquo;Dynamic Shapes&rdquo;](../DynamicShapes.cpp)

---

Das &bdquo;Real-World&rdquo; Beispiel zu diesem Entwurfsmuster besch�ftigt sich mit semi-grafischen GDI-Elementen (*Graphics Device Interface*)
wie Kreisen, Rechtecken, etc.
In einer Grundausf�hrung lassen sich derartige Figuren einfach schwarz-wei� zeichnen. Auf Wunsch, auch zur Laufzeit, k�nnte man diese Figuren
farbig und/oder mit einer entsprechenden Transparenz zeichnen.

Diese &bdquo;Zusatzw�nsche&rdquo; lassen sich sehr einfach und elegant mit dem *Decorator Pattern* Entwurfsmuster in die Tat umsetzen.
Einen entsprechenden Satz an GDI- und Dekorator-Klassen finden Sie in *Abbildung* 3 vor:

<img src="dp_decorator_03_shapes.svg" width="700">

*Abbildung* 3: Das *Decorator* Pattern in der Anwendung mit GDI-Elementen.

Es folgen vier exemplarische Anwendungsbeispiele, die das Zeichen von GDI-Elementen

  * ohne Dekoration
  * mit Farbe
  * mit Transparenz
  * mit Farbe und Transparenz

verdeutlichen sollen. 

###### *Szenario* 1:

*Code*:

```cpp
std::shared_ptr<IShape> circle = std::make_shared<Circle>(0.5f);
std::cout << circle->draw() << std::endl;
```

*Ausgabe*:

```
A circle of radius 0.500000
```

###### *Szenario* 2:

*Code*:

```cpp
std::shared_ptr<IShape> circle{
    std::make_shared<Circle>(0.5)
};
std::shared_ptr<IShape> redCircle{
    std::make_shared<ColoredShapeDecorator>(circle, "red") 
};
std::cout << redCircle->draw() << std::endl;
```

*Ausgabe*:

```
A circle of radius 0.500000 has color red
```

###### *Szenario* 3:

*Code*:

```cpp
std::shared_ptr<IShape> square{
    std::make_shared<Square>(3.0) 
};

std::shared_ptr<IShape> transparentSquare{
    std::make_shared<TransparentShapeDecorator>(square, static_cast<uint8_t>(85)) 
};

std::cout << transparentSquare->draw() << std::endl;
```

*Ausgabe*:

```
A square with side 3 has 33.3333% transparency
```

###### *Szenario* 4:

*Code*:

```cpp
std::shared_ptr<IShape> circle{
    std::make_shared<Circle>(15.0) 
};

std::shared_ptr<IShape> greenCircle{ 
    std::make_shared<ColoredShapeDecorator>(circle, "green")
};

std::shared_ptr<IShape> greenTransparentCircle{
    std::make_shared<TransparentShapeDecorator>(greenCircle, static_cast<uint8_t>(50)) 
};
std::cout << greenTransparentCircle->draw() << std::endl;
```

*Ausgabe*:

```
A circle of radius 15.000000 has color green has 19.6078% transparency
```

---

#### &bdquo;Real-World&rdquo; Beispiel zum Zweiten: Statisches Dekorieren mit Templates

[Quellcode &bdquo;Statische Shapes&rdquo;](../StaticShapes.cpp)

---

Das &bdquo;Real-World&rdquo;-Beispiel liegt in einer zweiten, alternativen Version vor.
Wenngleich es dem Charakter des *Decorator Patterns* etwas widerspricht, kann man
das Entwurfsmuster auch mit Template Klassen umsetzen: 
Auf diese Weise muss man zwar die Dekoration zur �bersetzungszeit festlegen,
mit Hilfe der Templates bewahrt man sich aber doch eine gewisse Flexibilit�t!

---

## Literaturhinweise

Die Anregungen zu den Beispielen findet man unter

[refactoring.guru](https://refactoring.guru/design-patterns/decorator/cpp/example#example-0)<br>(abgerufen am 23.06.2020).

und 

[Dmitri Nesteruk &bdquo;Design Patterns in Modern C++&rdquo;](https://github.com/Apress/design-patterns-in-modern-cpp)<br>(abgerufen am 14.05.2020).

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
