# Entwurfsmuster im Vergleich

[Zur�ck](../Readme.md)

---

## �berblick

  * [Vergleich Decorator Pattern vs. Proxy Pattern](#link1)
  * [Vergleich Visitor Pattern vs. Composite Pattern](#link2)
  * [Vergleich Strategy Pattern vs. Adapter Pattern](#link3)
  * [Vergleich Strategy Pattern vs. Template Method Pattern](#link4)
  * [Vergleich Observer Pattern vs. Iterator Pattern](#link5)
  * [Vergleich Factory Method Pattern vs. Abstract Factory Pattern](#link6)
  * [Vergleich Bridge Pattern vs. Adapter Pattern](#link7)

---

## Vergleich Decorator Pattern vs. Proxy Pattern <a name="link1"></a>

Ein prinzipieller Unterschied:

Das Decorator Pattern umh�llt eine Methode eines Zielobjekts,
das Proxy Pattern ein ganzes Objekt.

#### Decorator Pattern

  * Umh�llt eine Methode eines Originalobjekts.
  * Diese Methode gilt es aufzurufen.
  * Vor und nach dem Aufruf der Zielmethode kann zus�tzliche Funktionalit�t umgesetzt/erg�nzt werden.
  * Aus einer Reihe von Gr�nden wird diese Funktionalit�t *nicht* am Zielobjekt direkt umgesetzt.
  * *Feature*: Das Zielobjekt kann wiederum ein Dekorator sein: Dekoratoren-Objekte sind schachtelbar (&bdquo;Nested use of decorator objects&rdquo;).
  * Die Reihenfolge der geschachtelten Dekoratoren-Objekte ist beliebig bzw. einstellbar.
  * Die Reihenfolge der Dekoratoren-Objekte ist zur *Laufzeit* einstellbar.

#### Proxy Pattern

  * Umh�llt ein gesamtes Objekt.
  * 1:1 Ersetzung eines Originalobjekts mit entsprechenden Verantwortlichkeiten (Beispiel: Zielmethode wird *nicht* aufgerufen).
  * Kontrolliert/steuert den Zugriff auf ein unterlagertes Objekt.
  * Kontrolliert die Aufrufe von *getter*- und *setter*-Methoden, bevor diese an das Zielobjekt weitergereicht werden.

---

## Vergleich Visitor Pattern vs. Composite Pattern <a name="link2"></a>

Es gibt zun�chst prinzipielle Unterschiede:

  * Das Composite Pattern ist ein Strukturmuster, das hei�t, es dient zum Aufbau einer Datenstruktur.
  * Das Visitor Pattern ist ein Verhaltensmuster, es ist f�r Beziehungen und Verhalten verantwortlich.

#### Visitor Pattern

Wird angewendet, um eine Operation an einer Gruppe �hnlicher Objekte durchzuf�hren.

#### Composite Pattern

Wird angewendet, um einzelne Objekte und Objektgruppen homogen zu behandeln.

Fazit:<br />

Es handelt sich um unterschiedliche Muster, die jedoch h�ufig zusammen verwendet werden:

  * Der Zweck des Composite Patterns besteht darin, dieselbe Operation auf mehrere Elemente anzuwenden, die eine gemeinsame Schnittstelle haben.
  * Der Zweck des Visitor Patterns besteht darin, mehrere Elemente um eine neue Operation zu erweitern, ohne deren Implementierung zu �ndern. Daher sieht man h�ufig:

```cpp
Composite* c = new Composite();
Visitor* v = new ConcreteVisitor();
c->visit(v);
```
---

## Vergleich Strategy Pattern vs. Adapter Pattern <a name="link3"></a>

Das Strategy Pattern w�hlt zur Laufzeit das richtige &bdquo;*Verhalten*&rdquo; aus,
w�hrend das Adapter Pattern inkompatibele Schnittstellen zusammenarbeiten l�sst. 

#### Strategy Pattern

  * Erm�glicht die Definition/Realisierung einer Menge von Algorithmen, die austauschbar sind.
  * W�hlt zur Laufzeit das richtige &bdquo;*Verhalten*&rdquo; (Strategie) aus.

#### Adapter Pattern

  * Erm�glicht die Zusammenarbeit inkompatibler Schnittstellen.
  * �ndert die Schnittstelle eines Objekts.
  * Fungiert als Wrapper zwischen zwei Objekten.
  * F�ngt Aufrufe eines Objekts ab und transformiert sie in ein f�r das zweite Objekt erkennbaren Aufruf samt Konvertierung beteiligter Formate.

---

## Vergleich Strategy Pattern vs. Template Method Pattern <a name="link4"></a>

#### Strategy Pattern

  * Erm�glicht unterschiedliches Verhalten �hnlicher Objekte.
  * Erm�glicht �bersichtlichen Code.
  * Erm�glicht das nahtlose Hinzuf�gen neuen Verhaltens.


#### Template Method Pattern

  * Standardisiert Arbeitsabl�ufe �ber mehrere Implementierungen hinweg.
  * Erm�glicht Variationen in einzelnen Schritten unter Beibehaltung einer Gesamtsequenz.
  * Reduziert Code-Duplikation durch Implementierung gemeinsamer Logik in einer Basisklasse.
  * Kann zu einem einfacheren Design f�hren (�bersichtlicher Code).

---

## Vergleich Observer Pattern vs. Iterator Pattern <a name="link5"></a>

#### Observer Pattern

  * Wird verwendet, wenn �nderungen an einem Objekt m�glicherweise �nderungen anderer Objekte erfordern.
  * Benachrichtigt automatisch alle abh�ngigen Objekte (Beobachter) und aktualisiert sie, wenn ein Objekt (das Subject) seinen Zustand �ndert 


#### Iterator Pattern

  * Verwendet einen Iterator, um einen Container zu durchlaufen und auf dessen Elemente zuzugreifen
  * Entkoppelt Algorithmen von Containern

---

## Vergleich Factory Method Pattern vs. Abstract Factory Pattern <a name="link6"></a>

Das Factory Method Pattern und das Abstract Factory Pattern sind beides Entwurfsmuster f�r die Objekterstellung.
Sie weisen jedoch einige wesentliche Unterschiede auf:

#### Factory Method Pattern

  * *Zweck*: Definiert eine Schnittstelle zur Objekterstellung, erlaubt aber Unterklassen, den Typ der zu erstellenden Objekte zu �ndern.

  * *Klassendiagramm*: In der Regel umfasst es eine einzelne Erstellerklasse und mehrere konkrete Produktklassen.

  * *Anwendungsfall*: N�tzlich, wenn eine Klasse die zu erstellende Objektklasse nicht vorhersehen kann oder wenn eine Klasse m�chte, dass ihre Unterklassen die zu erstellenden Objekte festlegen.

  * *Beispiel*: Ein Dokumenteditor, in dem verschiedene Dokumenttypen (z. B. Word, PDF) mithilfe der Methode `createDocument()` erstellt werden k�nnen, die in den Unterklassen unterschiedlich implementiert ist.

#### Abstract Factory Pattern

  * *Zweck*: Bietet eine Schnittstelle zum Erstellen von Familien verwandter oder abh�ngiger Objekte, ohne deren konkrete Klassen anzugeben.

  * *Klassendiagramm*: Umfasst mehrere Factory-Klassen, die jeweils eine Familie verwandter Produkte erzeugen k�nnen.

  * *Anwendungsfall*: N�tzlich, wenn ein System unabh�ngig von der Erstellung, Zusammensetzung und Darstellung seiner Produkte sein muss oder mit mehreren Produktfamilien arbeiten muss.

  * *Beispiel*: Ein UI-Toolkit, das mehrere Erscheinungsbilder unterst�tzt (z. B. Windows, macOS), wobei jedes Erscheinungsbild eine Familie verwandter Objekte wie Buttons, Checkboxes usw. darstellt.

#### Vergleichszusammenfassung:

*Umfang*:<br />
  * Das Factory Method Pattern befasst sich mit der Erstellung eines einzelnen Produkts.
  * Das Abstract Factory Pattern befasst sich mit der Erstellung von Familien verwandter Produkte.

*Komplexit�t*:<br />
  * Die Factory-Methode ist einfacher und konzentriert sich auf ein einzelnes Produkt.
  * Die abstrakte Factory ist komplexer, da sie mehrere Produkte verarbeitet.

*Flexibilit�t*:<br />
  * Das Factory Method Pattern erm�glicht es Unterklassen, den genauen Typ des zu erstellenden Produkts zu bestimmen.
  * Das Abstract Factory Pattern stellt sicher, dass die von einer Fabrik erstellten Produkte miteinander kompatibel sind.


Diese Muster sind von grundlegender Bedeutung f�r das Verst�ndnis,
wie Systeme mit austauschbaren Komponenten entworfen und Objekte
auf eine Weise erstellt werden, die Flexibilit�t und Wiederverwendbarkeit f�rdert.

---

## Vergleich Bridge Pattern vs. Adapter Pattern <a name="link7"></a>

Wir beginnen unseren Vergleich mit dem Bridge Pattern:


### Vorteile des Bridge-Pattern

  * Der Code verfolgt durch die Extraktion der Abstraktion mehr das DRY Prinzip (*Don't Repeat Yourself*).
  * Der Code  ist erweiterbarer, da zwei separate Abstraktionen erstellt werden, die unabh�ngig voneinander variieren k�nnen.
  * Die einzelnen Klassen sind kleiner und daher leichter zu testen und zu verstehen.

### �hnlichkeiten mit dem Adapter-Pattern

Der Grund, warum der Unterschied zwischen dem Bridge-Pattern und dem Adapter-Pattern nicht so leicht zu verstehen, ist,
dass der verbindende Teil der &bdquo;Br�cke&rdquo; tats�chlich wie ein Adapter aussieht.

  * Ein Client kann als Abstraktion betrachtet werden, da er auch an eine Schnittstelle delegiert.
  * Ein Ziel kann als Implementierer betrachtet werden, da es ebenfalls eine Schnittstelle definiert, an die sich der Code halten muss.
  * Ein Adapter kann als verfeinerter Implementierer betrachtet werden, da er die Schnittstelle implementiert und die Anforderungen erf�llt.

Siehe auch die Beispiele [hier](https://doeken.org/blog/adapter-vs-bridge-pattern).

---

[Zur�ck](../Readme.md)

---
