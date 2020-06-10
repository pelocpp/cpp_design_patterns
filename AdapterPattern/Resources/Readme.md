# Adapter Pattern

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Das *Adapter Pattern* ist ein strukturelles Entwurfsmuster, das es Objekten mit
inkompatiblen Schnittstellen ermöglicht, zusammenarbeiten zu können.

#### Problem:

Wir demonstrieren den Einsatz des Adapter Patterns anhand des folgenden Beispiels,
in dem ein Audio-Player-Gerät nur MP3-Dateien abspielen kann, aber einen erweiterten Audio-Player verwenden möchte,
der VLC- und MP4-Dateien abspielen kann.

Ausgangspunkt ist eine Schnittstelle `MediaPlayer` und eine konkrete Klasse `AudioPlayer`,
die die `MediaPlayer`-Schnittstelle implementiert.
`AudioPlayer` Objekte spielen standardmäßig nur Audiodateien im MP3-Format ab.

Wir haben ferner zur Verfügung eine zusätzliche Schnittstelle `AdvancedMediaPlayer` und konkrete Klassen,
die die `AdvancedMediaPlayer`-Schnittstelle implementieren.
Diese Klassen können Dateien im VLC- und MP4-Format abspielen.

Wir wollen nun erreichen, dass die `AudioPlayer` Klasse auch die Formate VLC und MP4 wiedergibt.
Um dies zu erreichen, erstellen wir eine Adapterklasse `MediaAdapter`.
Diese Klasse `MediaAdapter` implementiert einerseits die `MediaPlayer`-Schnittstelle,
und damit die Kompatibilität zu dieser Schnittstelle aufrecht zu erhalten. 
Zum Anderen benutzt sie (*hat-sie*) eine Instanz der Klasse `AdvancedMediaPlayer`,
um auch dies weiteren Formate VLC und MP4 abspielen zu können.

Ein Redesign der Klasse `AudioPlayer` verwendet nun die Adapterklasse `MediaAdapter`.
Die Klasse `AudioPlayer` kennt dabei nicht die tatsächlichen Klasse, die das gewünschte Format wiedergeben können.
Sie reicht allerdings bei Anforderung entsprechender Audiotypen bei Benutzung der Klasse `AudioPlayer`
diese an die Adapterklasse weiter, so dass die Anforderung ebenfalls unterstützt werden kann.

*Hinweis*: Der Clientcode wird bei Einhaltung des Patterns nicht an die konkrete Adapterklasse gekoppelt,
sondern er darf nur über die vorhandene Clientschnittstelle mit dem Adapter zusammenarbeiten
(im vorliegenden Beispiel: Schnittstelle `MediaPlayer`). Auf diese Weise lassen sich neue Adapterklassen
in das Programm einführen, ohne imkompatibel zum vorhandenen Client-Code zu sein!

#### Lösung:

Das Pattern steht im Prinzip für eine einzige Klasse (Adapterklasse),
deren Aufgabe die Verknüpfung von Funktionen / das Weiterreichen unabhängiger oder inkompatibler Schnittstellen ist.


#### Struktur (UML):

<img src="dp_adapter.png" width="500">

Abbildung 1: Schematische Darstellung des *Adapter Pattern*.

#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/adapter/cpp/example#example-0)

vor.

#### Beginners Example:

Das oben zitierte Beispiel eines MediaPlayers finden Sie im Quellcode exemplarisch umgesetzt vor.

## Literaturhinweise

*Hinweise*:

## Weitere Beispiele

---

[Zurück](../../Readme.md)

---
