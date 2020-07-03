# Opaque Pointer /  Pimpl Pattern

## Wesentliche Merkmale

##### Kategorie: *Structural Pattern*

#### Ziel / Absicht:

Was versteht man unter einem *Opaque Pointer*? Opaque, zu Deutsch *undurchsichtig*, soll implizieren,
das wir es mit etwas zu tun haben, durch das wir nicht durchschauen können.
Ein *Opaque Pointer* (zu Deutsch gewissermaßen ein "undurchsichtiger Zeiger") ist ein Zeiger,
der auf eine Datenstruktur (Objekt) verweist, deren Inhalt zum Zeitpunkt seiner Definition nicht verfügbar ist.

##### Hinweis:

Das *Opaque Pointer* Pattern ist auch unter den Begriffen *d-pointer*, *compiler firewall*
oder auch *Cheshire Cat Pattern* oder *Pimpl* ("*Pointer to implementation*") bekannt.

#### Problem:

*Opaque Pointer* sind eine Möglichkeit, die Implementierungsdetails einer Schnittstelle vor Benutzern zu verbergen.

Auf diese Weise kann die Implementierung geändert werden,
ohne dass die C++-Module, die sie verwenden, neu kompiliert werden müssen.

Dies kommt auch dem Programmierer zugute, da eine einfache Schnittstelle erstellt werden kann
und die meisten Details in einer anderen Datei versteckt sind.

Dies ist wichtig, um beispielsweise die Binärcode-Kompatibilität mit verschiedenen Versionen
einer *Shared*-Bibliothek zu gewährleisten.

#### Lösung:

In seiner Grundform sieht das Muster wie folgt aus:

  * In einer Klasse verschieben wir alle privaten Member in einen neu deklarierten Typ - z.B. eine Klasse `PrivateImpl`.
  * Zu diesem neu deklarierten Typ gibt es in der Header-Datei der Hauptklasse nur eine Forward-Deklaration.
  * Die `PrivateImpl`-Klasse wird in gewohnter Manier in einer *cpp*- und *h*-Datei deklariert und implementiert.
  * Der Client-Code der Hauptklasse muss nun nicht neu kompiliert werden, wenn sich Änderungen an der Implementierung der privaten Hilfsklasse `PrivateImpl` ergeben (da sich die Schnittstelle nicht geändert hat).
  * Im Umkehrschluss bedeutet dies natürlich, dass Änderungen an der Schnittstelle tabu sind.


#### Pro / Kontra:

###### Pros:

  * Stellt eine so genannte "*Compilation Firewall*" dar:
    Wenn sich die private Implementierung ändert, muss der Clientcode nicht neu kompiliert werden.
    Alles in allem führt dies zu besseren Übersetzungszeiten.
  * Bietet so genannte "*Binary Compatibility*": für Bibliotheksentwickler von Interesse.
    Solange die Binärschnittstelle gleich bleibt, kann man die Anwendung mit einer anderen Version der Bibliothek verknüpfen.

###### Kontras:

  * Performance - Eine Indirektionsebene wird hinzugefügt.
  * Komplexer Code - Es erfordert etwas Disziplin, um solche Klassen zu pflegen.
  * Debugging - Da die Klasse aufgeteilt ist, erkennt man Details bei der Fehlersuche nicht sofort.


#### Ein Beispiel:

###### Grundlagen:

Wir betrachten ein Auto (Klasse `Car`), das logischerweise einen Motor besitzt (Klasse `Engine`).
Die Klasse `Car` könnte folgendes Header-File besitzen:

```cpp
#include "engine.h"
 
class Car
{
public:
   void coolDown();
private:
   Engine engine_;
};
```

Die Implementierung der Klasse  `Engine` soll hier nicht weiter betrachtet werden.
Die Implementierungs-Datei der Klasse `Car` sieht so aus:

```cpp
#include "car.h"
 
void Car::coolDown()
{
   /* ... */
}
```

Betrachten Sie das Problem, das - in Abhängigkeit von der Anzahl der Benutzer der Klasse `Car` -
weniger oder mehr in Erscheinung treten kann: Da die Datei `car.h` die Datei `engine.h` inkludiert,
besitzen alle Benutzer der Datei `Car.h` eine indirekte Abhängigkeit zur Datei `engine.h`.
Sprich alle Benutzer von `car.h` inkludieren `engine.h`.
Dies bedeutet, dass bei Änderungen an der Klasse `Engine` alle Benutzer von `car.h` neu übersetzt werden müssen,
eben auch für den Fall, dass an der Klasse `Car` nichts geändert wurde. Und zum Zweiten vor dem Hintergrund,
dass diese Clients sich möglicherweise der Abhängigkeit zur Klasse `Engine` gar nicht bewusst sind.

Das *Piml*-Idiom (*Pointer to Implementation*) löst diese Abhängigkeit durch das Hinzufügen
einer Indirektionsstufe in Gestalt einer zusätzlichen Klasse - nennen wir sie `CarImpl` - auf.
Aufgabe der Klasse `CarImpl` ist es, die Präsenz der Klasse `Engine` zu verdecken.

