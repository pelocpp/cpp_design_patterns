# Adapter Pattern

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Adapter Pattern* ist ein strukturelles Entwurfsmuster, das es Objekten mit
inkompatiblen Schnittstellen ermöglicht, zusammenarbeiten zu können.

#### Problem:

Wir demonstrieren den Einsatz des Adapter Patterns anhand des folgenden Beispiels,
in dem ein Audio-Player-Gerät nur MP3-Dateien abspielen kann und einen erweiterten Audio-Player verwenden möchte,
der VLC- und MP4-Dateien abspielen kann.

Wir haben eine Schnittstelle `MediaPlayer` und eine konkrete Klasse `AudioPlayer`,
die die `MediaPlayer`-Schnittstelle implementiert.
`AudioPlayer` Objekte spielen standardmäßig Audiodateien im MP3-Format ab.

Wir haben eine weitere Schnittstelle `AdvancedMediaPlayer` und konkrete Klassen,
die die `AdvancedMediaPlayer`-Schnittstelle implementieren.
Diese Klassen können Dateien im VLC- und MP4-Format abspielen.

Wir wollen nun erreichen, dass die `AudioPlayer` Klasse auch andere Formate wiedergibt.
Um dies zu erreichen, erstellen wir eine Adapterklasse `MediaAdapter`.
Diese Klasse `MediaAdapter` implementiert zum Einen die `MediaPlayer`-Schnittstelle 
und benutzt eine Instanz der Klasse `AdvancedMediaPlayer`,
um das gewünschte Format abzuspielen.

Die Klasse `AudioPlayer` verwendet die Adapterklasse `MediaAdapter`,
ohne dabei die tatsächliche Klasse zu kennen, die das gewünschte Format wiedergeben kann.
Bei Benutzung der Klasse `AudioPlayer` reicht diese den gewünschten Audiotyp nur an die Adapterklasse weiter.

*Hinweis*: Der Clientcode wird bei Einhaltung des Patterns nicht an die konkrete Adapterklasse gekoppelt,
sondern er darf nur über die vorhandene Clientschnittstelle mit dem Adapter zusammenarbeiten
(im vorliegenden Beispiel: Schnittstelle `MediaPlayer`).

Auf diese Weise lassen sich neue Adapterklassen in das Programm einführen,
ohne imkompatibel zum vorhandenen Client-Code zu sein!

#### Lösung:

Das Pattern steht für eine einzelne Klasse, deren Funktionalität die Verknüpfung von Funktionen
unabhängiger oder inkompatibler Schnittstellen ist.


#### Struktur (UML):

<img src="dp_adapter.png" width="500">

Abbildung 1: Schematische Darstellung des *Adapter Pattern*.

#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/adapter/cpp/example#example-0)

vor.

#### Beginners Example:

Ein typisches Beispiel für das *Composite Entwurfsmuster* ist ein Dateisystem mit Ordnern und Dateien:
Ordner können Dateien oder andere Ordner enthalten oder leer sein. Andererseits enthalten Dateien keine Ordner oder andere Dateien!

Um eine Analogie zur Abbildung 1 herzustellen, stellen wir dir drei relevanten Header-Dateien kurz vor`.
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

[Zurück](../../Readme.md)

---
