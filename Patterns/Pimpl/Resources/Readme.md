# Opaque Pointer /  Pimpl Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

##### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Was versteht man unter einem *Opaque Pointer*? Opaque, zu Deutsch *undurchsichtig*, impliziert,
das wir es mit etwas zu tun haben, durch das wir nicht durchschauen k�nnen.
Ein *Opaque Pointer* (zu Deutsch gewisserma�en ein "undurchsichtiger Zeiger") ist ein Zeiger,
der auf eine Datenstruktur (Objekt) verweist, deren Inhalt zum Zeitpunkt seiner Definition nicht verf�gbar ist.

#### Hinweis:

Das *Opaque Pointer* Pattern ist auch unter den Begriffen *d-pointer*, *compiler firewall*
oder auch *Cheshire Cat Pattern* oder *Pimpl* ("*Pointer to implementation*") bekannt.

#### Problem:

*Opaque Pointer* sind eine M�glichkeit, die Implementierungsdetails einer Schnittstelle vor Benutzern zu verbergen.

Auf diese Weise kann die Implementierung ge�ndert werden,
ohne dass die C++-Module, die sie verwenden, neu kompiliert werden m�ssen.

Dies kommt auch dem Programmierer zugute, da eine einfache Schnittstelle erstellt werden kann
und die meisten Details in einer anderen Datei versteckt sind.

Dies ist wichtig, um beispielsweise die Bin�rcode-Kompatibilit�t (*ABI*, *Application Binary Interface*)
mit verschiedenen Versionen einer *Shared*-Bibliothek zu gew�hrleisten.

#### L�sung:

In seiner Grundform sieht das Muster wie folgt aus:

  * Ausgangspunkt ist eine Klasse (Hauptklasse), die eine zweite Klasse (Hilfsklasse) benutzt und damit in Abh�ngigkeit zu dieser Klasse steht.
    Alle �nderungen an der unterlagerten Klasse w�rden eine Neu�bersetzung beider Klassen nach sich ziehen.
  * In der Hauptklasse verschieben wir alle privaten Member (vor allem die der Hilfsklasse)
    in einen neu deklarierten Typ - z.B. Klasse `PrivateImpl`.
  * Zu diesem neu deklarierten Typ gibt es in der Header-Datei der Hauptklasse nur eine Forward-Deklaration.
  * Die `PrivateImpl`-Klasse wird in gewohnter Manier in einer *cpp*- und *h*-Datei deklariert und implementiert.
  * Der Client-Code der Hauptklasse muss nun nicht neu kompiliert werden, wenn sich �nderungen an der **Implementierung** der privaten Hilfsklasse `PrivateImpl` ergeben
    (da sich die Schnittstelle nicht ge�ndert hat). Im Headerfile der Hauptklasse ist die benutzte Hilfsklasse nur �ber eine Vorw�rtsdeklaration bekannt.
  * Im Umkehrschluss bedeutet dies nat�rlich, dass �nderungen an der Schnittstelle tabu sind.


## Pro / Kontra:

###### Pros:

  * Stellt eine so genannte "*Compilation Firewall*" dar:
    Wenn sich die private Implementierung �ndert, muss der Clientcode nicht neu kompiliert werden.
    Alles in allem f�hrt dies zu besseren �bersetzungszeiten.
  * Bietet so genannte "*Application Binary Compatibility*": f�r Bibliotheksentwickler von Interesse.
    Solange die Bin�rschnittstelle gleich bleibt, kann man die Anwendung mit einer anderen Version der Bibliothek verkn�pfen.

###### Kontras:

  * Performance - Eine Indirektionsebene wird hinzugef�gt.
  * Komplexer Code - Es erfordert etwas Disziplin, um solche Klassen zu pflegen.
  * Debugging - Da die Klasse aufgeteilt ist, erkennt man Details bei der Fehlersuche nicht sofort.

---

#### Ein Beispiel:

[Quellcode *Car.h*](../Car/Car.h)<br />
[Quellcode *Car.cpp*](../Car/Car.cpp)<br />
[Quellcode *Engine.h*](../Car/Engine.h)<br />
[Quellcode *CarClient.cpp*](../Car/CarClient.cpp)

##### Grundlagen:

Wir betrachten ein Auto (Klasse `Car`), das logischerweise einen Motor besitzt (Klasse `Engine`).
Die Klasse `Car` k�nnte folgendes Header-File besitzen:

