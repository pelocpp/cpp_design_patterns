# Composite Pattern

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Composite Entwurfsmuster* ist ein strukturelles Entwurfsmuster,
mit dem Sie Objekte zu Baumstrukturen zusammensetzen und dann mit diesen Strukturen arbeiten können,
als würde es sich um einzelne Objekte handeln.

#### Problem:

Der Einsatz des *Composite Entwurfsmuster* ist dann sinnvoll,
wenn sich die Kernstruktur der Daten einer Anwendung als baumartige Struktur darstellen lässt.

Stellen Sie sich beispielsweise vor, Sie haben zwei Arten von Objekten:
Produkte und Kartons. Ein Karton kann mehrere Produkte sowie mehrere kleinere Kartons enthalten.
Diese kleineren Kartons können wiederum Produkte oder sogar noch kleinere Kartons aufnehmen usw.

Betrachten wir nun ein Bestellsystem, das diese Klassen verwendet.
Bestellungen können einfache Produkte ohne Verpackung sowie mit Produkten gefüllte Kartons und andere Produkte enthalten.
Wie würden Sie den Gesamtpreis einer solchen Bestellung bestimmen?

Sie können den direkten Ansatz ausprobieren:
Packen Sie alle Kartons aus, gehen Sie alle Produkte durch und berechnen Sie dann die Gesamtsumme.
Das wäre in der realen Welt machbar.
In einem Programm ist es jedoch nicht so einfach wie das Ausführen einer Wiederholungsschleife.
Sie müssen die Klassen der Produkte und Schachteln, die Sie durchlaufen,
die Verschachtelungsebenen der Schachteln und andere unangenehme Details kennen.
All dies macht den direkten Ansatz entweder sehr umständlich oder sogar unmöglich.

#### Lösung:

Die zentrale Idee des *Composite Entwurfsmusters* ist es, mit einer gemeinsamen Schnittstelle sowohl
für Produkte als auch für Kartons zu arbeiten. Aufgabe dieser Schnittstelle wäre es an dem betrachteten Beispiel,
eine Methode zur Berechnung des Gesamtpreises zu deklarieren.

Wie könnte eine derartige Methode aussehen?
Für ein Produkt wird einfach der Produktpreis zurückgegeben.
Bei einer Schachtel wird jeder Artikel in der Schachtel überprüft, der Preis abgefragt und eine Gesamtsumme für die Schachtel zurückgegeben.

Wenn eines dieser Elemente eine kleinere Schachtel wäre, würde diese Schachtel auch ihren Inhalt durchgehen, solange, bis die Preise aller inneren Komponenten berechnet wurden.
Eine Schachtel kann sogar zusätzliche Kosten zum Endpreis hinzufügen, wie z.B. Verpackungskosten oder ähnliches.

Der große Vorteil dieses Ansatzes besteht darin, dass Sie sich nicht um die konkreten Objekte kümmern müssen (Produkt oder Karton),
aus denen der Baum besteht. Sie müssen nicht wissen, ob es sich bei einem Objekt um ein einfaches Produkt oder eine Schachtel mit Einzelteilen handelt.
Sie können die Objekte alle gleich über eine gemeinsame Schnittstelle behandeln.
Wenn Sie eine Methode aufrufen, übergeben die Objekte selbst die Anforderung an den Baum.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Composite Patterns*.
Es besteht im Wesentlichen aus drei Teilen:

  * **Component**: Stellt eine Abstraktion (abstrakte Klasse, Interface) für alle Komponenten dar (elementare und zusammengesetzte).
    Manchmal wird neben den eigentlichen Methoden der Komponente auch zusätzlich Methoden für den Zugriff
    auf das übergeordnete Element einer Komponente in der rekursiven Struktur definiert.
  * **Composite**: Kernstück des Entwurfsmusters. Es handelt sich gewissermaßen um eine *zusammengesetzte Komponente*.
    Das heißt, dass ein `Composite`-Objekt eine Liste für die Kind-Elemente verwaltet.
    Das Objekt stellt Methoden zum Hinzufügen und Entfernen von Kind-Elementen bereit.
    Zusätzlich werden die Methoden der `Component`-Klasse implementiert. Typischerweise werden deren
    Realisierung an die entsprechende Methode der Kind-Elemente delegiert.
  * **Leaf**: 
    Stellt ein "Blatt"-Objekt in der Komposition (Baumstruktur) dar. Es werden alle Methoden der `Component`-Klasse implementiert.

<img src="dp_composite_pattern.png" width="600">

Abbildung 1: Schematische Darstellung des *Composite Entwurfsmusters*.

#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/composite/cpp/example#example-0)

vor.

#### Beginners Example:

Ein typisches Beispiel für das *Composite Entwurfsmuster* ist ein Dateisystem mit Ordnern und Dateien:
Ordner können Dateien oder andere Ordner enthalten oder leer sein. Andererseits enthalten Dateien keine Ordner oder andere Dateien!

Um eine Analogie zur Abbildung 1 herzustellen, stellen wir die drei relevanten Header-Dateien kurz vor.
Die Schnittstelle für die Beschreibung der übergreifenden Komponente könnte so aussehen:

```cpp
class FileComponent {
public:
    virtual void display(const std::string&) const = 0;
};
```

Davon leiten wir nun zwei Klassen für Dateien (Klasse `File`) und Ordner (Klasse `Directory`) ab:

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

Ein Testrahmen zur Veranschaulichung der Funktionalität könnte so aussehen:

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
    * Funktionalität des *Composite Entwurfsmusters* erkennbar.

  * *Kontras*
    * Ein Raw-Pointer (hier: `std::vector<FileComponent*>`) sollte in Produktsoftware vermieden werden
    * Die Dateien und Ordner sind in dem Beispiel nur exemplarisch vorhanden

In einer zweiten Implementierung stellen wir eine Realisierung auf Basis des C++17 Filesystems und unter Verwendung
der Klasse `std::shared_ptr<FileComponent>` vor.

#### 'Real-World' Beispiel:

In den Beispielen zu diesem Entwurfsmuster (siehe Klasse `DirectoryEx` und Datei `FileSystemAdvanced.cpp`)
können Sie die Umsetzung des *Composite Entwurfsmusters* am realen Dateisystem betrachten.

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

## Literaturhinweise

*Hinweise*:

Anregungen zum Beispiel und zum C++17 Filesystem findet man zum Beispiel unter

[www.martinbroadhurst.com](http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html)<br>(abgerufen am 11.05.2020).

[www.codingame.com](https://www.codingame.com/playgrounds/5659/c17-filesystem)<br>(abgerufen am 11.05.2020).

[github.com/achimoraites/DesignPatterns](https://github.com/achimoraites/DesignPatterns/blob/master/CompositePattern/FileSystem/src/ui/FileSystem.java)<br>(abgerufen am 11.05.2020).


## Weitere Beispiele

Ein weiterer Anwendungsfall für das *Composite Entwurfsmuster* sind arithmetische Ausdrücke.
Anregungen finden sich zum Beispiel unter

[https://stackoverflow.com/questions](https://stackoverflow.com/questions/57942934/composite-design-pattern-how-to-create-calculator)<br>(abgerufen am 11.05.2020).

---

[Zurück](../../Readme_05_Catalog.md)

---
