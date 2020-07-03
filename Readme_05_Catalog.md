# Katalog der Entwurfsmuster

Historisch gesehen wurde eine erste Aufstellung für Software Entwurfsmuster
von den vier Autoren Erich Gamma, Richard Helm, Ralph Johnson und John Vlissides im Jahre 1994
in einem Buch mit dem Titel "Design Patterns - Elemente wiederverwendbarer objektorientierter Software" gegeben.

Diese Autoren, zusammen auch als "*Gang of Four*" ("*GOF*") bekannt,
nehmen hier eine Kategorisierung der von ihnen beschriebenen Entwurfsmuster
in die drei Kategorien Erzeugungs-, Struktur- und Verhaltensmuster
(*Creational*, *Structural* und *Behavioral Design Patterns*) vor. Eine Aufstellung 
der einzelnen Entwurfsmuster dieser Kategorien finden Sie nachstehend in Abbildung 1 vor:

<img src="Resources/dp_overview.png" width="700">

Abbildung 1: Software Entwurfsmuster nach Erich Gamma, Richard Helm, Ralph Johnson und John Vlissides ("*GoF*").

#### Entwurfsmuster nach Gamma, Helm, Johnson und Vlissides

##### Erzeugungssmuster

In der Softwareentwicklung sind Erstellungsmuster (so genannte *Creational Patter*) Entwurfsmuster,
die sich mit Objekterstellungsmechanismen befassen und in Situationen verwendet werden,
in denen die klassischen Formen der Objekterzeugung zu Entwurfsproblemen führen
oder die Komplexität des Codes erhöhen.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Factory Method](FactoryMethod/Resources/Readme.md) | Das **Factory Method** Entwurfsmuster dient der Entkopplung des Clients von der konkreten Instanziierung einer Klasse. Das erstellte Objekt kann elegant ausgetauscht werden.. |
| [Abstract Factory](AbstractFactory/Resources/Readme.md) | Das **Abstract Factory** Design Pattern dient der Definition einer zusammenhängenden Familie aus Produkten. Die Familien können elegant ausgetauscht werden. |
| [Builder](Builder/Resources/Readme.md) | Ermöglicht schrittweises Erstellen komplexer Objekte. |
| [Prototype](Prototype/Resources/Readme.md) | Erstellen von Kopien vorhandener Objekte, ohne den Code von diesen Klassen abhängig zu machen. |
| [Singleton](Singleton/Resources/Readme.md) | Das **Singleton** Entwurfsmuster sorgt dafür, dass es von einer Klasse nur eine einzige Instanz gibt und diese global zugänglich ist. |

Tabelle 1. Erzeugungsmuster (*Creational Design Patterns*).

##### Strukturmuster

Strukturmuster beschreiben, wie sich Objekte und Klassen zu größeren Strukturen zusammensetzen lassen,
ohne dabei einen Verlust an Flexibilität und Effizient einzugehen.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Adapter](AdapterPattern/Resources/Readme.md) | Ermöglicht die Interaktion von Objekten mit inkompatiblen Schnittstellen. |
| [Bridge](Bridge/Resources/Readme.md) | Aufteilung einer größeren Klasse oder einer Reihe eng verwandter Klassen in zwei separate Hierarchien - Abstraktion und Implementierung. |
| [Composite Pattern](CompositePattern/Resources/Readme.md) | Das **Composite** Entwurfsmuster ermöglicht es, eine verschachtelte (Baum)Struktur einheitlich zu behandeln, unabhängig davon, ob es sich um ein atomares Element oder um ein Behälter für weitere Elemente handelt. Der Client kann elegant mit der Struktur arbeiten. |
| [Decorator](DecoratorPattern/Resources/Readme.md) | Hinzufügen neuen Verhaltens zu Objekten, indem diese Objekte in speziellen Hüllen-Objekten platziert werden, die dieses Verhalten besitzen. |
| Facade | Bereitstellung einer vereinfachten Schnittstelle zu einer Bibliothek, einem Framework oder einer Menge von Objekten. |
| [Flyweight](Flyweight/Resources/Readme.md) | Ermöglicht es, Objekte ressourcenschonended anzulegen, indem diese gemeinsame Zustandsdaten zwischen mehreren Objekten teilen, anstatt derartige Zustandsdaten in jedem Objekt zu duplizieren. |
| [Proxy](Proxy/Resources/Readme.md) | Bereitstellung eines Platzhalters (Stellvertreters) für ein anderes Objekt. Das Proxy-Objekt steuert den Zugriff auf das ursprüngliche Objekt. Vor oder nach der Ausführung der eigentlichen Anforderung am ursprünglichen Objekt lassen sich zusätzliche Aktionen ergänzen. |

Tabelle 2. Strukturmuster (*Structural Design Patterns*).

##### Verhaltensmuster

