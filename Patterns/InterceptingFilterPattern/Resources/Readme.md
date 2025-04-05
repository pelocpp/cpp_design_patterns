# Intercepting Filter Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Intercepting Filter Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
das sich der Vor- und Nachbearbeitung einer Anforderung (*&bdquo;Request&rdquo;*, typischerweise ein Methodenaufruf) zuwendet. 
Die Vor- und Nachbearbeitung definiert Aktionen, die vor und nach der Kernverarbeitung der Anforderung ausgef�hrt werden.
Es ist auch m�glich, dass eine Aktion entscheiden kann, ob die eigentliche Kernverarbeitung �berhaupt stattfindet.
In der Regel bearbeiten Aktionen den eingehenden oder ausgehenden Datenstrom in einer Form,
die f�r die weitere Verarbeitung geeignet ist.

Die Aktionen des Patterns bezeichnet man auch als *Filter*. Filter k�nnen die Authentifizierung / Autorisierung / Protokollierung oder
Nachverfolgung von Anforderungen durchf�hren und die Anforderungen dann an die entsprechenden Handler weiterleiten.

#### Problem:

Ohne das *Intercepting Filter Pattern* beruht die klassische L�sung auf einer Reihe von bedingten Anweisungen,
wobei jede fehlgeschlagene Bedingungsanweisung die Anforderung abbricht.
Verschachtelte `if` / `else`-Anweisungen stehen f�r eine Standardstrategie,
die aber zu einer Code-Un�bersichtlichkeit bzw. Code-Fragilit�t f�hren.

#### L�sung:

Der Schl�ssel zur flexiblen und unauff�lligen L�sung dieses Problems besteht in einem einfachen Mechanismus
zum Hinzuf�gen und Entfernen von Verarbeitungskomponenten, jede Komponente f�hrt eine bestimmte Filteraktion aus.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Intercepting Filter Patterns*.
Es besteht im Wesentlichen aus f�nf Teilen:

  * **Filter**: Definiert eine bestimmte Aufgabe, die vor oder nach der Ausf�hrung der eigentlichen Anforderung durch das `FilterManager`-Objekt initiiert wird.
  * **FilterChain**: Verwaltet ein oder mehrere Filter und f�hrt diese in definierter Reihenfolge auf dem Ziel-Objekt aus.
  * **Target**: Zielobjekt der Anforderung
  * **FilterManager**: Kennt das Zielobjekt und verwaltet ein `FilterChain` Objekt
  * **Client**: Objekt, das eine Anforderung an das Zielobjekt sendet.


<img src="dp_interceptor_filter_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Intercepting Filter Patterns*.

#### Hinweis:

Es bestehen gewisse �hnlichkeiten zum *Chain of Responsibility* Pattern.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Standardvariante<br />
[Quellcode 2](../ConceptualExample02.cpp) &ndash; Siehe Weiterarbeit

---

#### Weiterarbeit:

Wenn Sie das konzeptionelle Beispiel genau betrachten, werden Sie feststellen,
dass die Filter-Methoden nur *vor* der Zielmethode ausf�hrbar sind.
Erg�nzen Sie das Beispiel so, dass Filter-Methoden sowohl *vor* als auch *nach* der eigentlichen
Zielmethode ausf�hrbar sind.

---

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[Design Pattern - Intercepting Filter Pattern](https://www.tutorialspoint.com/design_pattern/intercepting_filter_pattern.htm)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
