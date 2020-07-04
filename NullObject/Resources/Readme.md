# *Null Object* Entwurfsmuster

## Wesentliche Merkmale

Das *Null Object Pattern* ist ein Entwurfsmuster, das sich der Thematik von Null-Referenzen annimmt.
Null-Referenzen gibt es in anderen Programmiersprachen sehr wohl, in C++ sind sie per Definition nicht existent.
Wir sprechen daher besser von so genannten *Null*-Objekten, also Objekten, die keinerlei Funktionalität haben.

Der Sinn des Musters besteht darin, einer Referenz ein Objekt zuzuweisen, das keine Aktion ausführt.
Dadurch wird erreicht, dass die Referenz zu jedem Zeitpunkt auf ein gültiges Objekt verweist,
was Behandlungen von Sonderfällen (das Nichtvorhandensein) erübrigt.

#### Kategorie: *Behavioural Pattern*

#### Ziel / Absicht:

Objekte ohne Funktionalität stellen natürlich einen Sonderfall dar.
Sie können Sinn ergeben, wenn reale Daten - zum Beispiel in einem Testszenario - nicht verfügbar sind,
man aber das Standardverhalten der Software trotzdem bereitstellen möchte.
Das Null-Objekt spiegelt folglich eine "*Do-Nothing*"-Beziehung wieder.

#### Problem:

Das  *Null Object* Entwurfsmuster befreit uns von der Pflicht, zur Laufzeit Abfragen bzgl. gewisser Zustände vornehmen zu müssen.
Überall im Quellcode, wo Überprüfungen auf Nullwerte erforderlich wären (was in C++ bei Referenzen ohnehin nicht möglich ist),
kommen Nullobjektklassen zum Einsatz.

#### Lösung:

Im *Null Object* Entwurfsmuster erstellen wir zunächst eine abstrakte Klasse,
die die verschiedenen auszuführenden Operationen definiert.

Davon leiten wir reale Klassen ab, die die eigentliche Funktionalität implementieren und schließlich eine Null-Objekt Klasse,
die *keine* Implementierung der Basisklasse bereitstellt. Um es anderes zu formulieren: Streng genommen stellt auch die
Null-Objekt Klasse eine Implementierung der Basisklasse dar, aber eben mit leeren Methodenrümpfen.

Nun kann man die Null-Objekt Klasse überall dort einsetzen, wo aus welchen Gründen auch immer,
eine Klasse mit einer realen
Realisierung (temporär) nicht anwendbar ist.


#### Struktur (UML):

<img src="db_null_object.png" width="500">

Abbildung 1: Schematische Darstellung des *Null Object* Entwurfsmusters.

#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/composite/cpp/example#example-0)

vor.

#### Beginners Example:

#### 'Real-World' Beispiel:


## Literaturhinweise

*Hinweise*:

Die Anregungen zu den Beispielen zum Null Object Pattern stammen aus

[Null Object Design Pattern in C++](https://iq.opengenus.org/null-object-design-pattern-cpp/)<br>(abgerufen am 15.05.2020).

[Dmitri Nesteruk "Design Patterns in Modern C++](https://github.com/Apress/design-patterns-in-modern-cpp)<br>(abgerufen am 14.05.2020).

---

[Zurück](../../Readme_05_Catalog.md)

---
