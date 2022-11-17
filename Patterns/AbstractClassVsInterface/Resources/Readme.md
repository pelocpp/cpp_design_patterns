# Abstrakte Klassen versus Interfaces

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

##### Grundlagen

Vergleichen wir zunächst die beiden Konzepte von abstrakten Klassen und Schnittstellen

  * Ein Interface (Schnittstelle) besitzt keine Implementierung von Methoden.
  Sie besitzt ausschließlich Methodendeklarationen.
  Natürlich benötigt es Klassen, die eine Schnittstelle implementieren, was wiederum bedeutet,
  das die Methoden der Schnittstelle dann eine Realisierung erhalten.

  * Ein Interface (Schnittstelle) hat keine Variablen.
  Es gibt von dieser Regel einige Ausnahmen, wie beispielsweise Konstantendefinitionen.

  * Eine Klasse, die eine Schnittstelle implementiert,
  muss alle Methoden der Schnittstelle implementieren.

  * Abstrakte Klassen können Variablendeklarationen und Methodenimplementierungen und Methodendeklarationen haben.
  Man kann von einer abstrakten Klasse erben, ohne die abstrakten Methoden implementieren zu müssen.
  Im Regelfall implementiert eine abstrakte Klasse einige der Methoden einer Schnittstelle,
  aber nicht alle.

  * Eine abstrakte Klasse kann nicht instanziiert werden.
  Im Regelfall leitet man eine andere Klasse von einer abstrakten Klasse ab.

  * Weder eine Schnittstelle noch eine abstrakte Klasse lassen sich Instanziieren.
  In beiden Fällen erhält man einen Übersetzungsfehler.

##### Umsetzung in C++

Bevor wir uns ansehen, wie wir die Features *abstract* und *interface* in C++
definieren wollen, betrachten wir *virtuelle* und *rein virtuelle* Methoden in C++:

  * Eine virtuelle Methode in C++ ist eine Methode,
  die in der abgeleiteten Klasse neu definiert werden kann (überschreiben),
  wobei die Verwendung des Schlüsselworts `virtual` bedeutet,
  eine so genannte späte Bindung (*late-binding*) an der Methode durchzuführen.

  * Eine reine virtuelle Methode in C++ ist eine virtuelle Methode,
  die nicht definiert, sondern nur deklariert wird, also keine Realisierung besitzt.
  Syntaktisch wird der Methodendeklaration die Kennung `= 0` am Ende hinzugefügt.

Eine abstrakte Klasse in C++
  a) muss mindestens eine rein virtuelle Methode haben,
  b) kann implementierte Methoden haben und
  c) kann Variablendeklaration haben.


Eine Schnittstelle (*interface*) in C++
  a) hat alle Methoden als rein virtuelle Methoden deklariert,
  b) hat keine Variablendeklaration.

Siehe Beispiele im Quelltext hierzu.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
