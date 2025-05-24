# Entwurfsmuster im Vergleich

[Zurück](../Readme.md)

---

## Überblick

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

Das Decorator Pattern umhüllt eine Methode eines Zielobjekts,
das Proxy Pattern ein ganzes Objekt.

#### Decorator Pattern

  * Umhüllt eine Methode eines Originalobjekts.
  * Diese Methode gilt es aufzurufen.
  * Vor und nach dem Aufruf der Zielmethode kann zusätzliche Funktionalität umgesetzt/ergänzt werden.
  * Aus einer Reihe von Gründen wird diese Funktionalität *nicht* am Zielobjekt direkt umgesetzt.
  * *Feature*: Das Zielobjekt kann wiederum ein Dekorator sein: Dekoratoren-Objekte sind schachtelbar (&bdquo;Nested use of decorator objects&rdquo;).
  * Die Reihenfolge der geschachtelten Dekoratoren-Objekte ist beliebig bzw. einstellbar.
  * Die Reihenfolge der Dekoratoren-Objekte ist zur *Laufzeit* einstellbar.

#### Proxy Pattern

  * Umhüllt ein gesamtes Objekt.
  * 1:1 Ersetzung eines Originalobjekts mit entsprechenden Verantwortlichkeiten (Beispiel: Zielmethode wird *nicht* aufgerufen).
  * Kontrolliert/steuert den Zugriff auf ein unterlagertes Objekt.
  * Kontrolliert die Aufrufe von *getter*- und *setter*-Methoden, bevor diese an das Zielobjekt weitergereicht werden.

---

## Vergleich Visitor Pattern vs. Composite Pattern <a name="link2"></a>

Es gibt zunächst prinzipielle Unterschiede:

  * Das Composite Pattern ist ein Strukturmuster, das heißt, es dient zum Aufbau einer Datenstruktur.
  * Das Visitor Pattern ist ein Verhaltensmuster, es ist für Beziehungen und Verhalten verantwortlich.

#### Visitor Pattern

Wird angewendet, um eine Operation an einer Gruppe ähnlicher Objekte durchzuführen.

#### Composite Pattern

Wird angewendet, um einzelne Objekte und Objektgruppen homogen zu behandeln.

Fazit:<br />

Es handelt sich um unterschiedliche Muster, die jedoch häufig zusammen verwendet werden:

  * Der Zweck des Composite Patterns besteht darin, dieselbe Operation auf mehrere Elemente anzuwenden, die eine gemeinsame Schnittstelle haben.
  * Der Zweck des Visitor Patterns besteht darin, mehrere Elemente um eine neue Operation zu erweitern, ohne deren Implementierung zu ändern. Daher sieht man häufig:

```cpp
Composite* c = new Composite();
Visitor* v = new ConcreteVisitor();
c->visit(v);
```
---

## Vergleich Strategy Pattern vs. Adapter Pattern <a name="link3"></a>

Das Strategy Pattern wählt zur Laufzeit das richtige &bdquo;*Verhalten*&rdquo; aus,
während das Adapter Pattern inkompatibele Schnittstellen zusammenarbeiten lässt. 

#### Strategy Pattern

  * Ermöglicht die Definition/Realisierung einer Menge von Algorithmen, die austauschbar sind.
  * Wählt zur Laufzeit das richtige &bdquo;*Verhalten*&rdquo; (Strategie) aus.

#### Adapter Pattern

  * Ermöglicht die Zusammenarbeit inkompatibler Schnittstellen.
  * Ändert die Schnittstelle eines Objekts.
  * Fungiert als Wrapper zwischen zwei Objekten.
  * Fängt Aufrufe eines Objekts ab und transformiert sie in ein für das zweite Objekt erkennbaren Aufruf samt Konvertierung beteiligter Formate.

---

## Vergleich Strategy Pattern vs. Template Method Pattern <a name="link4"></a>

#### Strategy Pattern

  * Ermöglicht unterschiedliches Verhalten ähnlicher Objekte.
  * Ermöglicht übersichtlichen Code.
  * Ermöglicht das nahtlose Hinzufügen neuen Verhaltens.


#### Template Method Pattern

  * Standardisiert Arbeitsabläufe über mehrere Implementierungen hinweg.
  * Ermöglicht Variationen in einzelnen Schritten unter Beibehaltung einer Gesamtsequenz.
  * Reduziert Code-Duplikation durch Implementierung gemeinsamer Logik in einer Basisklasse.
  * Kann zu einem einfacheren Design führen (übersichtlicher Code).

---

## Vergleich Observer Pattern vs. Iterator Pattern <a name="link5"></a>

#### Observer Pattern

  * Wird verwendet, wenn Änderungen an einem Objekt möglicherweise Änderungen anderer Objekte erfordern.
  * Benachrichtigt automatisch alle abhängigen Objekte (Beobachter) und aktualisiert sie, wenn ein Objekt (das Subject) seinen Zustand ändert 