```cpp
// File "Car.h"

#include "engine.h"
 
class Car
{
public:
   void coolDown();

private:
   Engine m_engine;
};
```

Die Implementierung der Klasse  `Engine` soll hier nicht weiter betrachtet werden.
Die Implementierungs-Datei der Klasse `Car` sieht so aus:

```cpp
// File "Car.cpp"

#include "car.h"
 
void Car::coolDown()
{
   /* ... */
}
```

Betrachten Sie das Problem, das - in Abh�ngigkeit von der Anzahl der Benutzer der Klasse `Car` -
weniger oder mehr in Erscheinung treten kann: Da die Datei `car.h` die Datei `engine.h` inkludiert,
besitzen alle Benutzer der Datei `Car.h` eine indirekte Abh�ngigkeit zur Datei `engine.h`.
Sprich alle Benutzer von `car.h` inkludieren `engine.h`.
Dies bedeutet, dass bei �nderungen an der Klasse `Engine` alle Benutzer von `car.h` neu �bersetzt werden m�ssen,
eben auch f�r den Fall, dass an der Klasse `Car` �berhaupt nichts ge�ndert wurde. Und zum Zweiten vor dem Hintergrund,
dass diese Clients sich m�glicherweise der Abh�ngigkeit zur Klasse `Engine` gar nicht bewusst sind.

Das *Piml*-Idiom (*Pointer to Implementation*) l�st diese Abh�ngigkeit durch das Hinzuf�gen
einer Indirektionsstufe in Gestalt einer zus�tzlichen Klasse - nennen wir sie `CarImpl` - auf.
Aufgabe der Klasse `CarImpl` ist es, die Pr�senz der Klasse `Engine` zu verdecken.

Ein Header-File f�r die Klasse `Car` k�nnte nun so aussehen:

```cpp
// File "Car.h"

class Car
{
public:
   Car();
   ~Car();
 
   void coolDown();

private:
   class CarImpl;
   CarImpl* m_impl;
};
```
 
Beachten Sie an diesem Header-File, das die Include-Anweisung `#include "engine.h"` nicht mehr
vorhanden ist.

Eine m�gliche Implementierung der Klassen `CarImpl` und `Car` in der Datei *Car.cpp* k�nnte nun so aussehen:

```cpp
// file "Car.cpp"

#include "Engine.h"
#include "Car.h"
 
class Car::CarImpl
{
public:
   void coolDown()
   {
      /* ... */
   }
private:
   Engine m_engine;
};
 
Car::Car() : m_impl(new CarImpl) {}
 
Car::~Car()
{
   delete m_impl;
}
 
void Car::coolDown()
{
   m_impl->coolDown();
}
```

Die Klasse `Car` delegiert ihre Aufrufe an die Klasse `Engine` nun an die Klasse `CarImpl`,
nat�rlich in der Erwartung, dass diese den Aufruf an eine Instanz von `Engine` weiterreicht.
Allerdings ist f�r die Klasse `Car` eine neue Verantwortlichkeit entstanden:
Die Verwaltung der Lebenszeit des `CarImpl`-Zeigers.

*Beachte*: Haben Sie eine Erkl�rung daf�r, warum Benutzer der Klasse `Car`, also des Header-Files `car.h`, �bersetzungsf�hig sind,
obwohl von der referenzierten Klasse `CarImpl` nur eine Vorw�rts-Deklaration vorliegt, also die tats�chliche Klassendefinition fehlt?

Die Klasse `Car` besitzt von der Klasse `CarImpl` nur einen Zeiger (sagen wir: dieser belegt 4 Bytes, sprich seine Gr��e ist dem Compiler bekannt) und kein Objekt.
Bei diesem Sachverhalt kann der Compiler Code generieren, er muss das tats�chliche Aussehen der Klasse `CarImpl` nicht kennen!

##### Verbesserungen:

Der Einsatz eines *raw-Pointers* in der Klasse `Car` entspricht nicht dem Aussehen eines *Modern C++* Designs.
Aus diesem Grund tauschen wir diesen Zeiger mit einem Smart-Pointer, beispielsweise einem `std::unique_ptr`-Objekt, aus.
Die Header-Datei der Klasse `Car` sieht nun so aus:

```cpp
// file "Car.h"

#include <memory>
 
class Car
{
public:
   Car();
   void coolDown();
private:
   class CarImpl;
   std::unique_ptr<CarImpl> m_impl;
};
```