Ein Header-File für die Klasse `Car` könnte nun so aussehen:

```cpp
class Car
{
public:
   Car();
   ~Car();
 
   void coolDown();
private:
   class CarImpl;
   CarImpl* impl_;
};
```
 
Beachten Sie an diesem Header-File, das die Include-Anweisung `#include "engine.h"` nicht mehr
vorhanden ist.

Eine mögliche Implementierung der Klassen `CarImpl` und `Car` könnte nun so aussehen:

```cpp
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
   Engine engine_;
};
 
Car::Car() : impl_(new CarImpl) {}
 
Car::~Car()
{
   delete impl_;
}
 
void Car::coolDown()
{
   impl_->coolDown();
}
```

Die Klasse `Car` delegiert ihre Aufrufe an die Klasse `Engine` nun an die Klasse `CarImpl`,
natürlich in der Erwartung, dass diese den Aufruf an eine Instanz von `Engine` weiterreicht.
Allerdings ist für die Klasse `Car` eine neue Verantwortlichkeit entstanden:
Die Verwaltung der Lebenszeit des `CarImpl`-Zeigers.

*Beachte*: Haben Sie eine Erklärung dafür, warum Benutzer der Klasse `Car`, also des Header-Files `car.h`, übersetzungsfähig sind,
obwohl von der referenzierten Klasse `CarImpl` nur eine Vorwärts-Deklaration vorliegt, also die tatsächliche Klassendefinition fehlt?

Die Klasse `Car` besitzt von der Klasse `CarImpl` nur einen Zeiger (sagen wir: dieser belegt 4 Bytes, sprich seine Größe ist dem Compiler bekannt) und kein Objekt.
Bei diesem Sachverhalt kann der Compiler Code generieren, er muss das tatsächliche Aussehen der Klasse `CarImpl` nicht kennen!

###### Verbesserungen:

Der Einsatz eines *raw-Pointers* in der Klasse `Car` entspricht nicht dem Aussehen eines *Modern C++* Designs.
Aus diesem Grund tauschen wir diesen Zeiger mit einem Smart-Pointer, beispielsweise einem `std::unique_ptr`-Objekt, aus.
Die Header-Datei der Klasse `Car` sieht nun so aus:

```cpp
#include <memory>
 
class Car
{
public:
   Car();
   void coolDown();
private:
   class CarImpl;
   std::unique_ptr<CarImpl> impl_;
};
```

Die Implementierungsdatei ändert sich nur marginal:

```cpp
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
   Engine engine_;
};
 
Car::Car() : impl_(new CarImpl) {}
```

Es sieht so weit alles gut aus - überraschenderweise erhalten wir in diesem Zustand des Programms
einen Übersetzungsfehler:

<b>
use of undefined type 'Car::EngineImpl'</br>
can't delete an incomplete type
</b>

In C ++ gibt es eine Regel, die besagt, dass das Löschen eines Zeigers zu undefiniertem Verhalten führt,
wenn:

  * Dieser Zeiger hat den Typ `void*` oder
  * Der Typ, auf den verwiesen wird, ist unvollständig, d.h. er wird nur vorwärts deklariert,
    wie `CarImpl` in unserer Header-Datei.

Der Übersetzungsfehler liegt als darin begründet, dass der korrespondierende Typ nur vorwärts deklariert ist.

Es sind zwei Änderungen am aktuellen Programm vorzunehmen:

  * Hinzufügen einer Destruktor-Deklaration in der Klasse `Car`:<br/>
    `~Car();`

  * Hinzufügen einer Destruktor-Definition in der Klasse `CarImpl`:<br/>
    `Car::~Car() = default;`

Damit haben einen ersten minimalistischen Durchlauf durch das Pimlp-Idiom beschritten!


#### Struktur (UML):

<img src="XXX.png" width="600">

Abbildung: XXX



## Anwendungsbeispiel:

  * TBD


## Literaturhinweise

https://www.bfilipek.com/2018/01/pimpl.html

https://www.geeksforgeeks.org/pimpl-idiom-in-c-with-examples/



https://www.gamasutra.com/view/news/167098/Indepth_PIMPL_vs_pure_virtual_interfaces.php

https://stackoverflow.com/questions/825018/pimpl-idiom-vs-pure-virtual-class-interface



https://marcmutz.wordpress.com/translated-articles/pimp-my-pimpl-reloaded/


https://www.fluentcpp.com/2017/09/22/make-pimpl-using-unique_ptr/



---

[Zurück](../../Readme_05_Catalog.md)

---

## Weiterarbeit:

a) Ein voll funktionsfähiges Beispiel (mit COpy und MOveable) implementieren.
2) 
c) Wenn Zeit: Einen Vergleich Pimpl vs Interface Inheritance herstellen.

