# Anzahl der Objekte einer baumartigen Struktur bestimmen

---

[Zurück](Readme.md)

---

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall des *Composite* Entwurfsmusters
und im weiteren Verlauf des *Visitor* Entwurfsmusters.

Die Details der Lösung entnehmen Sie dem Quellcode.

Das folgende Klassendiagramm hilft, die Zusammenhänge aller beteiligten Klassen darzustellen:

<img src="dp_counting_objects.svg" width="800">


#### Hinweis:

Im Quellcode finden Sie noch eine weitere Zusatzaufgabe realisiert vor,
nämlich die Bestimmung der maximalen Verschachtelungs­tiefe des Objektbaums.

Neben den `visit`-Methoden braucht die Visitor­schnitt­stelle noch eine weitere Methode,
die das Verlassen eines `Composite`-Objekts anzeigt, wie nennen sie `leave`.

Diese Methode muss nun durch die entsprechede `accept`-Methode in der Objektstruktur aufgerufen werden.
Wenn sich nun eine Operation für die Verschachtelungs­tiefe des Objektbaums „interessiert“,
muss sie nur dement­sprechend die `leave`-Methode implemen­tieren.
In dieser Methode muss nur eine Instanzvariable,
die die Ver­schachtelungs­tiefe reprä­sentiert, dekrementiert werden,
während sie in der dazugehörigen `visit`-Methode inkrementiert wird.


#### Literaturhinweis

Die Anregung zum diesem Beispiel finden Sie unter

[Das Besucher-Muster (Visitor Pattern) in C++](http://www.oop-trainer.de/Themen/Visitor.html).


#### Quellcode

[Siehe hier](../CountingObjects.cpp)

---

[Zurück](Readme.md)

---
