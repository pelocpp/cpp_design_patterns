# Katalog der Entwurfsmuster

[Zur�ck](../Readme.md)

---

Historisch gesehen wurde eine erste Aufstellung f�r Software Entwurfsmuster
von den vier Autoren Erich Gamma, Richard Helm, Ralph Johnson und John Vlissides im Jahre 1994
in einem Buch mit dem Titel "Design Patterns - Elemente wiederverwendbarer objektorientierter Software" gegeben.

Diese Autoren, zusammen auch als "*Gang of Four*" ("*GOF*") bekannt,
nehmen hier eine Kategorisierung der von ihnen beschriebenen Entwurfsmuster
in die drei Kategorien Erzeugungs-, Struktur- und Verhaltensmuster
(*Creational*, *Structural* und *Behavioral Design Patterns*) vor. Eine Aufstellung 
der einzelnen Entwurfsmuster dieser Kategorien finden Sie nachstehend in *Abbildung* 1 vor:

<img src="dp_overview.svg" width="700">

*Abbildung* 1: Software Entwurfsmuster nach Erich Gamma, Richard Helm, Ralph Johnson und John Vlissides ("*GoF*").

Speziell im Umfeld von *Modern C++* haben sich folgende Entwurfsmuster etabliert (*Abbildung* 2):

<img src="dp_overview_modern_cpp.svg" width="370">

*Abbildung* 2: *Modern C++* Entwurfsmuster.

Die drei Klassiker f�r Entwurfsmuster in Anwendungen mit Oberfl�chen sind in *Abbildung* 3 
zusammengestellt:

<img src="dp_overview_ui.svg" width="230">

*Abbildung* 3: Entwurfsmuster f�r die Gestaltung von Oberfl�chen.


#### Entwurfsmuster nach Gamma, Helm, Johnson und Vlissides

##### Erzeugungsmuster

In der Softwareentwicklung sind Erstellungsmuster (so genannte *Creational Pattern*) Entwurfsmuster,
die sich mit Objekterstellungsmechanismen befassen und in Situationen verwendet werden,
in denen die klassischen Formen der Objekterzeugung zu Entwurfsproblemen f�hren
oder die Komplexit�t des Codes erh�hen.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Simple Factory](../Patterns/SimpleFactory/Resources/Readme.md) | Ein **Simple Factory** Objekt wird typischerweise vom Client �ber eine statische Methode aufgerufen. |
| [Factory Method](../Patterns/FactoryMethod/Resources/Readme.md) | Das **Factory Method** Entwurfsmuster dient dem Zweck, alle Schritte zur Erzeugung eines Objekts kontrollieren zu wollen. Die Klasse des erstellten Objekts kann elegant ausgetauscht werden. |
| [Abstract Factory](../Patterns/AbstractFactory/Resources/Readme.md) | Das **Abstract Factory** Design Pattern dient der Definition einer zusammenh�ngenden Familie aus Produkten. Die Familien k�nnen elegant ausgetauscht werden. |
| [Builder](../Patterns/Builder/Resources/Readme.md) | Erm�glicht schrittweises Erstellen komplexer Objekte. |
| [Prototype](../Patterns/Prototype/Resources/Readme.md) | Prototype Pattern &ndash; auch als *Virtueller Konstruktor* bezeichnet. |
| [Singleton](../Patterns/Singleton/Resources/Readme.md) | Das **Singleton** Entwurfsmuster sorgt daf�r, dass es von einer Klasse nur eine einzige Instanz gibt und diese global zug�nglich ist. |

*Tabelle* 1: Erzeugungsmuster (*Creational Design Pattern*).

##### Strukturmuster

Strukturmuster beschreiben, wie sich Objekte und Klassen zu gr��eren Strukturen zusammensetzen lassen,
ohne dabei einen Verlust an Flexibilit�t und Effizienz einzugehen.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Adapter](../Patterns/AdapterPattern/Resources/Readme.md) | Erm�glicht die Interaktion von Objekten mit inkompatiblen Schnittstellen. |
| [Bridge](../Patterns/Bridge/Resources/Readme.md) | Aufteilung einer gr��eren Klasse oder einer Reihe eng verwandter Klassen in zwei separate Hierarchien - Abstraktion und Implementierung. |
| [Composite Pattern](../Patterns/CompositePattern/Resources/Readme.md) | Erm�glicht es, einzelne Objekte und Gruppen von Objekten einheitlich zu behandeln. |
| [Decorator](../Patterns/DecoratorPattern/Resources/Readme.md) | Hinzuf�gen neuen Verhaltens zu Objekten, indem diese Objekte in speziellen H�llen-Objekten platziert werden, die dieses Verhalten besitzen. |
| [Facade](../Patterns/Facade/Resources/Readme.md) | Bereitstellung einer vereinfachten Schnittstelle zu einer Bibliothek, einem Framework oder einer Menge von Objekten. |
| [Flyweight](../Patterns/Flyweight/Resources/Readme.md) | Erm�glicht es, Objekte ressourcenschonend anzulegen, indem diese gemeinsame Zustandsdaten zwischen mehreren Objekten teilen, anstatt derartige Zustandsdaten in jedem Objekt zu duplizieren. |
| [Proxy](../Patterns/Proxy/Resources/Readme.md) | Bereitstellung eines Platzhalters (Stellvertreters) f�r ein anderes Objekt. |

