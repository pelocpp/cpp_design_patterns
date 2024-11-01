# Composite Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_composite_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Um einzelne Objekte und Gruppen von Objekten einheitlich zu behandeln.&rdquo;

Das *Composite Entwurfsmuster* ist ein strukturelles Entwurfsmuster,
mit dem Sie Objekte zu Baumstrukturen zusammensetzen und dann mit diesen Strukturen arbeiten k�nnen,
als w�rde es sich um einzelne Objekte handeln.

#### Problem:

Der Einsatz des *Composite Entwurfsmuster* ist dann sinnvoll,
wenn sich die Kernstruktur der Daten einer Anwendung als baumartige Struktur darstellen l�sst.

Stellen Sie sich beispielsweise vor, Sie haben zwei Arten von Objekten:
Produkte und Kartons. Ein Karton kann mehrere Produkte sowie mehrere kleinere Kartons enthalten.
Diese kleineren Kartons k�nnen wiederum Produkte oder sogar noch kleinere Kartons aufnehmen usw.

Betrachten wir nun ein Bestellsystem, das diese Klassen verwendet.
Bestellungen k�nnen einfache Produkte ohne Verpackung sowie mit Produkten gef�llte Kartons und andere Produkte enthalten.
Wie w�rden Sie den Gesamtpreis einer solchen Bestellung bestimmen?

Sie k�nnen den direkten Ansatz ausprobieren:
Packen Sie alle Kartons aus, gehen Sie alle Produkte durch und berechnen Sie dann die Gesamtsumme.
Das w�re in der realen Welt machbar.
In einem Programm ist es jedoch nicht so einfach wie das Ausf�hren einer Wiederholungsschleife.
Sie m�ssen die Klassen der Produkte und Schachteln, die Sie durchlaufen,
die Verschachtelungsebenen der Schachteln und andere unangenehme Details kennen.
All dies macht den direkten Ansatz entweder sehr umst�ndlich oder sogar unm�glich.

#### L�sung:

Die zentrale Idee des *Composite Entwurfsmusters* ist es, mit einer gemeinsamen Schnittstelle sowohl
f�r Produkte als auch f�r Kartons zu arbeiten. Aufgabe dieser Schnittstelle w�re es an dem betrachteten Beispiel,
eine Methode zur Berechnung des Gesamtpreises zu deklarieren.

Wie k�nnte eine derartige Methode aussehen?
F�r ein Produkt wird einfach der Produktpreis zur�ckgegeben.
Bei einer Schachtel wird jeder Artikel in der Schachtel �berpr�ft, der Preis abgefragt und eine Gesamtsumme f�r die Schachtel zur�ckgegeben.

Wenn eines dieser Elemente eine kleinere Schachtel w�re, w�rde diese Schachtel auch ihren Inhalt durchgehen, solange, bis die Preise aller inneren Komponenten berechnet wurden.
Eine Schachtel kann sogar zus�tzliche Kosten zum Endpreis hinzuf�gen, wie z.B. Verpackungskosten oder �hnliches.

Der gro�e Vorteil dieses Ansatzes besteht darin, dass Sie sich nicht um die konkreten Objekte k�mmern m�ssen (Produkt oder Karton),
aus denen der Baum besteht. Sie m�ssen nicht wissen, ob es sich bei einem Objekt um ein einfaches Produkt oder eine Schachtel mit Einzelteilen handelt.
Sie k�nnen die Objekte alle gleich �ber eine gemeinsame Schnittstelle behandeln.
Wenn Sie eine Methode aufrufen, �bergeben die Objekte selbst die Anforderung an den Baum.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Composite Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Component**: Stellt eine Abstraktion (abstrakte Klasse, Interface) f�r alle Komponenten dar (elementare und zusammengesetzte).
    Manchmal werden neben den eigentlichen Methoden der Komponente auch zus�tzlich Methoden f�r den Zugriff
    auf das �bergeordnete Element einer Komponente in der rekursiven Struktur definiert.
  * **Composite**: Kernst�ck des Entwurfsmusters. Es handelt sich gewisserma�en um eine *zusammengesetzte Komponente*.
    Das hei�t, dass ein `Composite`-Objekt eine Liste f�r die Kind-Elemente verwaltet.
    Das Objekt stellt Methoden zum Hinzuf�gen und Entfernen von Kind-Elementen bereit.
    Zus�tzlich werden die Methoden der `Component`-Klasse implementiert. Typischerweise wird deren
    Realisierung an die entsprechende Methode des Kind-Elements delegiert.
  * **Leaf**: 
    Stellt ein "Blatt"-Objekt in der Komposition (Baumstruktur) dar. Es werden alle Methoden der `Component`-Klasse implementiert.

