# Singleton Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_singleton_pattern_intro.png" width="500" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Singleton Pattern* ist ein Entwurfsmuster, mit dem sichergestellt wird,
dass es zu einer Klasse nur eine einzige Instanz gibt.
Immer wenn neue Objekte einer Singleton-Klasse benötigt werden,
wird die zuvor erstellte Einzelinstanz bereitgestellt.

#### Problem:

In einigen Fällen ist es wichtig, zu einer konkreten Klasse maximal nur eine Instanz zu haben.
Zum Beispiel dann, wenn man nur einen einzigen globalen Zugriffspunkt
auf eine begrenzte Ressource benötigt. 

Würde man eine derartige globale Variable erstellen, die kopiert wird,
würde dies zu mehreren Zugriffspunkten führen und damit zu möglichen Dateninkonsistenzen.

*Beispiele*:
  * Stream Objekte von C++: `std::cout`, `std::cin` und `std::cerr`.
  * `HttpContext`-Klasse (Java, C# und andere).
 
Ein weiteres Beispiel für Singletons sind Klassen wie zum Beispiel `Color`.
Würde man &ndash; beispielsweise bei jeder Notwendigkeit im Gebrauch einer Farbe wie *rot* &ndash;
ein entsprechendes `Color`-Objekt erzeugen, würde man die Speicherplatzanforderungen
dieser Anwendung nicht mehr in den Griff bekommen. 

Aus diesem Grund gibt es in den entsprechenden Frameworks (J2SE, .NET) für diesen
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

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Singleton Patterns*.
Es besteht nur aus einer einzigen Klasse:

  * **Singleton**: Dieser Klasse besitzt eine statische Methode `getSingleton`,
    die pro Aufruf eine einzelne Instanz zurückgibt (Referenz, Zeiger),
    die in einer privaten Variablen residiert.

<img src="dp_singleton_pattern.svg" width="300">

*Abbildung* 1: Schematische Darstellung des *Singleton Patterns*.

#### Double-Checked Locking / Doppelt überprüfte Sperrung:

Eine *doppelt überprüfte Sperrung* (englisch *double-checked locking*) ist ein Muster in der Softwareentwicklung,
welches dazu dient, den Zugriff auf ein gemeinsames Objekt durch mehrere gleichzeitig laufende Threads zu regeln.

Die klassische Realisierung der `getInstance`-Methode weist einen kleinen Schönheitsfehler auf:

```cpp
Singleton* Singleton::getInstance()
{
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        if (m_instance == nullptr) {
            m_instance = new Singleton();
        }
    }

    return m_instance;
}
```

Das Erzeugen des (einzigen) Objekts erfolgt thread-sicher, so weit, so gut. Der Schönheitsfehler dabei ist,
dass der Zugriff auf das Objekt (präziser: der lesende Zugriff zum Erlangen einer Zeigervariablen, die auf das Objekt zeigt)
über dieselbe Methode (!) sehr oft geschehen kann und damit auch
die lesenden Zugriffe auf das Singleton-Objekt thread-sicher ausgeführt werden, was überflüssig ist und
unnötige Rechenzeit beansprucht.

Die `getInstance`-Methode sollte deshalb mit einer so genannten *doppelt überprüften Sperrung*
realisiert werden. Hier wird nur das Erzeugen des Singleton-Objekts thread-sicher ausgeführt,
der (lesende) Zugriff auf die Zeigervariable des Objekts wird ohne Sperre durchgeführt:

```cpp
Singleton* Singleton::getInstance()
{
    if (m_instance == nullptr)
    {
        std::scoped_lock<std::mutex> lock{ m_mutex };
        if (m_instance == nullptr)  // <= NOTE: double-check of m_instance being nullptr
        {
            m_instance = new Singleton(value);
        }
    }

    return m_instance;
}
```


#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Mit *Double-Checked Locking*

---

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/singleton/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Singleton)

vor.

## Weiterarbeit:

Ein seht guter Aufsatz, wie `std::shared_ptr`-, `std::weak_ptr`- und Singleton-Objekte zusammenarbeiten,
kann unter

[Shared Singleton's](http://btorpey.github.io/blog/2014/02/12/shared-singletons/)

nachgelesen werden.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
