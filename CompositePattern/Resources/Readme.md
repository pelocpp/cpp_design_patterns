# Composite Pattern

## Wesentliche Merkmale

##### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Composite Entwurfsmuster* ist ein strukturelles Entwurfsmuster,
mit dem Sie Objekte zu Baumstrukturen zusammensetzen und dann mit diesen Strukturen arbeiten können,
als wären sie einzelne Objekte.

#### Problem:

Der Einsatz des *Composite Entwurfsmuster* ist nur dann sinnvoll,
wenn sich die Kernstruktur der Anwendung als Baum dargestellen lässt.

Stellen Sie sich beispielsweise vor, Sie haben zwei Arten von Objekten:
Produkte und Kartons. Ein Karton kann mehrere Produkte sowie mehrere kleinere Kartons enthalten.
Diese kleinen Kartons können wiederum Produkte oder sogar kleinere Kartons usw. aufnehmen.

Angenommen, Sie möchten ein Bestellsystem erstellen, das diese Klassen verwendet.
Bestellungen können einfache Produkte ohne Verpackung sowie mit Produkten gefüllte Kartons und andere Kartons enthalten.
Wie würden Sie den Gesamtpreis einer solchen Bestellung bestimmen?

Sie können den direkten Ansatz ausprobieren:
Packen Sie alle Kartons aus, gehen Sie alle Produkte durch und berechnen Sie dann die Gesamtsumme.
Das wäre in der realen Welt machbar.
In einem Programm ist es jedoch nicht so einfach wie das Ausführen einer Wiederholungsschleife.
Sie müssen die Klassen der Produkte und Schachteln, die Sie durchlaufen,
die Verschachtelungsebenen der Schachteln und andere unangenehme Details im Voraus kennen.
All dies macht den direkten Ansatz entweder sehr umständlich oder sogar unmöglich.


#### Lösung:

Die zentrale Idee des *Composite Entwurfsmusters* ist es, mit einer gemeinsamen Schnittstelle sowohl
für Produkte als auch für Kartons zu arbeiten. Aufgabe dieser Schnittstelle wäre es an dem betrachteten Beispiel,
eine Methode zur Berechnung des Gesamtpreises zu deklarieren.

Wie könnte eine derartige Methode aussehen?
Für ein Produkt wird einfach der Produktpreis zurückgegeben.
Bei einer Schachtel wird jeder Artikel in der Schachtel überprüft, der Preis abgefragt und eine Gesamtsumme für diese Schachtel zurückgegeben.

Wenn eines dieser Elemente eine kleinere Schachtel wäre, würde diese Schachtel auch ihren Inhalt usw. durchgehen, bis die Preise aller inneren Komponenten berechnet wurden.
Eine Schachtel kann sogar zusätzliche Kosten zum Endpreis hinzufügen, wie z.B. Verpackungskosten oder ähnliches.

Der große Vorteil dieses Ansatzes besteht darin, dass Sie sich nicht um die konkreten Objekte kümmern müssen (Produkt oder Karton),
aus denen der Baum besteht. Sie müssen nicht wissen, ob es sich bei einem Objekt um ein einfaches Produkt oder eine große Schachtel mit vielen Einzelteilen handelt.
Sie können die Objekte alle gleich über die gemeinsame Schnittstelle behandeln.
Wenn Sie eine Methode aufrufen, übergeben die Objekte selbst die Anforderung an den Baum.

#### Struktur (UML):

<img src="dp_composite_pattern.png" width="600">

Abbildung: Schematische Darstellung des *Composite Entwurfsmusters*.


## Anwendungen des Design Pattern in der STL:

  * TBD

## Anwendungsbeispiel:

  * TBD

* Siehe Stockmayer File and Directory !!!*


Beispiele:

Die Beispiele zu diesem Pattern orientieren sich an:

[https://refactoring.guru/design-patterns/strategy](https://refactoring.guru/design-patterns/strategy/java/example)


## Literaturhinweise

http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html

https://github.com/achimoraites/DesignPatterns/blob/master/CompositePattern/FileSystem/src/ui/FileSystem.java

https://www.codingame.com/playgrounds/5659/c17-filesystem


# TODO

Beispiel mit arithmetischen Ausdrücken:

https://nick79.gitlab.io/mnblog/post/composite_design_pattern/

---

[Zurück](../../Readme.md)

---