Verhaltensentwurfsmuster betrachten Algorithmen und der Aufteilung von Verantwortlichkeiten zwischen Objekten.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Chain of Responsibility](ChainOfResponsibility/Resources/Readme.md) | Ermöglicht das Weiterleiten von Anforderungen entlang einer Kette von Handlern. Nach Erhalt einer Anforderung entscheidet jeder Handler, die Anforderung entweder zu verarbeiten oder an den nächsten Handler in der Kette weiterzuleiten. |
| [Command Pattern](CommandPattern/Resources/Readme.md) | Das **Command** Entwurfsmuster ermöglicht die Modularisierung von Befehlen und Aufrufen. Auf elegante Weise können Befehle rückgängig gemacht, protokolliert oder in einer Warteschlange gelegt werden. |
| Interpreter | Das **Interpreter** Entwurfsmuster definiert eine Repräsentation für die Grammatik einer Sprache und die Möglichkeit, Sätze dieser Sprache zu interpretieren. |
| [Iterator](IteratorPattern/Resources/Readme.md) | Ermöglicht das Traversieren (Durchlaufen) von Elementen einer listenartigen Datenstruktur, ohne die zugrunde liegende Darstellung (Liste, Array,  Stapel, Baum usw.) bekannt zu machen. |
| Mediator | Das **Mediator** Muster dient zum Steuern des kooperativen Verhaltens von Objekten, wobei Objekte nicht direkt kooperieren, sondern über einen Vermittler. |
| [Memento](Memento/Resources/Readme.md) | Das **Memento** Entwurfsmuster dient der Erfassung und Spaicherung des internen Zustands eines Objektes. Hiermit kann man den vorherigen Status eines Objekts speichern und wiederherstellen, ohne Details der Implementierung preisgeben zu müssen. |
| [Observer](Observer/Resources/Readme.md) | Das **Observer** Entwurfsmuster ist für Situation geeignet, in denen ein oder mehrere Objekte benachrichtigt werden müssen, sobald sich der Zustand eines bestimmten Objekts ändert. |
| [State](StatePattern/Resources/Readme.md) | 	Das **State** Entwurfsmuster ermöglicht die elegante Modellierung von zustandsabhängigen Verhalten eines Objekts. Je nach internen Zustand ändert sich das Verhalten des Objekts, es scheint, als hätte das Objekt seine Klasse geändert. |
| [Strategy Pattern](StrategyPattern/Resources/Readme.md) | Beschreibt eine Familie von Algorithmen, kapselt jeden einzelnen und macht sie austauschbar. Das Strategiemuster ermöglicht es, den Algorithmus unabhängig von ihn nutzenden Klienten zu variieren. |
| [Template Method](TemplatePattern/Resources/Readme.md) | Definiert das Grundgerüst eines Algorithmus in einer Oberklasse, lässt Unterklassen bestimmte Schritte des Algorithmus überschreiben, ohne dabei Änderungen an der prinzipiellen Algorithmusstruktur zu gestatten. |
| Visitor | Befasst sich mit der Trennung von Algorithmen von den Objekten, mit denen sie arbeiten. |

Tabelle 3. Verhaltensmuster (*Behavioral Design Patterns*).

#### Weitere Entwurfsmuster

Neben diesen klassischen Entwurfsmustern finden sich in verschiendenen Publikationen weiterere
Gruppierungen von Entwurfsmustern. In Büchern über "Modern C++" stößt man häufig auf folgende Entwurfsmuster:

| Muster | Kurzbeschreibung |
|:-------------- |----|
| RAII (Resource Acquisition Is Initialization) | Objektlebenszeit und Ressourcenverwaltung |
| [Opaque Pointer / Pimpl](OpaquePointer/Resources/Readme.md)  | *Pointer to implementation* |
| [Null Object](NullObject/Resources/Readme.md) | Null Objekt |
| SFINAE | *Substitution failure is not an error* |
| CRTP | *Curiously recurring template pattern* |

Tabelle 4: Weitere Software (*Modern C++*)

In einem weiteren Buch [Robert Nystrom](https://gameprogrammingpatterns.com/),
aktuell bei der Fa. Google in der Entwicklung der Programmiersprache Dart beschäftigt,
finden sich weitere interessante Entwurfsmuster:

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Double Buffer | TBD |
| Game Loop | TBD |
| Update Method | TBD |

Tabelle 5. Sequencing Patterns

sowie

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Bytecode | TBD |
| Subclass Sandbox | TBD |
| Type Object | TBD |

Tabelle 6. Behavioral Patterns

und

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Component | TBD |
| Event Queue | TBD |
| Service Locator | TBD |

Tabelle 7. Decoupling Patterns

und

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Data Locality | TBD |
| Dirty Flag | TBD |
| Object Pool | TBD |

Tabelle 8. Optimization Patterns

Für den Entwurf von Oberflächen gibt es im Prinzip drei "Klassiker"

| Muster | Kurzbeschreibung |
|:-------------- |----|
| MVC | Model-View-Controller |
| MVP | Model-View-Presenter |
| MVVM | Model View View-Model |

Tabelle 9. Entwurfsmuster für Oberflächen

---

[Zurück](Readme.md)

---