<img src="dp_composite_pattern.svg" width="600">

*Abbildung* 1: Schematische Darstellung des *Composite Entwurfsmusters*.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) - Variante mit "Raw"-Zeiger

[Quellcode 2](../ConceptualExample02.cpp) - Variante mit `std::shared_ptr`-Zeiger

---

#### 'Beginners Example':

Das Beispiel demonstriert das klassische *Composite Pattern* mit Kreisen und Gruppen von Kreisen:

```cpp
01: struct IShape
02: {
03:     virtual void draw() const = 0;
04: };
05: 
06: class Circle : public IShape
07: {
08: private:
09:     std::string m_name;
10: 
11: public:
12:     ...
13:     virtual void draw() const override {
14:         std::cout << "Circle: " << m_name;
15:     }
16: };
17: 
18: class Group : public IShape
19: {
20: private:
21:     std::string m_name;
22:     std::vector<std::shared_ptr<IShape>> m_objects;
23: 
24: public:
25:     ...
26:     virtual void draw() const override {
27:         std::cout << "Group " << m_name << " contains:" << std::endl;
28:         for (const std::shared_ptr<IShape> shape : m_objects) {
29:             shape->draw();
30:         }
31:     }
32:     ...
33: };
34: 
35: void test_shapes()
36: {
37:     Group root("Root");
38: 
39:     std::shared_ptr<IShape> circle = std::make_shared<Circle>("Top Level Circle");
40:     root.push(circle);
41: 
42:     std::shared_ptr<Group> subgroup = std::make_shared<Group>("Subgroup");
43:     subgroup->push(std::make_shared<Circle>("First Second Level Circle"));
44:     subgroup->push(std::make_shared<Circle>("Another Second Level Circle"));
45:     root.push(subgroup);
46: 
47:     root.draw();
48: }
```

Betrachten Sie die Schl�sselstellen in dem Code-Fragment:

  * Zeile 18: Klasse `Group` leitet sich von Klasse `IShape` ab.
  * Zeile 45: Auch `Group`-Objekte k�nnen mit `push` einer Gruppe hinzugef�gt werden, also nicht nur `Circle`-Objekte.
  * Zeilen 26 und 29: Die `draw`-Methode agiert f�r Kreise und Kreisgruppen unterschiedlich.
 
---

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/composite/cpp/example#example-0)

vor.

**Hinweis**:

Das *Conceptual Example* liegt in zwei Varianten vor:

  * Variante 1: klassisch - d.h. mit "raw"-Zeigern.
  * Variante 2: Wie Variante 1, aber mit `std::shared_ptr` Objekten und `std::enable_shared_from_this<>` Mechanismus.

In Variante 2 wird prinzipiell ohne "raw"-Zeiger gearbeitet, also so,
wie man es der "reinen Lehre" nach machen sollte. Dabei stellt sich aber eine Frage:
Wie erhalte ich von einem Objekt einen `std::shared_ptr`, desses Objekterzeugung
au�erhalb meines Wirkungskreises liegt. Die Frage lautet also gewisserma�en:

```cpp
component->setParent((std::shared_ptr<Component>) this);
```

Das geht so nicht, wie zu erwarten war. Es gibt aber den folgenden Weg:

```cpp
class Composite : public Component, public std::enable_shared_from_this<Composite> {
    ...
}
```

Die Klasse `Composite` leitet sich von einer Standard-Klasse `std::enable_shared_from_this<>` ab,
die genau zu diesem Zweck realisiert wurde.
Damit vererbt sie eine Methode `shared_from_this` an die Kindklasse:

```cpp
component->setParent(shared_from_this());
```

**Achtung**: Der Aufruf `shared_from_this` ist aber nur dann zul�ssig,
wenn es von dem Objekt (hier: Klasse `Composite`) bereits einen Shared Pointer gibt!
Das muss nicht immer der Fall sein!
Weitere Details der Realisierung entnehmen Sie bitte der zweiten Variante des *Conceptual Example*.

