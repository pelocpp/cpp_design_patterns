# Prototype Pattern &ndash; auch als *Virtueller Konstruktor* bezeichnet

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_prototype_pattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/category/design-patterns/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&ldquo;Erstelle eine Kopie eines Objekts durch einen Zeiger auf seinen Basistyp.&rdquo;


Das *Prototype Pattern* ist ein Entwurfsmuster,
das zum Instanziieren einer Klasse auf das Kopieren oder Klonen der Eigenschaften eines anderen, vorhandenen Objekts zurückgreift.
Das neue Objekt ist eine exakte Kopie des Prototyps, ermöglicht jedoch Änderungen an diesem, ohne das Original zu verändern.

#### Problem:

Mit dem *Prototype* Entwurfsmuster können wir die Komplexität des Erstellens
neuer Instanzen vor dem Client verbergen. Das Konzept besteht darin, ein vorhandenes Objekt zu kopieren,
anstatt eine neue Instanz (samt dazugehöriger Klasse) von Grund auf neu zu erstellen.
Dies kann bisweilen mit einem recht zeitintensiven Aufwand verbunden sein.

Das vorhandene Objekt fungiert als Prototyp eines neuen Objekts und besitzt seinen Status.
Das neu kopierte Objekt kann dieselben Eigenschaften bei Bedarf ändern.
Dieser Ansatz spart Ressourcen und Zeit, insbesondere wenn die Objekterstellung nicht-trivial ist.

#### Lösung:

Das *Prototype* Entwurfsmuster stammt aus der Kategorie der Erzeugungssmuster.
Das Entwurfsmuster ist erforderlich, wenn die Objekterstellung zeitaufwändig und kostspielig ist.
Daher erstellen wir ein neues Objekt auf Basis eines vorhandenen Objekts.

Diese Art der Objekterstellung wird als *Klonen* bezeichnet.
Wenn das ursprüngliche Objekt geklont wird, ist das neue Objekt &ndash; in Abhängigkeit von der Implementierung
der `clone`-Methode &ndash; eine flache (*shallow*) oder tiefe (*deep*) Kopie.
Diese Kopie dupliziert alle Eigenschaften und Felder des ursprünglichen Objekts.
Wenn eine Eigenschaft ein Referenztyp ist, sollte vom referenzierten Objekt ebenfalls eine tiefe Kopie erstellt werden,
um insgesamt zu einer echten Kopie des ursprünglichen Objekts zu gelangen.

In manchen Programmiersprachen wird die `clone`-Methode automatisch bereitgestellt bzw. vom Programmersteller erzwungen:

  * **Java**:<br/>
    ```java
    @Override
    protected Object clone() throws CloneNotSupportedException {
      ...
    }
    ```

  * **.NET Framework**:<br/>
    ```java
    public object Clone () {
      ...
    }
    ```

Dies ist in C++ so nicht der Fall. Eine `clone`-Methode (gleichwertig: Kopierkonstruktor) ist am Ursprungsobjekt bei Anwendung des
*Prototype Patterns* explizit bereitzustellen.

#### Eine anschauliche Beschreibung:

Wir betrachten das Entwurfsmuster *Prototyp* an Hand der Fragestellung
&ldquo;Was ist der Unterschied zwischen dem Entwurfsmuster *Prototyp* und dem Kopierkonstruktor in C++&rdquo;?

  * Der Kopierkonstruktor ist ein programmiersprachliches Konstrukt der Sprache C++.

  * Das Entwurfsmuster *Prototyp* ist ein Entwurfsmuster, das verwendet wird, um (polymorphe) Objekte basierend auf einer vorhandenen Instanz zu erzeugen.

  * Es wäre schwierig, Ersteres zu verwenden, um Letzteres zu implementieren, da der Kopierkonstruktor verwendet wird, wenn die genaue Instanz des Objekts bekannt ist,
    während das *Prototyp*-Entwurfsmuster verwendet wird, wenn es irgendeine Implementierung einer Schnittstelle gibt
    und Sie nur ein neues Objekt von genau der gleichen Implementierung erhalten möchten,
    ohne dabei auf mühselige Casting- oder Typumwandlungsmethoden zurückzugreifen.

  * Nehmen wir an, Sie haben Schnittstelle `I` und die Implementierungen `A` und `B`. Irgendwann erhalten Sie ein Objekt `i`, das `I` implementiert.
    Vielleicht möchten Sie es nicht ändern, sondern lieber eine neue Instanz erhalten und dann einige Änderungen daran vornehmen.
    Wie könnte das erreicht werden, wenn Sie die genaue Klasse von `i` nicht kennen?
    Sie wissen also nicht, ob `i`  ein Objekt der Klasse `A` oder `B` referenziert!
    Das Entwurfsmuster *Prototyp* ist eine Lösung dieses Problems: 