*Tabelle* 2: Strukturmuster (*Structural Design Pattern*).


##### Verhaltensmuster

Verhaltensentwurfsmuster betrachten Algorithmen und der Aufteilung von Verantwortlichkeiten zwischen Objekten.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Chain of Responsibility](../Patterns/ChainOfResponsibility/Resources/Readme.md) | Erm�glicht das Weiterleiten von Anforderungen entlang einer Kette von Handlern. |
| [Command Pattern](../Patterns/CommandPattern/Resources/Readme.md) | Das **Command** Entwurfsmuster erm�glicht die Modularisierung von Befehlen und Aufrufen. Auf elegante Weise k�nnen Befehle r�ckg�ngig gemacht, protokolliert oder in einer Warteschlange gelegt werden. |
| [Interpreter](../Patterns/InterpreterPattern/Resources/Readme.md) | Das **Interpreter** Entwurfsmuster definiert eine Repr�sentation f�r die Grammatik einer Sprache und die M�glichkeit, S�tze dieser Sprache zu interpretieren. |
| [Iterator](../Patterns/IteratorPattern/Resources/Readme.md) | Erm�glicht das Traversieren (Durchlaufen) von Elementen einer listenartigen Datenstruktur, ohne die zugrunde liegende Darstellung (Liste, Array,  Stapel, Baum usw.) zu kennen. |
| [Mediator](../Patterns/Mediator/Resources/Readme.md) | Das **Mediator** Muster dient zum Steuern des kooperativen Verhaltens von Objekten, wobei Objekte nicht direkt kooperieren, sondern �ber einen Vermittler. |
| [Memento](../Patterns/Memento/Resources/Readme.md) | Das **Memento** Entwurfsmuster dient der Erfassung und Speicherung des internen Zustands eines Objektes. Hiermit kann man den vorherigen Status eines Objekts speichern und wiederherstellen, ohne Details der Implementierung preisgeben zu m�ssen. |
| [Observer](../Patterns/Observer/Resources/Readme.md) | Das **Observer** Entwurfsmuster ist f�r Situation geeignet, in denen ein oder mehrere Objekte benachrichtigt werden m�ssen, sobald sich der Zustand eines bestimmten Objekts �ndert. |
| [State](../Patterns/StatePattern/Resources/Readme.md) | 	Das **State** Entwurfsmuster erm�glicht die elegante Modellierung vom zustandsabh�ngigen Verhalten eines Objekts. Je nach internem Zustand �ndert sich das Verhalten des Objekts, es scheint, als h�tte das Objekt seine Klasse ge�ndert. |
| [Strategy Pattern](../Patterns/StrategyPattern/Resources/Readme.md) | Beschreibt eine Familie von Algorithmen, kapselt jeden einzelnen und macht sie austauschbar. Das Strategiemuster erm�glicht es, den Algorithmus unabh�ngig von ihn nutzenden Klienten zu variieren. |
| [Template Method](../Patterns/TemplatePattern/Resources/Readme.md) | Definiert das Grundger�st eines Algorithmus in einer Oberklasse, l�sst Unterklassen bestimmte Schritte des Algorithmus �berschreiben, ohne dabei �nderungen an der prinzipiellen Algorithmusstruktur zu gestatten. |
| [Visitor Method](../Patterns/Visitor/Resources/Readme.md) | Befasst sich mit der Trennung von Algorithmen von den Objekten, mit denen sie arbeiten. |

*Tabelle* 3: Verhaltensmuster (*Behavioral Design Pattern*).

#### Weitere Entwurfsmuster

Neben diesen klassischen Entwurfsmustern finden sich in verschiedenen Publikationen weitere
Gruppierungen von Entwurfsmustern. In B�chern �ber "Modern C++" st��t man h�ufig auf folgende Entwurfsmuster:

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [RAII](../Patterns/RAII_Idiom/Resources/Readme.md) | *Resource Acquisition Is Initialization* |
| [Opaque Pointer / Pimpl](../Patterns/Pimpl/Resources/Readme.md) | *Pointer to implementation* |
| [Null Object](../Patterns/NullObject/Resources/Readme.md) | Null Objekt |
| [Intercepting Filter Pattern](../Patterns/InterceptingFilterPattern/Resources/Readme.md) | *Intercepting Filter Pattern* |
| [Type Erasure](../Patterns/TypeErasure/Resources/Readme.md) | *Type Erasure* |
| [Policy-Based Design](../Patterns/PolicyBasedDesign/Resources/Readme.md) | *Policy-Based Design* |
| SFINAE | *Substitution failure is not an error* |
| CRTP | *Curiously recurring template pattern* |