Die Implementierungsdatei �ndert sich nur marginal:

```cpp
// file "Car.cpp"

#include "Engine.h"
#include "Car.h"
 
class CarImpl
{
public:
   void coolDown()
   {
      /* ... */
   }
private:
   Engine m_engine;
};
 
Car::Car() : m_impl(new CarImpl) {}
```

Es sieht so weit alles gut aus - �berraschenderweise erhalten wir in diesem Zustand des Programms
einen �bersetzungsfehler:

<b>
use of undefined type 'Car::EngineImpl'</br>
can't delete an incomplete type
</b></b>

In C ++ gibt es eine Regel, die besagt, dass das L�schen eines Zeigers zu undefiniertem Verhalten f�hrt,
wenn:

  * Dieser Zeiger hat den Typ `void*` oder
  * Der Typ, auf den verwiesen wird, ist unvollst�ndig, d.h. er wird nur vorw�rts deklariert,
    wie `CarImpl` in unserer Header-Datei.

Der �bersetzungsfehler liegt als darin begr�ndet, dass der korrespondierende Typ nur vorw�rts deklariert ist.

Es sind zwei �nderungen am aktuellen Programm vorzunehmen:

  * Hinzuf�gen einer Destruktor-Deklaration in der Klasse `Car`:<br/>
    `~Car();`

  * Hinzuf�gen einer Destruktor-Definition in der Klasse `CarImpl`:<br/>
    `Car::~Car() {};`


##### *Hinweis*:

Prinzipiell gibt es 2 M�glichkeiten, um diese Fehlermeldung zu beseitigen:

  * Bereitstellung eines benutzerdefinierten Destruktors f�r die Ausgangsklasse,
    der explizit implementiert ist (dazu z�hlt auch eine Implementierung mit `default`).
    Diese Definition muss im Quellcode nach der vollst�ndigen Definition der *Pimpl*-Klasse stehen.
  * Bereitstellung eines benutzerdefinierten Deleters f�r das `std::unique_ptr<>`-Objekt.


##### *Weiterer Hinweis*:

Die Fehlermeldung *use of undefined type* tritt nur dann auf, wenn die betrachtete Klasse (mit *Pimpl*-Zeiger)
und der Anwender der Klasse in verschiedenen Dateien residieren!

Damit haben einen ersten minimalistischen Durchlauf durch das *Pimpl*-Idiom beschritten!

---

#### Ein zweiter Beispiel:

[Quellcode *User.h*](../User/User.h)<br />
[Quellcode *User.cpp*](../User/User.cpp)<br />
[Quellcode *UserClient.cpp*](../User/UserClient.cpp)

---

#### Struktur (UML):

<img src="dp_pimple_idiom.svg" width="700">

*Abbildung* 1: Struktur des Pimpl-Idioms.

## Pimpl @ Microsoft

Auf der offiziellen WebSite von Microsoft gibt es zu Pimpl auch eine kleine Verfahrensanweisung,
wenn gleich sehr knapp gehalten:

[Pimpl For Compile-Time Encapsulation (Modern C++)](https://docs.microsoft.com/en-us/cpp/cpp/pimpl-for-compile-time-encapsulation-modern-cpp?view=vs-2019) (Abruf: 16.07.2020)

---

## Weiterarbeit:

Stellen Sie einen Vergleich *Pimpl-Idiom* versus *Interface Inheritance* an.

---

## Literaturhinweise

Weitere intessante Artikel und Aufs�tze zum *Pimpl-Idiom* finden Sie unter

[The Pimpl Pattern - what you should know](https://www.bfilipek.com/2018/01/pimpl.html) (Abruf: 16.07.2020)

[PImpl Idiom in C++ with Examples](https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/) (Abruf: 16.07.2020)

[In-depth: PIMPL vs pure virtual interfaces](https://www.gamasutra.com/view/news/167098/Indepth_PIMPL_vs_pure_virtual_interfaces.php) (Abruf: 16.07.2020)

[Pimpl idiom versus Pure virtual class interface](https://stackoverflow.com/questions/825018/pimpl-idiom-vs-pure-virtual-class-interface) (Abruf: 16.07.2020)

[Pimp My Pimpl - Reloaded](https://marcmutz.wordpress.com/translated-articles/pimp-my-pimpl-reloaded/) (Abruf: 16.07.2020)

[How to implement the pimpl idiom by using unique_ptr](https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/) (Abruf: 16.07.2020)

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
