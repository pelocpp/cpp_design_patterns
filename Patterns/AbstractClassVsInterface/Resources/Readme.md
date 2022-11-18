# Abstrakte Klassen versus Interfaces

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale

##### Grundlagen

Vergleichen wir zunächst die beiden Konzepte von *abstrakten Klassen* und *Schnittstellen*:

  * Ein *Interface* (*Schnittstelle*) besitzt keine Implementierung von Methoden,
  sie besteht ausschließlich Methodendeklarationen.
  Natürlich benötigt es Klassen, die eine Schnittstelle implementieren, was wiederum bedeutet,
  das die Methoden der Schnittstelle dann eine Realisierung erhalten.

  * Ein Interface (Schnittstelle) enthält keine Variablen.
  Es gibt von dieser Regel einige Ausnahmen, wie beispielsweise möglicherweise
  die Definition von Konstanten.

  * Eine Klasse, die eine Schnittstelle implementiert,
  muss alle Methoden der Schnittstelle implementieren.

  * *Abstrakte Klassen* können Variablendeklarationen und Methodenimplementierungen und Methodendeklarationen haben.
  Man kann von einer abstrakten Klasse erben, ohne die abstrakten Methoden implementieren zu müssen.
  Im Regelfall implementiert eine abstrakte Klasse einige der Methoden einer Schnittstelle,
  aber nicht alle.

  * Eine abstrakte Klasse kann nicht instanziiert werden.
  Im Regelfall leitet man eine andere Klasse von einer abstrakten Klasse ab.

  * Auch kann man eine Schnittstelle nicht instanziieren.
  Wie beim Versuch, eine abstrakte Klasse zu instanziieren,
  erhält man einen Übersetzungsfehler.

##### Umsetzung in C++

Bevor wir uns ansehen, wie wir die Features *abstract* und *interface* in C++
definieren könnten, betrachten wir *virtuelle* und *rein virtuelle* Methoden in C++:

  * Eine *virtuelle* Methode in C++ ist eine Methode,
  die in der abgeleiteten Klasse neu definiert werden kann (Vorgang des *Überschreibens*),
  wobei die Verwendung des Schlüsselworts `virtual` bedeutet,
  eine so genannte *späte Bindung* (*late-binding*) an der Methode durchzuführen.

  * Eine *rein virtuelle* Methode in C++ ist eine virtuelle Methode,
  die nicht definiert, sondern nur deklariert wird, also keine Realisierung besitzt.
  Syntaktisch wird der Methodendeklaration am Ende `= 0`  hinzugefügt.

Eine abstrakte Klasse in C++
  1. muss mindestens eine rein virtuelle Methode haben,
  2. kann implementierte Methoden haben und
  3. kann Variablendeklaration haben.


Eine Schnittstelle (*interface*) in C++
  1. hat alle Methoden als rein virtuelle Methoden deklariert,
  2. hat keine Variablendeklarationen.

Siehe Beispiele im Quelltext hierzu.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---
