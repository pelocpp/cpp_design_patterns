# Adapter Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_adapter_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

#### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Erm�glicht die Interaktion von Objekten mit inkompatiblen Schnittstellen.&rdquo;

Das *Adapter Pattern* ist ein strukturelles Entwurfsmuster, das es Objekten mit
inkompatiblen Schnittstellen erm�glicht, zusammenarbeiten zu k�nnen.

Ist eine Klasse auf eine bestimmte Schnittstelle angewiesen,
die von einer anderen Klasse nicht implementiert wird,
fungiert der Adapter als �bersetzer zwischen diesen beiden Klassen.

#### Problem:

Das Adapter Entwurfsmuster ist ein strukturelles Muster, das eine Vorgehensweise
zum Erstellen von Beziehungen zwischen Objekten definiert.
Das Muster &bdquo;�bersetzt&rdquo; eine Schnittstelle f�r eine Klasse in eine andere kompatible Schnittstelle.

Es gelangt zum Einsatz, wenn Anforderungen ge�ndert werden
und Funktionen von Klassen zu implementieren sind,
deren Schnittstellen nicht mit den eigenen kompatibel sind.

#### L�sung:

Das Pattern steht im Prinzip f�r eine einzige Klasse (Adapterklasse),
deren Aufgabe die Verkn�pfung von Funktionen / das Weiterreichen unabh�ngiger oder inkompatibler Schnittstellen ist.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Adapter Patterns*.
Es besteht im Wesentlichen aus vier Teilen:

  * **Client**: Stellt die Klasse dar, die eine inkompatible Schnittstelle verwenden muss.
    Diese inkompatible Schnittstelle wird von der Klasse `Adaptee` implementiert.
  * **ITarget**: Definiert die Schnittstelle, die der Client kennt und verwendet.
  * **Adaptee**: Stellt eine Klasse dar, die eine vom Client ben�tigte Funktionalit�t bietet. Typischerweise unterst�tzt die `Adaptee`-Klasse die `ITarget`-Schnittstelle nicht.
  * **Adapter**: Konkrete Implementierung des Adapters. Diese Klasse �bersetzt die inkompatible Schnittstelle von `Adaptee` in die Schnittstelle, die der Client verwendet.

<img src="dp_adapter_01.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Adapter Patterns*.

Der Klassenname `Adaptee` steht stellvertretend f�r Service-Klassen, die es gilt,
�ber Adapter-Klassen verf�gbar zu machen.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### Beispiele zum Adapter Pattern in der STL:

Die STL Container `std::stack`, `std::queue` und `std::priority_queue` bieten eine andere Schnittstelle
f�r STL Sequenzcontainer an. Aus diesem Grund spricht man bei diesen drei Klassen auch von so genannten
*Container Adaptern*.

Das folgende Code-Snippet zeigt die Template-Signatur der drei Container-Adapter:

```cpp
template<typename T, typename Container = std::deque<T>> 
class stack;

template<typename T, typename Container = std::deque<T>> 
class queue;

template<
    typename T,
    typename Container = std::vector<T>, 
    typename Compare = std::less<typename Container::value_type>
> 
class priority_queue;
```

Man kann erkennen, das `std::stack` und `std::queue` standardm��ig den Container `std::deque`
als Sequenzcontainer verwenden, hingegen wird `std::vector` von `std::priority_queue` verwendet.

Dar�ber hinaus erfordert `std::priority_queue` auch ein Vergleichsobjekt,
das standardm��ig auf `std::less` voreingestellt ist.

---

#### Weitere Beispiele zum Adapter Pattern in der STL:

Neben den *Container Adaptern* in der STL gibt es auch *Iteratoren Adapter*,
beispielsweise die &bdquo;Einf�ge Iteratoren&rdquo;:

  * `std::front_inserter`
  * `std::back_inserter`
  * `std::inserter`

Mit diesen *Iteratoren Adaptern* lassen sich Elemente am Anfang, am Ende oder an einer beliebigen Stelle
in einen Container einf�gen.

---


**Hinweis**: Prinzipiell gibt es f�r das Adapter Pattern zwei Vorgehensweisen in der Umsetzung mit einer realen Programmiersprache:

  * **Objekt Adapter Ansatz**:
    Diese Implementierung verwendet das Prinzip der *Komposition* von Objekten:
    Der Adapter implementiert die Schnittstelle eines Objekts, die f�r den Client relevant sind.
    Die anderen Objekte werden &bdquo;umh�llt&rdquo;, deren Funktionalit�t ist �ber die eine bekannte Schnittstelle nach au�en zu transportieren.
    Der Zugriff auf die - schnittstellentechnisch gesehen - inkompatiblen Funktion dieser Objekte ist die eigentliche Dienstleistung des Adapter-Objekts.
    Dieser Ansatz kann in allen g�ngigen Programmiersprachen implementiert werden (&bdquo;*has-a*&rdquo; Relationship / &bdquo;*hat-ein*&rdquo; Beziehung).

  * **Klassen Adapter Ansatz**:
    Diese Implementierung verwendet die Vererbung: Der Adapter erbt Schnittstellen von allen Objekten gleichzeitig
   (vorhandenes Objekt, neue Service-Objekte mit inkompatiblen Service-Funktionen).
    Beachten Sie, dass dieser Ansatz nur in Programmiersprachen implementiert werden kann,
    die Mehrfachvererbung unterst�tzen, z.B. C++.
    Wie beim *Objekt Adapter Ansatz* besteht auch hier die eigentliche Aufgabe der Adapter Klasse darin,
    die geerbten Funktionalit�ten �ber die vorhandene Schnittstelle verf�gbar zu machen.


