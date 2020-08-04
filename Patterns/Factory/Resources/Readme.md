# Factory Pattern

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Factory Pattern* ist ein Entwurfsmuster, mit dem Objekte erstellt werden können,
ohne die Erstellungslogik dem Client zur Verfügung zu stellen.
Für die neu erstellten Objekte steht eine gemeinsame Schnittstelle zur Verfügung.

#### Lösung:

Dieses Muster wird auch als *Simple Factory* Pattern bezeichnet.
Das *Factory*-Entwurfsmuster definiert eine Fabrikklasse mit einer Methode zum Erstellen von Objekten unterschiedlichen Typs
und überlässt die Auswahl des konkreten Klassentyps der Fabrikklasse.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Factory Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **ProductBase**: Basisklasse (oder Schnittstelle) für alle Produkte,
    die von der *Factory*-Klassen hergestellt werden sollen. Die Schnittstelle beschreibt eine oder mehrere Methoden,
    die von den konkreten Ableitungen der Klasse implementiert werden.
  * **ConcreteProduct**: Konkrete Implementierung der Klasse `ProductBase`.
    Objekte des Typs `ConcreteProduct` werden von der Klasse *Factory* erzeugt.
  * **Factory**: Diese Klasse besitzt eine Methode `getProduct`,
    die Objekte zurückliefert, die die `ProductBase`-Schnittstelle implementieren.
    Über einen Parameter der `getProduct`-Methode wird typischerweise gesteuert, welches `ConcreteProduct` Objekt zu erzeugen ist.

<img src="dp_factory_pattern.svg" width="700">

Abbildung 1: Schematische Darstellung des *Factory Patterns*.

#### Hinweis:

Die beiden Entwurfsmuster *Abstract Factory* und *Factory Method* sind nicht 
miteinander zu verwechseln.

Sie haben zumindest gemeinsam, dass sie beide den Client von konkreten Typen entkoppeln.
Der Client kennt nur die Schnittstelle zur Factory und den Produkten. Welche Produkte konkret erstellt werden, entscheidet die Unterklasse/Implementierung der Schnittstelle. Der Client stützt sich allein auf Abstraktion.
Damit zu den Unterschieden:

**Abstract Factory**<br/>
  * Bietet eine Schnittstelle zum Erstellen von Familien verwandter oder abhängiger Objekte, ohne deren konkrete Klassen anzugeben.
  * Ganze Produktfamilie wird erstellt.
  * Breite Schnittstelle.
  * Schnittstelle (Abstract Factory) ist oft nur ein Interface und enthält keinen Implementierungscode.

**Factory Method**<br/>
  * Definiert eine Schnittstelle zum Erstellen eines Objekts, aber lässt
    die Unterklassen entscheiden, welche Klasse instanziiert werden soll. Mit dem *Factory Method Pattern*  kann eine Klasse die Instanziierung auf Unterklassen verschieben.
  * Schmale Schnittstelle.
  * Schnittstelle ist oft abstrakt und enthält generischen Code (Herstellungscode, den alle Produkte durchlaufen müssen).
 
#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[Factory Method vs. Simple Factory](https://dzone.com/articles/factory-method-vs-simple-factory-1)

und 

[Factory vs Factory Method vs Abstract Factory](https://medium.com/bitmountn/factory-vs-factory-method-vs-abstract-factory-c3adaeb5ac9a)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
