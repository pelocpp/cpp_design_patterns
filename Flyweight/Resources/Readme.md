# Flyweight Pattern

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Flyweight Pattern* ist ein Entwurfsmuster aus der Kategorie der *Structural Pattern*,
das verwendet wird, um den Ressourcenverbrauch eines Programms mit einer sehr großen Anzahl von Objekten zu minimieren.
Beim Erzeugen von vielen tausend identischen Objekten können zustandslose "Flyweight"-Objekte
den in Anspruch genommen Speicher auf ein vertretbares Maß reduzieren.

#### Problem:

Manchmal arbeiten Programme mit einer großen Anzahl von Objekten, die dieselbe Struktur haben,
und einige Zustände dieser Objekte variieren nicht zeitlich.
Wenn wir den klassischen Ansatz verwenden (Instanzen erstellen, Instanzvariablen schreiben),
können sich die Speicher- bzw. Speicherbereichsanforderungen inakzeptabel erhöhen.
Das *Flyweight Pattern* stellt eine Alternative in diesem Kontext dar.

#### Lösung:

Ein so genanntes *Flyweight* ist ein Objekt, das den Speicherbedarf minimiert,
indem so viele Daten wie möglich mit anderen ähnlichen Objekten geteilt werden.
Es gestattet, Objekte in großer Anzahl zu verwenden,
wenn eine einfache wiederholte Erzeugung entsprechender Objekte 
eine nicht akzeptablen Speicherbereich beanspruchen würde.
Für jedes Objekt, das gemeinsam genutzte Daten verwendet,
wird nur ein Verweis (Referenz, Pointer) auf ein gemeinsam genutztes Objekt gespeichert.

Das *Flyweight Pattern* verwendet häufig eine Variation des *Factory Method* Entwurfsmusters
für die Erzeugung der gemeinsam genutzten Objekte.
Die Fabrik erhält eine Anfrage für eine *Flyweight* Instanz.
Wenn bereits ein übereinstimmendes Objekt verwendet wird,
wird eine Referenz dieses Objekt zurückgegeben. Andernfalls wird ein neues *Flyweight* Objekt generiert.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Flyweight Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **FlyweightBase**: Definiert eine Schnittstelle, über die *Flyweight* Objekte einen externen
    Zustand empfangen und darauf operieren können.
  * **ConcreteFlyweight**: Implementiert die *Flyweight* Objekt Schnittstelle und fügt Speicher für den intrinsischen Status (gemeinsam genutzten Status) hinzu, falls vorhanden.
    Ein ConcreteFlyweight-Objekt muss "gemeinsam nutzbar" (*sharable*) sein.
    Jeder Zustand, den dieses Objekt speichert, muss intrinsisch sein,
    d.h. er muss unabhängig vom Kontext des `ConcreteFlyweight`-Objekts sein.
  * **UnsharedFlyweight**: Nicht alle *Flyweight* Unterklassen können gemeinsam genutzt werden
    Die *Flyweight* Objekt Schnittstelle ermöglicht das Teilen, erzwingt es jedoch nicht
    Es ist üblich, dass `UnsharedFlyweight`-Objekte `ConcreteFlyweight`-Objekte als
    Kind-Objekte ab einer bestimmten Ebene in der Flyweight-Objektstruktur haben.
  * **FlyweightFactory**: Die *FlyweightFactory* erstellt und verwaltet *Flyweight* Objekte.
    Darüber hinaus verwaltet die Fabrik einen Pool unterschiedlicher *Flyweight* Objekte.
    Die Fabrik gibt bei einer entsprechenden Anforderung ein Objekt aus dem Pool zurück,
    falls es bereits erstellt wurde,
    oder fügt dem Pool ein Neues hinzu und gibt dieses zurück, falls dies der Anforderung entspricht.


<img src="dp_flyweight.png" width="500">

Abbildung 1: Schematische Darstellung des *Flyweight Patterns*.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/flyweight)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Flyweight)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:

To be done:

## Literaturhinweise

*Hinweise*:

---

[Zurück](../../Readme.md)

---