#### Iterator Pattern

  * Verwendet einen Iterator, um einen Container zu durchlaufen und auf dessen Elemente zuzugreifen
  * Entkoppelt Algorithmen von Containern

---

## Vergleich Factory Method Pattern vs. Abstract Factory Pattern <a name="link6"></a>

Das Factory Method Pattern und das Abstract Factory Pattern sind beides Entwurfsmuster für die Objekterstellung.
Sie weisen jedoch einige wesentliche Unterschiede auf:

#### Factory Method Pattern

  * *Zweck*: Definiert eine Schnittstelle zur Objekterstellung, erlaubt aber Unterklassen, den Typ der zu erstellenden Objekte zu ändern.

  * *Klassendiagramm*: In der Regel umfasst es eine einzelne Erstellerklasse und mehrere konkrete Produktklassen.

  * *Anwendungsfall*: Nützlich, wenn eine Klasse die zu erstellende Objektklasse nicht vorhersehen kann oder wenn eine Klasse möchte, dass ihre Unterklassen die zu erstellenden Objekte festlegen.

  * *Beispiel*: Ein Dokumenteditor, in dem verschiedene Dokumenttypen (z. B. Word, PDF) mithilfe der Methode `createDocument()` erstellt werden können, die in den Unterklassen unterschiedlich implementiert ist.

#### Abstract Factory Pattern

  * *Zweck*: Bietet eine Schnittstelle zum Erstellen von Familien verwandter oder abhängiger Objekte, ohne deren konkrete Klassen anzugeben.

  * *Klassendiagramm*: Umfasst mehrere Factory-Klassen, die jeweils eine Familie verwandter Produkte erzeugen können.

  * *Anwendungsfall*: Nützlich, wenn ein System unabhängig von der Erstellung, Zusammensetzung und Darstellung seiner Produkte sein muss oder mit mehreren Produktfamilien arbeiten muss.

  * *Beispiel*: Ein UI-Toolkit, das mehrere Erscheinungsbilder unterstützt (z. B. Windows, macOS), wobei jedes Erscheinungsbild eine Familie verwandter Objekte wie Buttons, Checkboxes usw. darstellt.

#### Vergleichszusammenfassung:

*Umfang*:<br />
  * Das Factory Method Pattern befasst sich mit der Erstellung eines einzelnen Produkts.
  * Das Abstract Factory Pattern befasst sich mit der Erstellung von Familien verwandter Produkte.

*Komplexität*:<br />
  * Die Factory-Methode ist einfacher und konzentriert sich auf ein einzelnes Produkt.
  * Die abstrakte Factory ist komplexer, da sie mehrere Produkte verarbeitet.

*Flexibilität*:<br />
  * Das Factory Method Pattern ermöglicht es Unterklassen, den genauen Typ des zu erstellenden Produkts zu bestimmen.
  * Das Abstract Factory Pattern stellt sicher, dass die von einer Fabrik erstellten Produkte miteinander kompatibel sind.


Diese Muster sind von grundlegender Bedeutung für das Verständnis,
wie Systeme mit austauschbaren Komponenten entworfen und Objekte
auf eine Weise erstellt werden, die Flexibilität und Wiederverwendbarkeit fördert.

---

## Vergleich Bridge Pattern vs. Adapter Pattern <a name="link7"></a>

Wir beginnen unseren Vergleich mit dem Bridge Pattern:


### Vorteile des Bridge-Pattern

  * Der Code verfolgt durch die Extraktion der Abstraktion mehr das DRY Prinzip (*Don't Repeat Yourself*).
  * Der Code  ist erweiterbarer, da zwei separate Abstraktionen erstellt werden, die unabhängig voneinander variieren können.
  * Die einzelnen Klassen sind kleiner und daher leichter zu testen und zu verstehen.

### Ähnlichkeiten mit dem Adapter-Pattern

Der Grund, warum der Unterschied zwischen dem Bridge-Pattern und dem Adapter-Pattern nicht so leicht zu verstehen, ist,
dass der verbindende Teil der &bdquo;Brücke&rdquo; tatsächlich wie ein Adapter aussieht.

  * Ein Client kann als Abstraktion betrachtet werden, da er auch an eine Schnittstelle delegiert.
  * Ein Ziel kann als Implementierer betrachtet werden, da es ebenfalls eine Schnittstelle definiert, an die sich der Code halten muss.
  * Ein Adapter kann als verfeinerter Implementierer betrachtet werden, da er die Schnittstelle implementiert und die Anforderungen erfüllt.

Siehe auch die Beispiele [hier](https://doeken.org/blog/adapter-vs-bridge-pattern).

---

[Zurück](../Readme.md)

---
