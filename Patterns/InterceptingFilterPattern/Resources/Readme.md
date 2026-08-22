# Intercepting Filter Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

> &bdquo;Das Intercepting Filter Pattern ermöglicht es, eingehende Anfragen durch eine Kette von Filtern zu leiten, die diese Anfragen vor oder nach ihrer eigentlichen Verarbeitung prüfen, verändern oder ergänzend bearbeiten.&rdquo;

Das *Intercepting-Filter-Pattern* gehört zu den klassischen Entwurfsmustern für die Verarbeitung von Anfragen,
wie sie ursprünglich im Kontext von Webanwendungen (J2EE Core Patterns) beschrieben wurden,
sich aber genauso auf beliebige Request-Response-orientierte Systeme in C++ übertragen lassen.

Die Grundidee ist, wiederkehrende, anfragebezogene Querschnittsaufgaben &ndash; etwa Logging, Autorisierung, Kompression oder Eingabevalidierung &ndash;
nicht in den eigentlichen Verarbeitungscode zu mischen, sondern in eigenständige Filter-Objekte auszulagern.
Diese Filter werden zu einer Kette (*Filter Chain*) zusammengesetzt, die eine eingehende Anfrage nacheinander durchläuft,
bevor sie den eigentlichen Ziel-Handler erreicht; häufig laufen dieselben Filter auch auf dem Rückweg der Antwort
in umgekehrter Reihenfolge noch einmal durch.

Jeder Filter implementiert dabei eine gemeinsame Schnittstelle und entscheidet selbst,
ob und wie er die Anfrage bearbeitet und ob er sie an den nächsten Filter in der Kette weiterreicht.

Ein zentraler Filter-Manager oder die Kette selbst kümmert sich um die Reihenfolge und den Aufruf der einzelnen Filter,
sodass diese untereinander keine Abhängigkeiten kennen müssen.
Dadurch lassen sich einzelne Filter unabhängig voneinander entwickeln, testen, austauschen oder auch zur Laufzeit neu konfigurieren,
ohne den eigentlichen Anwendungscode anzufassen.

Das Pattern fördert so eine klare Trennung von fachlicher Logik und technischen Querschnittsbelangen
und erhöht Wiederverwendbarkeit sowie Wartbarkeit des Systems.

In C++ lässt es sich beispielsweise über eine abstrakte Basisklasse `Filter` mit virtueller `execute()`-Methode und
eine Kette aus `std::vector<std::unique_ptr<Filter>>` realisieren.

#### Struktur (UML):

Das folgende UML-Diagramm beschreibt eine Implementierung des *Intercepting Filter Patterns*.
Es besteht im Wesentlichen aus fünf Teilen:

  * **Filter**: Definiert eine bestimmte Aufgabe, die vor oder nach der Ausführung der eigentlichen Anforderung durch das `FilterManager`-Objekt initiiert wird.
  * **FilterChain**: Verwaltet ein oder mehrere Filter und führt diese in definierter Reihenfolge auf dem Ziel-Objekt aus.
  * **Target**: Zielobjekt der Anforderung
  * **FilterManager**: Kennt das Zielobjekt und verwaltet ein `FilterChain` Objekt
  * **Client**: Objekt, das eine Anforderung an das Zielobjekt sendet.


<img src="dp_interceptor_filter_pattern.svg" width="800">

*Abbildung* 1: Schematische Darstellung des *Intercepting Filter Patterns*.

#### Hinweis:

Es bestehen gewisse Ähnlichkeiten zum *Chain of Responsibility* Pattern.

---

#### Conceptual Example:

[Quellcode 1](../ConceptualExample01.cpp) &ndash; Standardvariante<br />
[Quellcode 2](../ConceptualExample02.cpp) &ndash; Siehe Weiterarbeit

---

#### Weiterarbeit:

Wenn Sie das konzeptionelle Beispiel genau betrachten, werden Sie feststellen,
dass die Filter-Methoden nur *vor* der Zielmethode ausführbar sind.
Ergänzen Sie das Beispiel so, dass Filter-Methoden sowohl *vor* als auch *nach* der eigentlichen
Zielmethode ausführbar sind.

---

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[Design Pattern - Intercepting Filter Pattern](https://www.tutorialspoint.com/design_pattern/intercepting_filter_pattern.htm)

vor.

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
