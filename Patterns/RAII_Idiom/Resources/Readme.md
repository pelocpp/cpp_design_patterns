# RAII Idiom

## Wesentliche Merkmale

#### Ziel / Absicht:

**RAII** (*Resource Acquisition Is Initialization*) ist ein Programmieridiom (Paradigma), das auf 
Bjarne Stroustrup und Andrew Koenig zurückzuführen ist. Die Idee ist, eine Ressource
(Speicherbereich auf der Halde (*Heap Memory*), Datei, Socket, Mutex, ...) an ein Objekt zu binden
und den Mechanismus der Objektkonstruktion und -destruktion  (Konstruktor, Destruktor) zu nutzen,
um  Ressourcen in einem Programm automatisch
zu verwalten.

#### Prinzip:

Jedes Mal, wenn wir eine Ressource erwerben wollen, tun wir dies, indem wir ein Objekt erstellen,
dass diese Ressource besitzt. Wann immer das Objekt den Gültigkeitsbereich verlässt, wird die Ressource
automatisch freigegeben.

#### Lösung:

Wir betrachten das Prinzip einer RAII-verwalteten Ressource an Hand einer Folge von Code-Beispielen:

##### 1. Eine RAII-konforme Klasse:

```cpp
template <typename T>
class RAII {
public:
    explicit RAII(T* p) : m_p(p) {}
    ~RAII() { delete m_p; };

    // grant access to pointer inside RAII object
    T* operator->() { return m_p; }
    const T* operator->() const { return m_p; }
    T& operator&() { return *m_p; }
    const T* operator&() const { return *m_p; }

private:
    T* m_p;
};
```

---

##### 2. Einfache Anwendung eines RAII-Objekts (*Compound-Statement*):

```cpp
void test() 
{
    {
        RAII<Dummy> p(new Dummy(1));
    }

    std::cout << "Done." << std::endl;
}
```

###### Ausgabe:

```
c'tor Dummy [1]
d'tor Dummy [1]
Done.
```

---

##### 3. Zugriff auf die Ressoure (Überladener `->` und `&` Operator):

```cpp
void test() 
{
    {
        RAII<Dummy> p(new Dummy(2));
        p->sayHello();
        int value = p->getValue();
        std::cout << "Value " << value << " inside Dummy object." << std::endl;

        Dummy& dRef = p.operator&();
        dRef.sayHello();
        value = dRef.getValue();
        std::cout << "Value " << value << " inside Dummy object." << std::endl;
    }

    std::cout << "Done." << std::endl;
}
```

###### Ausgabe:

```
c'tor Dummy [2]
Hello Dummy [2]
Value 2 inside Dummy object.
Hello Dummy [2]
Value 2 inside Dummy object.
d'tor Dummy [2]
Done.
```

---

##### 4. Vorzeitiges Verlassen einer Wiederholungsschleife:

```cpp
void test()
{

    // test RAII idiom upon a loop break
    do {
        RAII<Dummy> p(new Dummy(3));
        break;
    } while (false);

    std::cout << "Done." << std::endl;
}
```

###### Ausgabe:

```
c'tor Dummy [3]
d'tor Dummy [3]
Done.
```

---

##### 5. Verhalten des RAII-Idioms bei Eintreten eines Ausnahme (*Exception*):

```cpp
void test_04()
{

    // test RAII idiom upon exception being thrown
    try {
        RAII<Dummy> p(new Dummy(4));
        throw 99;
    }
    catch (int n) {
        std::cout << "Exception " << n << " occurred!" << std::endl;
    }

    std::cout << "Done." << std::endl;
}
```

###### Ausgabe:

```
c'tor Dummy [4]
d'tor Dummy [4]
Exception 99 occurred!
Done.
```

---

##### 6. Reihenfolge bei der Freigabe mehrere RAII-verwalteter Ressourcen:

```cpp
void test_05() {

    // test RAII idiom with two encapsulated resources:
    // Note order of destructor calls

    RAII<Dummy> p1(new Dummy(1));

    RAII<Dummy> p2(new Dummy(2));

    std::cout << "Done." << std::endl;
}
```

###### Ausgabe:

```
c'tor Dummy [1]
c'tor Dummy [2]
Done.
d'tor Dummy [2]
d'tor Dummy [1]
```

---

##### 7. RAII-verwalteter Ressource als Instanzvariable eines Objekts

```cpp
class RAIIContainer
{
public:
    RAIIContainer(Dummy* p) : m_rp(p) {}

private:
    RAII<Dummy> m_rp;
};

void test_06()
{
    {
        RAIIContainer cont(new Dummy(5));
    }

    std::cout << "Done." << std::endl;
}
```

---

###### Ausgabe:

```
c'tor Dummy [5]
d'tor Dummy [5]
Done.
```

#### Struktur:

Die folgenden beiden Abbildungen beschreiben konzeptionell die Allokation
einer Ressource mit und ohne RAII-Idiom:

<img src="xxx.svg" width="600">

Abbildung 1: XXX.

<img src="xxx.svg" width="600">

Abbildung 2: XXX.


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/visitor/cpp/example#example-0)

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Visitor)

vor.

#### 'Real-World' Example:

Im Buch [Entwurfsmuster: Das umfassende Handbuch](https://www.amazon.de/Entwurfsmuster-umfassende-Handbuch-Matthias-Geirhos/dp/3836227622)
von Matthias Geirhos findet sich zu diesem Entwurfsmuster ein Beispiel aus der Welt des Onlinehandels vor.
Sagen wir, ein Onlinehändler würde Bücher, Spiele und Videos verkaufen.
Das ist nichts Neues, und ein Warenkorb mit Büchern, Spielen und Videos stellt auch keine große Herausforderung dar.

Nun aber kommen die Methoden ins Spiel. Mit den Elementen eines Warenkorbs kann man sehr unterschiedliche Dinge anstellen wie zum Beispiel:

  * Berechnung des Gesamtpreises aller Artikel im Warenkorb,
  * Zusammenstellung des Inhalts des Warenkorbs als HTML für die Website des Onlinehandels,
  * Erstellung einer Rechnung zum Inhalt des Warenkorbs als PDF,
  * ...

Und natürlich gibt es noch viele Methoden, die nur einzelnen Klassen (Buch, Spiel, ...) vorbehalten sind.

Damit sind wir im Zentrum des Musters angekommen: Es trennt die Klassenhierarchie von den Operationen, die
stattdessen in eine zweite Hierarchie wandern. Und anstatt die Operation direkt aufzurufen,
erstellen wir ein Objekt für diese auszuführende Operation (den so genannten *Visitor*) und übergeben es
dem Objekt der fachlichen Hierarchie (der so genannten *ObjectStructure*),
die dann die Operation aufruft.

Studieren Sie den Beispielcode aus dem Buch und führen Sie diesen in ein C++-Programm über. Betrachten Sie hierzu auch Abbildung 2:

<img src="dp_visitor_pattern_onlineshop.svg" width="700">

Abbildung 2: Ein Onlinehandel modelliert mit dem *Visitor Pattern*.

Implementieren Sie zwei *Visitor*-Klassen, eine für die Berechnung des Gesamtpreises aller Artikel im Warenkorb und eine weitere
zur Darstellung des Inhalts des Warenkorbs in HTML.


## Weiterarbeit:

Eng verwandt mit dem  *Visitor Pattern* ist das  *Double Dispatch* Pattern. Siehe hierzu

[Visitor and Double Dispatch](https://refactoring.guru/design-patterns/visitor-double-dispatch)

und 

[Double Dispatch in C++](http://www.vishalchovatiya.com/double-dispatch-in-cpp/)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