Noch ein zweiter **Hinweis**:
In der zweiten Variante gibt es in der Klasse `Composite` einen STL_Container (typischerweise `std::list` oder `std::vector`)
zur Verwaltung der Kind-Elemente. Beim Gebrauch von `std::shared_ptr`-Objekten k�nnen hier zirkul�re Referenzen 
entstehen - der Container in meinem Beispiel wurde deshalb als

```cpp
std::vector<std::weak_ptr<Component>> m_children;
```

definiert! Dies l�st das Problem zirkul�rer Referenzen, generiert gleichzeitig aber ein zweites Problem:
F�r `std::weak_ptr`-Objekte ist kein `==`-Operator definiert! Damit kommt es bei der Anwendung vieler STL-Algorithmen,
sei es explizit oder implizit (z.B. in einer *range-based loop*), zu �bersetzungsfehlern!
Aus diesem Grund habe ich in der zweiten Variante die Methode `remove` weggelassen,
da sie intern den `==`-Operator ben�tigen w�rde. Wer ebenfalls diese Methode implementieren
m�chte, findet unter dem Stichwort *"removing an item from a list of weak_ptrs"*
L�sungsm�glichkeiten im Netz angeboten (Stichwort *Custom Deleter*), die ich aus Aufwandsgr�nden
in diesem Beispiel nicht umsetzen wollte.


#### Ein zweites 'Beginners Example':

Ein typisches Beispiel f�r das *Composite Entwurfsmuster* ist ein Dateisystem mit Ordnern und Dateien:
Ordner k�nnen Dateien oder andere Ordner enthalten oder leer sein. Andererseits enthalten Dateien keine Ordner oder andere Dateien!

Um eine Analogie zur *Abbildung* 1 herzustellen, stellen wir die drei relevanten Header-Dateien kurz vor.
Die Schnittstelle f�r die Beschreibung der �bergreifenden Komponente k�nnte so aussehen:

```cpp
class FileComponent {
public:
    virtual void display(const std::string&) const = 0;
};
```

Davon leiten wir nun zwei Klassen f�r Dateien (Klasse `File`) und Ordner (Klasse `Directory`) ab:

```cpp
class File : public FileComponent {
public:
    File(const std::string& name, const std::string& data);
    void display(const std::string&) const override;
    ...

private:
    std::string m_name;
    std::string m_data;
};
```

und 

```cpp
class Directory : public FileComponent {
public:
    // c'tor(s)
    Directory(const std::string& name);

    // public interface
    void addFileComponent(FileComponent*);
    void display(const std::string&) const override;

private:
    std::string m_name;
    std::vector<FileComponent*> m_contents;
};
```

Ein Testrahmen zur Veranschaulichung der Funktionalit�t k�nnte so aussehen:

```cpp
void main() {

    Directory dir1 ("Directory 1:");
    Directory dir2 ("Directory 2:");

    File file1 ("File 1", "Data of file 1");
    File file2 ("File 2", "Data of file 2");
    File file3 ("File 3", "Data of file 3");

    dir1.addFileComponent(&file1);
    dir1.addFileComponent(&file2);
    dir1.addFileComponent(&dir2);
    dir2.addFileComponent(&file3);
    dir2.addFileComponent(&dir3);

    dir1.display(" ");
}
```

  * *Pros*:
    * Funktionalit�t des *Composite Entwurfsmusters* erkennbar.

  * *Kontras*
    * Ein Raw-Pointer (hier: `std::vector<FileComponent*>`) sollte in Produktsoftware vermieden werden
    * Die Dateien und Ordner sind in dem Beispiel nur exemplarisch vorhanden

In einer zweiten Implementierung stellen wir eine Realisierung auf Basis des C++17 Filesystems und unter Verwendung
der Klasse `std::shared_ptr<FileComponent>` vor.

#### &bdquo;Real-World&rdquo; Beispiel:

In den Beispielen zu diesem Entwurfsmuster (siehe Klasse `DirectoryEx` und Datei `FileSystemAdvanced.cpp`)
k�nnen Sie die Umsetzung des *Composite Entwurfsmusters* am realen Dateisystem betrachten.