```cpp
   I* i2 = i.clone();
```

  * In einer statisch typisierten Programmiersprache kann man ein Objekt nur dann kopieren,
    wenn man seinen statischen Typ kennt, da der Compiler wissen muss,
    wie viel Speicherplatz er zuweisen muss.
    Daher kann man ein Objekt des abgeleiteten Typs nicht direkt über einen Zeiger
    auf seine Basis kopieren.

  * Der *Virtuelle Konstruktor* ist eine Technik zum Delegieren des Vorgangs des Kopierens
    des Objekts an die abgeleitete Klasse durch die Verwendung virtueller Funktionen.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Prototype Patterns*.
Es besteht im Wesentlichen aus zwei Teilen:

  * **Prototype**: Abstrakte Basisklasse, die eine (abstrakte) `clone`-Methode besitzt. 
    Die `clone`-Methode liefert ein Prototypobjekt zurück.
  * **ConcretePrototype**: Klasse, die sich von der Prototype-Basisklasse ableitet. Sie kann zusätzliche Funktionen enthalten.
    In dieser Klasse wird die `clone`-Methode überschrieben.

<img src="dp_prototype_pattern.svg" width="500">

*Abbildung* 1: Schematische Darstellung des *Prototype Patterns*.

#### Hinweis:

Es ist **nicht** möglich, das *Virtueller Konstruktor*-Idiom unverändert &ndash; so wie im
ersten konzeptionellen Beispiel gezeigt &ndash; zu implementieren.
Der Grund ist, das abgeleitete virtuelle Methoden kovariante Rückgabetypen haben müssen.
Bei den beiden Datentypen `std::shared_ptr<Prototype>` und `std::shared_ptr<ConcretePrototype>` ist dies **nicht** der Fall.

Eine einfache Umgehung dieses Problems besteht darin,
dass die Methode `ConcretePrototype::clone` stattdessen einen `Prototype`-Zeiger zurückgibt.

#### Hinweis:

In JavaScript ist das *Prototype Pattern* quasi nativ enthalten.

Die Erstellung von Objekten erfolgt hier &ndash; unter anderem &ndash; auf der Basis von so genannten
&ldquo;Konstruktorfunktionen&rdquo;, die als Blaupausen für neue Objekte verwendet werden können.
Man spricht dabei auch von der so genannten &ldquo;*Prototypischen Vererbung*&rdquo;.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Sehr einfache Version &ndash; mit *raw*-Zeigern und Smart Pointern 

[Quellcode 2](../ConceptualExample02.cpp) &ndash; Beispiel eines Schachbretts mit Spielfiguren unterschiedlichen Typs

[Quellcode 3](../ConceptualExample03.cpp) &ndash; Ein Beispiel mit einer Factory für Prototypen

[Quellcode 4](../ConceptualExample04.cpp) &ndash; Wie letztes Beispiel, nur mit Smart Pointern

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/prototype/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/430590/Design-Patterns-1-of-3-Creational-Design-Patterns#Prototype)

vor.

Eine Beschreibung des *Virtueller Konstruktor*-Idioms findet man [hier](https://cpppatterns.com/patterns/virtual-constructor.html).

Die Problematik des kovarianten Rückgabetyps ist in StackOverflow beschrieben:

[Return Type Covariance with Smart Pointers](https://stackoverflow.com/questions/6924754/return-type-covariance-with-smart-pointers/6925201)    

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

