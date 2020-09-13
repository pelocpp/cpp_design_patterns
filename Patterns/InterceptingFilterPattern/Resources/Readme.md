# Intercepting Filter Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Intercepting Filter Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*, das sich der Vor- und Nachbearbeitung einer Anforderung ("*Request*", typischerweise ein Methodenaufruf)
zuwendet. 
Die Vor- und Nachbearbeitung definiert Aktionen, die vor und nach der Kernverarbeitung der Anforderung ausgeführt werden.
Es ist auch möglich, dass eine Aktion entscheiden kann, ob die eigentliche Kernverarbeitung überhaupt ausgeführt wird.
In der Regel bearbeiten Aktionen den eingehenden oder ausgehenden Datenstrom in einer Form,
die für die weitere Verarbeitung geeignet ist.

Die Aktionen des Patterns bezeichnet man auch als *Filter*. Filter können die Authentifizierung / Autorisierung / Protokollierung oder
Nachverfolgung von Anforderungen durchführen und die Anforderungen dann an die entsprechenden Handler weiterleiten.

#### Problem:

Ohne das *Intercepting Filter Pattern* beruht die klassische Lösung auf einer Reihe von bedingten Anweisungen,
wobei jede fehlgeschlagene Bedingungsanweisung die Anforderung abbricht.
Verschachtelte `if` / `else`-Anweisungen sind eine Standardstrategie, die aber zu einer Code-Unübersichtlichkeit bzw. Code-Fragilität führen.

#### Lösung:

Der Schlüssel zur flexiblen und unauffälligen Lösung dieses Problems besteht in einem einfachen Mechanismus
zum Hinzufügen und Entfernen von Verarbeitungskomponenten, jede Komponente führt eine bestimmte Filteraktion aus.


#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Intercepting Filter Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Filter**: Definiert eine bestimmte Aufgabe, die vor oder nach der Ausführung der eigentlichen Anforderung durch das `FilterManager`-Objekt initiiert wird.
  * **FilterChain**: Verwaltet ein oder mehrere Filter und führt diese in definierter Reihenfolge auf dem Ziel-Objekt aus.
  * **Target**: Zielobjekt der Anforderung
  * **FilterManager**: Kennt das Zielobjekt und verwaltet ein `FilterChain` Objekt
  * **Client**: Objekt, das eine Anforderung an das Zielobjekt sendet.


<img src="dp_interceptor_filter_pattern.svg" width="800">

Abbildung 1: Schematische Darstellung des *Intercepting Filter Patterns*.


#### Hinweis:

Es bestehen gewisse Ähnlichkeiten zum *Chain of Responsibility* Pattern.

#### Conceptual Example:

[Quellcode](../ConceptualExample01.cpp) - Standardvariante<br/>
[Quellcode](../ConceptualExample02.cpp) - Siehe Weiterarbeit

#### Weiterarbeit:

Wenn Sie das konzeptionelle Beispiel genau betrachten, werden Sie feststellen,
dass die Filter-Methoden nur *vor* der Zielmethode ausführbar sind.
Ergänzen Sie das Beispiel so, dass Filter-Methoden sowohl vor als auch nach der eigentlichen
Zielmethode ausführbar sind.

---

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[Design Pattern - Intercepting Filter Pattern](https://www.tutorialspoint.com/design_pattern/intercepting_filter_pattern.htm)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
