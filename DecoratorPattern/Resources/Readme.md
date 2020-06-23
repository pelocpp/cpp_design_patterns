# Decorator Pattern

## Wesentliche Merkmale

##### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Decorator Pattern* ist ein strukturelles Entwurfsmuster, das die Funktionalität eines Objekts erweitert,
indem es dieses mit einer oder mehreren Dekorationsklassen "umhüllt", oder gewissermaßen dekoriert.
*Decorator* Klassen können vorhandene Elemente ändern und zur Laufzeit neue Methoden und Eigenschaften hinzufügen.


##### Hinweis:

Das Spezialisieren (Vererbung) einer Klasse ist typischerweise das Erste, was einem einfällt,
wenn man das Verhalten eines Objekts ändern (erweitern) möchte.
Die Vererbung weist jedoch einige schwerwiegende Einschränkungen auf, die es zu beachten gilt:

  * Die Vererbung ist ein statisches Konzept, also etwas, was zur Übersetzungszeit festgelegt sein muss.
    Zur Laufzeit lässt sich das Verhalten eines bestimmten Objekts nicht ändern.
    Ferner kann man nur ein ganzes Objekt durch ein anderes Objekt ersetzen, das aus einer anderen Unterklasse erstellt wurde.
    Das *Decorator Pattern* zielt auf das Ändern von Verhaltensweisen bestimmter Methoden ab.
  * Unterklassen können nur eine übergeordnete Klasse haben. In den meisten Sprachen lässt das Prinzip der Vererbung nicht zu,
    dass eine Klasse das Verhalten mehrerer Klassen gleichzeitig erbt (Prinzip der Mehrfachvererbung, in C++ allerdings möglich)

Eine Möglichkeit, diese Einschränkungen zu überwinden, ist die Verwendung von
*Aggregation* oder *Komposition* anstelle von Vererbung.
Beide Alternativen funktionieren fast gleich: Ein Objekt hat einen Verweis (Referenz, Zeiger) 
auf ein anderes und *delegiert* ihm dadurch Tätigkeiten.
Bei der Vererbung kann das Objekt diese Arbeit *selbst* ausführen,
es *erbt* das Verhalten von seiner Oberklasse.

Mit diesem Ansatz (Gebrauch eines Verweises) können Sie das verknüpfte "Hilfs"-Objekt leicht durch ein
anderes ersetzen und so das Verhalten des Containers zur Laufzeit ändern.
Ein Objekt kann das Verhalten mehrerer Klassen verwenden, indem es Verweise auf mehrere Objekte verwaltet und an diese alle Arten von Arbeit delegieren.

<img src="dp_decorator_01.png" width="500">

Abbildung 1: Vererbung versus Aggregation.

#### Problem:

Das Objekt, das Sie verwenden möchten, führt die grundlegenden Funktionen aus, die Sie benötigen.
Möglicherweise müssen Sie dem Objekt jedoch noch einige zusätzliche Funktionalitäten hinzufügen,
die vor oder nach der Basisfunktionalität des betrachteten Objekts auszuführen sind.

#### Lösung:

