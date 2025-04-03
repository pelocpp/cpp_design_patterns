# Entwurfsmuster im Vergleich

[Zur�ck](../Readme.md)

---

## �berblick

  * [Vergleich Decorator Pattern vs. Proxy Pattern](#link1)
  * [Vergleich Visitor Pattern vs. Composite Pattern](#link2)
  * [Vergleich Strategy Pattern vs. Adapter Pattern](#link3)
  * [Vergleich Strategy Pattern vs. Template Method Pattern](#link4)
  * [Vergleich Observer Pattern vs. Iterator Pattern](#link5)

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

[Zur�ck](../Readme.md)

---
