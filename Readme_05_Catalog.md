# Katalog der Entwurfsmuster

Entwurfsmuster lassen sich in die drei Kategorien Erzeugungs-, Struktur- und Verhaltensmuster
(Creational, Structural and Behavioral Design Patterns) untergliedern. Eine Aufstellung 
der einzelnen Entwurfsmuster dieser Kategorien finden Sie nachstehend vor:

<img src="Resources/dp_overview.png" width="600">

## Erzeugungssmuster

In der Softwareentwicklung sind Erstellungsmuster (so genannten *Creational Patter*) Entwurfsmuster,
die sich mit Objekterstellungsmechanismen befassen und in Situationen verwendet werden,
in denen die klassischen Formen der Objekterzeugung zu Entwurfsproblemen führen
oder die Komplexität des Codes erhöhen kann.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Factory Method](FactoryMethod/Resources/Readme.md) | Bietet eine Schnittstelle zum Erstellen von Objekten in einer Oberklasse, ermöglicht es jedoch den Unterklassen, den Typ der zu erstellenden Objekte zu ändern.. |
| [Abstract Factory](AbstractFactory/Resources/Readme.md) | Erstellung von Familien verwandter Objekte, ohne deren konkrete Klassen anzugeben. |
| [Builder](Builder/Resources/Readme.md) | Ermöglicht das schrittweise Erstellen komplexer Objekte. |
| [Prototype](Prototype/Resources/Readme.md) | Erstellen von Kopien vorhandener Objekte, ohne Ihren Code von ihren Klassen abhängig zu machen. |
| [Singleton](Singleton/Resources/Readme.md) | Hiermit können Sie sicherstellen, dass eine Klasse nur eine Instanz hat, während Sie einen globalen Zugriffspunkt für diese Instanz bereitstellen. |

Tabelle 1. Erzeugungsmuster (Creational Design Patterns).

## Strukturmuster

Structural patterns explain how to assemble objects and classes into larger structures while keeping these structures flexible and efficient.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Adapter](AdapterPattern/Resources/Readme.md) | Allows objects with incompatible interfaces to collaborate. |
| [Bridge](Bridge/Resources/Readme.md) | Lets you split a large class or a set of closely related classes into two separate hierarchies - abstraction and implementation - which can be developed independently of each other. |
| [Composite Pattern](CompositePattern/Resources/Readme.md) | Lets you compose objects into tree structures and then work with these structures as if they were individual objects. |
| [Decorator](DecoratorPattern/Resources/Readme.md) | Lets you attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors. |
| Facade | Provides a simplified interface to a library, a framework, or any other complex set of classes. |
| [Flyweight](Flyweight/Resources/Readme.md) | Lets you fit more objects into the available amount of RAM by sharing common parts of state between multiple objects instead of keeping all of the data in each object. |
| [Proxy](Proxy/Resources/Readme.md) | Lets you provide a substitute or placeholder for another object. A proxy controls access to the original object, allowing you to perform something either before or after the request gets through to the original object. |

Tabelle 2. Strukturmuster (Structural Design Patterns).

## Verhaltensmuster

Behavioral design patterns are concerned with algorithms and the assignment of responsibilities between objects.

| Muster | Kurzbeschreibung |
|:-------------- |----|
| [Chain of Responsibility](ChainOfResponsibility/Resources/Readme.md) | Lets you pass requests along a chain of handlers. Upon receiving a request, each handler decides either to process the request or to pass it to the next handler in the chain. |
| [Command Pattern](CommandPattern/Resources/Readme.md) | Turns a request into a stand-alone object that contains all information about the request. This transformation lets you parameterize methods with different requests, delay or queue a request's execution, and support undoable operations. |
| Interpreter | TBD |
| [Iterator](IteratorPattern/Resources/Readme.md) | Lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.). |
| Mediator | Lets you reduce chaotic dependencies between objects. The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object. |
| [Memento](Memento/Resources/Readme.md) | Lets you save and restore the previous state of an object without revealing the details of its implementation. |
| [Observer](Observer/Resources/Readme.md) | Lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they're observing. |
| State | Lets an object alter its behavior when its internal state changes. It appears as if the object changed its class. |
| [Strategy Pattern](StrategyPattern/Resources/Readme.md) | Lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable. |
| [Template Method](TemplatePattern/Resources/Readme.md) | Defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure. |
| Visitor | Lets you separate algorithms from the objects on which they operate. |

Tabelle 3. Verhaltensmuster (Behavioral Design Patterns).


Neben diesen klassischen Entwurfsmustern finden sich in verschiendenen Publikationen weiterere
Gruppierungen von Entwurfsmustern - so zum Beispiel bei [Robert Nystrom](https://gameprogrammingpatterns.com/),
aktuell bei der Fa. Google in der Entwicklung der Programmiersprache Dart beschäftigt:

| Muster | Kurzbeschreibung |
|:-------------- |----|
| Double Buffer | TBD |
| Game Loop | TBD |
| Update Method | TBD |

Tabelle 4. Sequencing Patterns





| Muster | Kurzbeschreibung |
|:-------------- |----|
| Bytecode | TBD |
| Subclass Sandbox | TBD |
| Type Object | TBD |

Tabelle 5. Behavioral Patterns



| Muster | Kurzbeschreibung |
|:-------------- |----|
| Component | TBD |
| Event Queue | TBD |
| Service Locator | TBD |

Tabelle 6. Decoupling Patterns



| Muster | Kurzbeschreibung |
|:-------------- |----|
| Data Locality | TBD |
| Dirty Flag | TBD |
| Object Pool | TBD |

Tabelle 7. Optimization Patterns


| Muster | Kurzbeschreibung |
|:-------------- |----|
| MVC | Model-View-Controller |
| MVVM | Model View View-Model |

Tabelle 7. Entwurfsmuster für Oberflächen

---

[Zurück](Readme.md)

---
