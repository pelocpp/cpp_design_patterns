# Template Method Pattern

## Wesentliche Merkmale

##### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Definiert das prinzipielle Grundgerüst eines Algorithmus in einer zentralen Methode.
Diese lagert einen oder vorzugsweise mehrere Teilschritte in Methoden abgeleiteter Klassen aus.
Änderungen an den Teilschritten haben keine Auswirkungen auf die Arbeitsweise (Realisierung)
der zentralen Methode.

Das Template Method Pattern ist ein Verhaltensentwurfsmuster,
das das Grundgerüst eines Algorithmus in einer Oberklasse definiert,
Unterklassen jedoch bestimmte Schritte des Algorithmus überschreiben lässt,
ohne dabei seine prinzipielle Struktur zu ändern.

#### Problem:

Es gibt eine Methode oder anders formuliert, eine Reihe von auszuführenden Schritten (Teilmethoden),
die auf einer höheren Abstraktionsebene
festgelegt sind (Reihenfolge der Ausführung, Bereitstellung von Parametern, ...).

In einer niedrigeren Abstraktionsebene (Detailebene) können die Teilmethoden eine unterschiedliche Implementierung haben.


#### Lösung:

Das *Template Method Pattern* schlägt vor, dass Sie einen Algorithmus in eine Reihe von Schritten aufteilen,
diese Schritte in Methoden umwandeln und diese Methoden in einer einzigen „Vorlagenmethode“ aufrufen,
daher auch der Name dieses Entwurfsmusters.
Die Schritte können entweder abstrakt sein oder eine Standardimplementierung aufweisen.
Um den Algorithmus zu verwenden, muss der Client eine eigene Unterklasse bereitstellen, alle abstrakten Schritte implementieren und bei Bedarf einige der optionalen Schritte überschreiben
Die Vorlagenmethode sollte dabei nicht überschrieben oder verändert werden.

Das *Template Method Pattern* ermöglicht die Realisierung von variierenden Teilschritten, während ein konsistenter Grundprozess beibehalten wird.


#### Struktur (UML):

<img src="dp_template_method_pattern.svg" width="600">

Abbildung: Schematische Darstellung des *Template Method Patterns*.


#### Hinweis:

Template Method Pattern und Strategy Pattern besitzen viele Gemeinsamkeiten. Ein Unterschied zwischen den beiden Mustern ist,
dass das Template Method Pattern auf Vererbung beruht, dass Strategy Pattern hingehen auf Komposition.

## Anwendungsbeispiel:

In Spezialisierungen der Oberklasse können bzw. sollten ein oder mehrere Teilmethoden überschrieben werden,
um die **Template Methode* in der Oberklasse zu vervollständigen. 

Die Skelett-Methode ist davon ausgenommen - die prinzipielle Struktur des Algorithmus ist beizubehalten,
also nicht zu verändern.


#### Beispiele:

Die Beispiele zu diesem Pattern orientieren sich an:

[https://refactoring.guru/design-patterns/strategy](https://refactoring.guru/design-patterns/strategy/java/example)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---