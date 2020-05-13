# Decorator Pattern

## Wesentliche Merkmale

##### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das Decorator Pattern ist ein konzeptionelles Muster,
mit dem Objekte dynamisch um neue Verhaltensweisen erweitert werden können,
indem sie in spezielle *Wrapper*-Objekte (Hüllen-Objekte) eingebettet werden.

##### Hinweis:

Das Spezialisieren (Vererbung) einer Klasse ist typischerweise das Erste, was einem einfällt,
wenn man das Verhalten eines Objekts ändern (erweitern) möchte.
Die Vererbung weist jedoch einige schwerwiegende Einschränkungen auf, die es zu beachten gilt:

  * Die Vererbung ist ein statisches Konzept, also etwas, was zur Übersetzungszeit festgelegt sein muss.
    Zur Laufzeit lässt sich das Verhalten eines bestimmten Objekts nicht ändern.
    Ferner kann man nur ein ganzes Objekt durch ein anderes Objekt ersetzen, das aus einer anderen Unterklasse erstellt wurde.
    Das *Decorator Pattern* zielt auf das Ändern von Verhaltensweisen bestimmter Methoden ab.
  * Unterklassen können nur eine übergeordnete Klasse haben. In den meisten Sprachen lässt das Prinzip der Vererbung nicht zu,
    dass eine Klasse das Verhalten mehrerer Klassen gleichzeitig erbt (Prinzip der Mehrfachvererbung, in C++ allerdings möglich)

Eine Möglichkeit, diese Einschränkungen zu überwinden, ist die Verwendung von
*Aggregation* oder *Komposition* anstelle von Vererbung.
Beide Alternativen funktionieren fast gleich: Ein Objekt hat einen Verweis (Referenz, Zeiger) 
auf ein anderes und *delegiert* ihm dadurch Tätigkeiten.
Bei der Vererbung kann das Objekt diese Arbeit *selbst* ausführen,
es *erbt* das Verhalten von seiner Oberklasse.

Mit diesem Ansatz (Gebrauch eines Verweises) können Sie das verknüpfte "Hilfs"-Objekt leicht durch ein
anderes ersetzen und so das Verhalten des Containers zur Laufzeit ändern.
Ein Objekt kann das Verhalten mehrerer Klassen verwenden, indem es Verweise auf mehrere Objekte verwaltet und an diese alle Arten von Arbeit delegieren.

<img src="dp_decorator_01.png" width="500">

Abbildung 1: Vererbung versus Aggregation.

#### Problem:

Das Objekt, das Sie verwenden möchten, führt die grundlegenden Funktionen aus, die Sie benötigen.
Möglicherweise müssen Sie dem Objekt jedoch noch einige zusätzliche Funktionalitäten hinzufügen,
die vor nach der Basisfunktionalität des betrachteten Objekts auszuführen ist.



#### Lösung:



#### Pro / Kontra:

###### Pros:

  * Das Verhalten eines Objekts kann erweitert werden, ohne eine neue Unterklasse erstellen zu müssen.
  * Einem Objekt können zur Laufzeit Verantwortlichkeiten hinzugefügt oder daraus entfernt werden.
  * Es können mehrere Verhaltensweisen kombiniert werden, indem man ein Objekt in mehrere Dekoratoren einhüllt.
  * *Single Responsibility Principle*: Eine monolithische Klasse,
    die viele mögliche Verhaltensvarianten implementiert, kann so in mehrere kleinere Klassen unterteilt werden.

###### Kontras:

  * Es ist schwierig, einen bestimmten Wrapper vom Wrapper-Stapel zu entfernen.
  * Es ist schwierig, einen Dekorateur so zu implementieren, dass sein Verhalten nicht von der Reihenfolge im Dekorationsstapel abhängt.
  * Der anfängliche Konfigurationscode von Ebenen (Hüllen) sieht möglicherweise nicht sehr gut aus.


#### Struktur (UML):

<img src="dp_decorator_02.png" width="600">

Abbildung 2: Vererbung versus Aggregation.


Bild abgleichen mit

http://www.vincehuston.org/dp/decorator.html
und Buch von Shalloway ....



#### Ein Beispiel:

###### Grundlagen:


## Anwendungen des Design Pattern in der STL:

  * TBD



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

[Zurück](../../Readme.md)

---

## Weiterarbeit:

a) Ein voll funktionsfähiges Beispiel (mit COpy und MOveable) implementieren.

b) Bridge

c) Wenn Zeit: Einen Vergleich Pimpl vs Interface Inheritance herstellen.

