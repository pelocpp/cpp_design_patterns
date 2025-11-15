# Dependency Inversion Principle

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall des &ldquo;Dependency Inversion Principle&rdquo;-Idioms.

Was ist am vorliegenden Code-Fragment zu kritisieren?

  * Jeder Entwickler (Objekte der Klassen `FrontEndDeveloper` bzw. `BackEndDeveloper`) wird von einem `Project`-Objekt erstellt.

  * Dieser Ansatz ist jedoch nicht ideal, denn nun hängt das übergeordnete Modul (Klasse `Project`)
    von untergeordneten Modulen ab &ndash; den Klassen für die einzelnen Entwickler.

Dies können wir dadurch vermeiden, indem wir die Entwickler-Klassen und die Klasse `Project` so realisieren,
dass sie nur von einer Schnittstelle abhängen:

```cpp
01: class Developer {
02: public:
03:     virtual ~Developer() = default;
04:     virtual void develop() = 0;
05: };
```

Nun kennt die `Project`-Klasse nicht mehr länger die Implementierungen der beteiligten Entwickler-Klassen.

Bei diesem Ansatz wird Klasse `Project` von den konkreten Implementierungen entkoppelt, sie hängt stattdessen
nur von der abstrakten Schnittstelle `Developer` ab.

Auch die Klassen des untergeordneten Moduls leiten sich von dieser Schnittstelle ab!

Weitere Details zur Lösung entnehmen Sie bitte dem Quellcode.

#### Literaturhinweis

Die Anregung zum diesem Beispiel finden Sie in dem Buch

[Software Architecture with C++](https://www.amazon.de/Software-Architecture-effective-architecture-techniques-ebook/dp/B08TQBR8F4)

von Piotr Gaczkowski und Adrian Ostrowski vor.


#### Quellcode

[Siehe hier](../DependencyInversionPrinciple.cpp)

---

[Zurück](Readme.md)

---