*Tabelle* 4: Weitere Softwaremuster (*Modern C++*)

In der Softwareentwicklung beschreiben *Concurrency Pattern* jene Arten von Entwurfsmustern,
die sich mit dem Multithreading-Programmierparadigma befassen:

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Active Object | *Active Object* Entwurfsmuster |
| Monitor Object | *Monitor Object* Entwurfsmuster |

*Tabelle* 5: *Concurrency Pattern*

F�r den Entwurf von Oberfl�chen gibt es im Prinzip drei "Klassiker"

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [MVC](../Patterns/MVC/Resources/Readme.md) | Model-View-Controller |
| MVP | Model-View-Presenter |
| MVVM | Model View View-Model |

*Tabelle* 6: Entwurfsmuster f�r Oberfl�chen

In einem weiteren Buch von [Robert Nystrom](https://gameprogrammingpatterns.com/),
aktuell bei der Fa. Google in der Entwicklung der Programmiersprache *Dart* besch�ftigt,
finden sich weitere interessante Entwurfsmuster vor:

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Double Buffer | Vermeintliche Ausf�hrung einer Reihe von aufeinanderfolgenden (sequentiellen) Vorg�ngen (quasi) unverz�glich oder (quasi) gleichzeitig. |
| Game Loop | Entkopplung des Spieleverlaufs (Ablauf der Anwendung) von Benutzereingaben und Prozessorgeschwindigkeit. |
| Update Method | Simulation des Ansto�es einer Aktivit�t bei einer Anzahl unabh�ngiger Objekte (Ausf�hrung eines *Frames* in regelm��igen Abst�nden). |

*Tabelle* 7: Sequencing Patterns
    
sowie

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Bytecode | Schaffung von Flexibilit�t f�r die Daten, indem Sie sie als Anweisungen f�r eine virtuelle Maschine codieren. |
| Subclass Sandbox | Definieren Sie das Verhalten in einer Unterklasse mithilfe einer Reihe von Operationen, die von der Basisklasse bereitgestellt werden. |
| Type Object | Erm�glicht die flexible Erstellung neuer *Klassen*, indem Sie eine einzelne Klasse erstellen, von der jede Instanz einen anderen Objekttyp darstellt. |

*Tabelle* 8: Behavioral Patterns

und

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Component | Erm�glicht einer einzelnen Entit�t, mehrere Dom�nen zu umfassen, ohne die Dom�nen miteinander zu koppeln. |
| Event Queue | Entkoppelt die Verarbeitung einer Nachricht oder ein Ereignisses vom Zeitpunkt, zu dem sie gesendet (bzw. empfangen) wird. |
| Service Locator | Stellt einen globalen Zugriffspunkt auf einen Dienst bereit, ohne Benutzer an eine konkrete Klasse zu koppeln, die den Service implementiert. |

*Tabelle* 9: Decoupling Patterns

und

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Data Locality | Beschleunigen Sie den Speicherzugriff, indem Sie Daten so anordnen, dass das CPU-Caching genutzt wird. |
| Dirty Flag | Vermeiden Sie unn�tige Rechenzeit, indem Sie diese verschieben, bis das Ergebnis ben�tigt wird. |
| Object Pool | Verbesserung von Rechenleistung und Speichernutzung, indem Objekte aus einem festen Pool wiederverwendet werden, anstatt sie einzeln anzufordern und freizugeben. |
| Spatial Partition | Effizienter Zugriff auf Objekte, indem diese in einer nach ihren Positionen geordneten Datenstruktur gespeichert werden. |

*Tabelle* 10: Optimization Patterns

---

#### `std::enable_shared_from_this`

Das Thema `std::enable_shared_from_this` wird in einigen Mustern speziell angesprochen:

  * [Mediator](../Patterns/Mediator/Resources/Readme.md)<br/>
  * [Composite Pattern](../Patterns/CompositePattern/Resources/Readme.md)<br/>
  * [State](../Patterns/StatePattern/Resources/Readme.md)<br/>
  * [Observer](../Patterns/Observer/Resources/Readme.md)<br/>
  * [Visitor Method](../Patterns/Visitor/Resources/Readme.md)<br/>

---

[Zur�ck](../Readme.md)

---
