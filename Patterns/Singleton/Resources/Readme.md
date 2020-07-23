# Singleton Pattern

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Singleton Pattern* ist ein Entwurfsmuster, mit dem sichergestellt wird,
dass es zu einer Klasse nur eine einzige Instanz gibt.
Immer wenn neue Objekte einer Singleton-Klasse benötigt werden,
wird die zuvor erstellte Einzelinstanz bereitgestellt.

#### Problem:

In einigen Fällen ist es wichtig, zu einer konkreten Klasse maximal nur eine Instanz zu haben.
Zum Beispiel dann wenn man nur einen einzigen globalen Zugriffspunkt
auf eine begrenzte Ressource benötigt. 

Würde man eine derartige globale Variable erstellen, die kopiert wird,
würde dies zu mehreren Zugriffspunkten führen und damit zu Dateninkonsistenzen führen.

*Beispiele*:
  * Stream Objekte von C++: `std::cout`, `std::cin` und `std::cerr`.
  * `HttpContext`-Klasse (Java, C# und andere).
 
Ein weiteres Beispiel für Singletons sind Klassen wie zum Beispiel `Color`.
Würde man - zum Beispiel bei jeder Notwendigkeit im Gebrauch einer Farbe wie zum Beispiel *rot* -
ein entsprechendes `Color`-Objekt erzeugen, würde man die Speicherplatzanforderungen
dieser Anwendung nicht mehr in den Griff bekommen. 

Aus diesem Grund gibt es in den entsprechenden Frameworks (JSEE, .NET) für diesen
Anwendungsfall zugeschnittene (leicht
modifizierte `getSingleton`) Methoden, die für jeweils eine Farbe immer dasselbe Objekt
zurückliefern:

```c#
// C# / .NET Framework
public static Color FromArgb (byte a, byte r, byte g, byte b);
```

Natürlich setzt dies voraus, dass die Klasse Color in derartigen Anwendungsfällen
*immutable*, also unveränderbar ist. Andernfalls könnte zur Laufzeit aus einer
roten eine blaue Farbe werden, was so sicherlich nicht erwünscht ist.


#### Lösung:

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Singleton Patterns*.
Es besteht nur aus einer einzigen Klasse:

  * **Singleton**: Dieser Klasse besitzt eine statische Methode `getSingleton`,
    die pro Aufruf eine einzelne Instanz zurückgibt (Referenz, Zeiger),
    die in einer privaten Variablen residiert.

<img src="dp_singleton_pattern.png" width="300">

Abbildung 1: Schematische Darstellung des *Singleton Patterns*.

#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/singleton/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Singleton)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

## Literaturhinweise

*Hinweise*:

TO BE DONE:

Ein guter Aufsatz, wie shared_ptr, weak_ptr und Singletons zusammenarbeiten !!!

http://btorpey.github.io/blog/2014/02/12/shared-singletons/


---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