*Abbildung* 1 gibt das Entwurfsmuster mit dem *Objekt Adapter* Ansatz wieder. In *Abbildung* 2 finden Sie
das Muster auf Basis des *Klassen Adapter* Ansatzes vor:

<img src="dp_adapter_02.svg" width="700">

*Abbildung* 2: Schematische Darstellung des *Adapter Patterns* (*Klassen Adapter Ansatzes*).

Im &bdquo;Real-World&rdquo; Beispiel zu diesem Entwurfsmuster finden Sie beide Varianten umgesetzt vor.

---

#### Abgrenzung zu anderen Entwurfsmustern:

  * Das *Adapter Pattern* implementiert als Objektadapter �hnelt dem *Bridge Pattern*,
  hat jedoch eine andere Absicht.
  Der Zweck des *Bridge Patterns* besteht darin, die Schnittstelle von der Implementierung zu trennen.
  Der Zweck des *Adapter Patterns* besteht darin, eine vorhandene Schnittstelle zu modifizieren.

  * Das *Decorator Pattern* erweitert ein Objekt, ohne seine Schnittstelle zu �ndern.
  Decoratoren-Objekte sind in diesem Sinne *pluggable*, im Gegensatz zum *Bridge-* oder *Adapter Pattern*.

  * Das *Proxy Pattern* erweitert die Implementierung f�r das Objekt, f�r das es steht,
  �ndert jedoch nicht seine Schnittstelle.

---

#### Pluggable Adapter Design Pattern mit Modern C++:

Unter 
[Adapter Design Pattern in Modern C++ (Vishal Chovatiya)](https://vishalchovatiya.com/posts//adapter-design-pattern-in-modern-cpp/)
findet sich eine Umsetzung des Adapter Patterns mit Modern C++ Sprachmitteln vor.

Der Adapter unterst�tzt hier die Adaptees (die nicht verwandt sind und unterschiedliche Schnittstellen haben)
unter Verwendung derselben &bdquo;Zielschnittstelle&rdquo;, die dem Client/API-Benutzer bekannt ist.

Das Beispiel erf�llt diese Eigenschaft, indem es die Lambda-Funktionen und das Klassentemplate `std::function<>`
von C++ 11 verwendet.

*Hinweise zum Quellcode*:

  * Der *Pluggable Adapter* besitzt ab einem bestimmten Zeitpunkt eine Verbindung zu einem Zielobjekt.
  Sobald das Zielobjekt vorhanden ist und seine Methode(n) an ein *Callable*-Objekt
  (in unserem Beispiel: `m_request`) zugewiesen wurden, bleibt die Zuordnung bestehen,
  bis ein anderer Satz von Methode(n) zugewiesen wird.

  * Der *Pluggable Adapter* zeichnet sich dadurch aus, dass er �ber Konstruktoren f�r jeden Typ verf�gt,
  f�r den er die Stellvertreterrolle �bernimmt.

---

#### &bdquo;Real-World&rdquo; Beispiel:

Wir demonstrieren den Einsatz des Adapter Patterns anhand des folgenden Beispiels,
in dem wir ein Audio-Player-Ger�t betrachten, das nur *MP3*-Dateien abspielen kann,
aber erweitert werden soll, um *VLC*- und *MP4*-Dateien abspielen zu k�nnen.

Ausgangspunkt ist eine Schnittstelle `IMediaPlayer` und eine konkrete Klasse `AudioPlayer`,
die die `IMediaPlayer`-Schnittstelle implementiert.
`AudioPlayer` Objekte spielen nur Audiodateien im MP3-Format ab.
Bei anderen Formaten reagiert das `AudioPlayer`-Objekt mit einer Fehlermeldung.

Wir haben ferner zwei zus�tzliche Schnittstellen `IVlcMediaPlayer` und `IMp4MediaPlayer` sowie konkrete Klassen zur Verf�gung,
die die beiden Schnittstellen implementieren.
Diese Klassen k�nnen Dateien im *VLC*- und *MP4*-Format abspielen.

Wir wollen nun erreichen, dass die `AudioPlayer` Klasse auch die Formate *VLC* und *MP4* wiedergibt.
Um dies zu erreichen, erstellen wir eine Adapterklasse `MediaAdapter`.
Diese Klasse `MediaAdapter` implementiert einerseits die `IMediaPlayer`-Schnittstelle,
um damit die Kompatibilit�t zu dieser Schnittstelle aufrecht zu erhalten. 
Zum Anderen benutzt sie (*hat-sie*) zwei Instanzen der Klassen `VlcPlayer` und `Mp4Player`,
um auch die weiteren Formate *VLC* und *MP4* abspielen zu k�nnen.

Ein Redesign der Klasse `AudioPlayer` (im beiliegenden Quellcode hat sie den Namen `AudioPlayerExtended`)
verwendet nun die Adapterklasse `MediaAdapter`.
Die Klasse `AudioPlayer` kennt nach wie vor nicht die tats�chlichen Klassen, die das gew�nschte Format wiedergeben k�nnen.
Sie reicht allerdings bei Benutzung der Klasse `AudioPlayer` und bei Anforderung entsprechender Audiotypen
diese an die Adapterklasse weiter, so dass die Anforderung doch unterst�tzt werden kann.

*Hinweis*: Der Client-Code wird bei Einhaltung des Patterns nicht an die konkrete Adapterklasse gekoppelt,
sondern er darf nur �ber die vorhandene Client-Schnittstelle mit dem Adapter zusammenarbeiten
(im vorliegenden Beispiel: Schnittstelle `IMediaPlayer`). Auf diese Weise lassen sich neue Adapterklassen
in das Programm einf�hren, ohne inkompatibel zum vorhandenen Client-Code zu sein!

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/adapter/cpp/example#example-0)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
