# Template Method Pattern

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---

<img src="dp_template_methodpattern_intro.png" width="600" />

<sup>(Credits: [Blog von Vishal Chovatiya](https://vishalchovatiya.com/pages/start-here/))</sup>

---

## Wesentliche Merkmale

##### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

###### In einem Satz:

&bdquo;Um einen Entwurf eines Algorithmus auf einer h�heren Ebene bereitzustellen, der von seinen abgeleiteten Klassen zu vervollst�ndigen ist.&rdquo;

Definiert das prinzipielle Grundger�st eines Algorithmus in einer zentralen Methode.
Diese lagert einen oder vorzugsweise mehrere Teilschritte in Methoden abgeleiteter Klassen aus.
�nderungen an den Teilschritten haben keine Auswirkungen auf die Arbeitsweise (Realisierung)
der zentralen Methode.

Das *Template Method Pattern* ist ein Verhaltensentwurfsmuster,
das das Grundger�st eines Algorithmus in einer Oberklasse definiert,
Unterklassen jedoch bestimmte Schritte des Algorithmus �berschreiben l�sst,
ohne dabei seine prinzipielle Struktur zu �ndern.

#### Problem:

Es gibt eine Methode oder anders formuliert, eine Reihe von auszuf�hrenden Schritten (Teilmethoden),
die auf einer h�heren Abstraktionsebene
festgelegt sind (Reihenfolge der Ausf�hrung, Bereitstellung von Parametern, ...).

In einer niedrigeren Abstraktionsebene (Detailebene) k�nnen die Teilmethoden eine unterschiedliche Implementierung haben.


#### L�sung:

Das *Template Method Pattern* hat zum Inhalt, dass Sie einen Algorithmus in eine Reihe von Schritten aufteilen,
diese Schritte in Methoden umwandeln und diese Methoden in einer einzigen &bdquo;Vorlagenmethode&rdquo; aufrufen,
daher auch der Name dieses Entwurfsmusters.
Die Schritte k�nnen entweder abstrakt sein oder eine Standardimplementierung aufweisen.
Um den Algorithmus zu verwenden, muss der Client eine eigene Unterklasse bereitstellen, alle abstrakten Schritte implementieren und bei Bedarf einige der optionalen Schritte �berschreiben.
Die Vorlagenmethode sollte dabei nicht �berschrieben oder ver�ndert werden!

Das *Template Method Pattern* erm�glicht die Realisierung von variierenden Teilschritten, w�hrend ein konsistenter Grundprozess beibehalten wird.


#### Struktur (UML):

<img src="dp_template_method_pattern.svg" width="450">

*Abbildung* 1: Schematische Darstellung des *Template Method Patterns*.


## Anwendungsbeispiel:

In Spezialisierungen der Oberklasse k�nnen bzw. sollten ein oder mehrere Teilmethoden �berschrieben werden,
um die **Template Methode** in der Oberklasse zu vervollst�ndigen. 

Die Skelett-Methode ist davon ausgenommen - die prinzipielle Struktur des Algorithmus ist beizubehalten,
also nicht zu ver�ndern.

---

#### Conceptual Example:

[Quellcode](../ConceptualExample.cpp)

---

#### &bdquo;Real-World&rdquo; Beispiel:

Im &bdquo;Real-World&rdquo; Beispiel zu diesem Entwurfsmuster 
definiert die Template-Methode einen Algorithmus f�r die Arbeit mit einem sozialen Netzwerk.
Unterklassen, die einem bestimmten sozialen Netzwerk entsprechen,
implementieren diese Schritte gem�� der vom sozialen Netzwerk bereitgestellten API.

Die Klasse `SocialNetwork` repr�sentiert die Basisklasse des sozialen Netzwerks.
Zwei weitere Klassen `Twitter` und `Facebook` stehen f�r konkrete Beispiele sozialer Netzwerke.

Die &bdquo;Vorlagenmethode&rdquo; ist in der Klasse `SocialNetwork` vorgegeben, sie lautet `post`:

```cpp
bool post(const std::string& message);
```

Ihre Implementierung darf nicht ver�ndert werden, um dem Charakter des Entwurfsmusters gerecht zu werden.
Die Teilschritte, die zur Realisierung der `post`-Methode erforderlich sind, lauten in dem Beispiel
`logIn`, `logOut` und `sendData`. Diese drei Methoden sind geeignet von konkreten Social Media Klassen
zu �berschreiben, siehe dazu auch *Abbildung* 2:

<img src="dp_template_method_pattern_social_media.svg" width="800">

*Abbildung* 2: Das *Template Method Pattern* am Beispiel sozialer Netzwerke.

---

Die Anwendungsf�lle des *Template Method*-Pattern und des *Strategy*-Pattern sind ziemlich �hnlich.
Beide Muster erm�glichen es, Variationen eines Algorithmus bereitzustellen.
Das *Template Method*-Pattern basiert auf der Ebene von Klassen und der Bildung von Unterklassen,
das Strategiemuster auf der Ebene von Objekten und deren Komposition.

Das *Strategy*-Pattern erh�lt unterschiedliche Strategien in der Gestalt von Objekten
und kann somit zur Laufzeit seine Strategien austauschen.

Die *Template*-Methode kehrt den Kontrollfluss nach dem Hollywood-Prinzip um:
&bdquo;Don't call us, we call you&rdquo;.

Das *Strategy*-Pattern gleicht mehr einer Black Box.
Es erm�glicht, eine Strategie durch eine andere zu ersetzen, ohne deren Details zu kennen.

---


## FAQs

*Frage*: Was ist der Unterschied zwischen dem *Strategy*- und *Template Method*-Pattern?

  * Das *Template Method*-Pattern basiert auf **Vererbung**: Es werden Teile eines Algorithmus ver�ndert, indem diese Teile in abgeleiteten Klassen erweitert werden.

  * *Strategy*-Pattern basiert auf der **Komposition**: Es werden Teile des Verhaltens eines Objekts ver�ndert, indem es verschiedene Strategien haben kann, die unterschiedlichem Verhalten entsprechen.

oder auch:

  * *Template Method*-Pattern: Funktioniert auf **Klassenebene**, es ist also ein statisches Konzept.

  * *Strategy*-Pattern: Funktioniert auf **Objektebene**, das Verhalten wird zur Laufzeit ge�ndert.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/template-method/cpp/example#example-0)

und

[https://www.codeproject.com](https://www.codeproject.com/Articles/455228/Design-Patterns-3-of-3-Behavioral-Design-Patterns#Template)

vor.

---

[Zur�ck](../../../Resources/Readme_05_Catalog.md)

---