*Wrapper* oder Hülle ist der alternative Kurzname für das Decorator-Pattern,
der die Hauptidee des Musters klar zum Ausdruck bringt. Ein "Wrapper" ist ein Objekt,
das mit einem "Ziel"-Objekt verknüpft werden kann. Das Wrapper-Objekt enthält die gleichen Methoden
wie das Ziel und delegiert alle eingehenden Requests an es.
Der Wrapper kann das Verhalten jedoch ändern,
indem er entweder vor oder nach dem Weiterleiten der Anforderung an das Ziel
zusätzliches Verhalten hinzufügt.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Decorator Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Component**: Abstrakte Basisklasse für alle konkreten Komponenten und Decorator-Klassen.
    Diese Klasse definiert diejenigen Klassenelemente, die standardmäßig von diesen Klassentypen implementiert werden müssen.
  * **ConcreteComponent**: Diese Klasse erbt von der Klasse `Component`. Es kann diese Klasse mehrfach geben. Es damit jeweils einen Objekttyp definiert,
    der von einer Decorator-Klasse umhüllt wird.
  * **DecoratorBase**: Stellt die abstrakte Basisklasse für alle Decorator-Klassen dar. Es wird ein Konstruktor hinzugefügt,
    der ein `Component-Objekt` als Parameter akzeptiert. Das übergebene Objekt ist die Komponente, die umhüllt wird.
    Da das umhüllte Objekt von `Component` erben muss, kann es sich um ein `ConcreteComponent`-Objekt
    oder ein anderes Decorator-Objekt handeln. Auf diese Weise können mehrere Decorator-Objekte auf ein einzelnes Objekt angewendet werden.
  * **ConcreteDecorator**: Diese Klasse repräsentiert ein konkretes Decorator-Objekt für eine Komponente.
    Es kann einige zusätzliche Methoden enthalten, die die Funktionalität der Komponente erweitern.
    Die `operation`-Methoden können auf zwei Arten verwendet werden:
    Sie können unverändert bleiben und in diesem Fall wird die Basisklassenmethode der Komponente aufgerufen
    oder die `operation`-Methode kann geändert werden oder vollständig durch eine neue Implementierung ersetzt werden.

<img src="dp_decorator_02.png" width="650">

Abbildung 2: Schematische Darstellung des *Decorator* Patterns.


###### Hinweis:

Während ein Dekorateur seine Funktionalität vor oder nach Weiterleiten der Anforderung an das Objekt,
was es dekoriert, hinzufügen kann, sollte die Kette der Instanziierung
immer mit dem `ConcreteComponent`-Objekt enden.

#### Implementierung:

Erstellen Sie eine abstrakte Klasse, die sowohl die ursprüngliche Klasse darstellt
als auch die neuen Methoden besitzt, die der Klasse hinzugefügt werden sollen.
Platzieren Sie in den Dekoratoren die neuen Methoden-Anrufe
vor oder nach den Anrufen an das eingehüllte Objekt, um die richtige Reihenfolge zu erhalten.

#### Pro / Kontra:

###### Pros:

  * Das Verhalten eines Objekts kann erweitert werden, ohne eine neue Unterklasse erstellen zu müssen.
  * Einem Objekt können zur Laufzeit Verantwortlichkeiten hinzugefügt oder daraus entfernt werden.
  * Es können mehrere Verhaltensweisen kombiniert werden, indem man ein Objekt in mehrere Dekoratoren einhüllt.
  * *Single Responsibility Principle*: Eine monolithische Klasse,
    die viele mögliche Verhaltensvarianten implementiert, kann so in mehrere kleinere Klassen unterteilt werden.

###### Kontras:

  * Es ist schwierig, einen bestimmten Wrapper vom Wrapper-Stapel zu entfernen.
  * Es ist schwierig, einen Dekorateur so zu implementieren, dass sein Verhalten nicht von der Reihenfolge im Dekorationsstapel abhängt.
  * Der anfängliche Konfigurationscode von Ebenen (Hüllen) sieht möglicherweise nicht sehr gut aus.

#### Beispiel:

Siehe Verzeichnis *ConceptualExample*.


## Anwendungsbeispiel:

  * TBD


## Literaturhinweise

*Hinweise*:

Die Anregungen zu den Beispielen findet man unter

[refactoring.guru](https://refactoring.guru/design-patterns/decorator/cpp/example#example-0)<br>(abgerufen am 23.06.2020).

und 

[Dmitri Nesteruk "Design Patterns in Modern C++](https://github.com/Apress/design-patterns-in-modern-cpp)<br>(abgerufen am 14.05.2020).

---

[Zurück](../../Readme.md)

---

## Weiterarbeit:

a) Beispiel Dmitri Nesteruk !!!