Auf meinem Rechner sieht die Ausgabe des Programms so aus, wenn wir als Root-Verzeichnis das Projektverzeichnis
dieses Beispiels eingeben. Weitere Details zur Realisierung entnehmen Sie bitte dem Beispielcode.

```cpp
C:\Development\GitRepositoryCPlusPlus\Cpp_DesignPatterns\CompositePattern
    CompositePattern.vcxproj - data: 8080
    CompositePattern.vcxproj.filters - data: 2688
    CompositePattern.vcxproj.user - data: 168
    ConceptualExample.cpp - data: 5989
    Debug
        CompositePattern.Build.CppClean.log - data: 1952
        CompositePattern.log - data: 193
        CompositePattern.tlog
            CL.command.1.tlog - data: 8108
            CL.read.1.tlog - data: 137510
            CL.write.1.tlog - data: 12606
            CompositePattern.lastbuildstate - data: 188
            link.command.1.tlog - data: 2892
            link.read.1.tlog - data: 6222
            link.write.1.tlog - data: 1876
        CompositePattern.vcxproj.FileListAbsolute.txt - data: 0
        ConceptualExample.obj - data: 337227
        Directory.obj - data: 265238
        DirectoryEx.obj - data: 298175
        File.obj - data: 218396
        FileSystemAdvanced.obj - data: 815101
        FileSystemBeginners.obj - data: 173995
        FileSystemExample01.obj - data: 173995
        FileSystemExample02.obj - data: 815046
        Program.obj - data: 37639
        vc142.idb - data: 322560
        vc142.pdb - data: 1003520
    Directory.cpp - data: 989
    Directory.h - data: 749
    DirectoryEx.cpp - data: 1136
    DirectoryEx.h - data: 828
    File.cpp - data: 961
    File.h - data: 700
    FileComponent.h - data: 494
    FileSystemAdvanced.cpp - data: 1940
    FileSystemBeginners.cpp - data: 1152
    FileSystemExample03.cpp - data: 1955
    Program.cpp - data: 877
    Resources
        CompositePattern.png - data: 24524
        CompositePattern_02.jpg - data: 43563
        CompositePattern_02.png - data: 19732
        dp_composite_pattern.png - data: 17626
        Readme.md - data: 6441
```

---

## Weitere Beispiele

Ein weiterer Anwendungsfall f�r das *Composite Entwurfsmuster* sind arithmetische Ausdr�cke.
Anregungen finden sich zum Beispiel unter

[https://stackoverflow.com/questions](https://stackoverflow.com/questions/57942934/composite-design-pattern-how-to-create-calculator)<br>(abgerufen am 11.05.2020).

---

## Pro / Kontra:

###### Pros:

  * Auf Basis von Polymorphismus und Rekursion lassen sich komplexe Baumstrukturen einheitlich behandeln.
  * Es ist ziemlich einfach, die Baumstruktur um neue Komponenten zu erweitern.

###### Kontras:

  * Jede neue Operation der Komponente muss auf dem Blattknoten und dem zusammengesetzten Knoten implementiert werden.

---


## FAQs

*Frage*: Unterschied zwischen *Decorator*- und *Composite*-Pattern?

  * Das *Decorator*-Pattern bewirkt eine Verfeinerung in der Ausgestaltung einer Schnittstelle.

  * Das *Composite*-Pattern zieht eine Vereinheitlichung von Schnittstellen f�r einzelne Objekte und Gruppen von Objekten nach sich.

---

## Literaturhinweise

*Hinweise*:

Anregungen zum Beispiel und zum C++17 Filesystem findet man zum Beispiel unter

[www.martinbroadhurst.com](http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html)<br>(abgerufen am 11.05.2020).

[www.codingame.com](https://www.codingame.com/playgrounds/5659/c17-filesystem)<br>(abgerufen am 11.05.2020).

[github.com/achimoraites/DesignPatterns](https://github.com/achimoraites/DesignPatterns/blob/master/CompositePattern/FileSystem/src/ui/FileSystem.java)<br>(abgerufen am 11.05.2020).

Das &bdquo;*Beginners Example*&rdquo;-Beispiel kann [hier](https://vishalchovatiya.com/posts//composite-design-pattern-in-modern-cpp/) im Original nachgelesen werden.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
