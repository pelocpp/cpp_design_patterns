# Kritik an Entwurfsmustern

Es scheint, als hätten nur faule Leute Designmuster noch nicht kritisiert.
Schauen wir uns die typischsten Argumente gegen die Verwendung von Mustern an.

#### Behelfslösungen für eine schwache Programmiersprache

Typischerweise entsteht der Bedarf an Mustern, wenn Entwickler eine Programmiersprache oder eine Technologie wählen (oder wählen müssen),
der die erforderliche Abstraktionsebene fehlt. In diesem Fall werden Muster zu einer Behelfslösung,
die der Sprache die dringend benötigten Zusatzfähigkeiten verleiht.

#### Ineffiziente Lösungen

Entwurfsmustern versuchen, einen bereits weit verbreiteten Ansätze zu systematisieren bzw. zu verallgemeinern.
Diese Vorlage wird von vielen Entwicklern als Dogma angesehen und sie implementieren das Muster „auf den Punkt“,
ohne es an den Kontext des Projekts flexibel anzupassen.

Beispielsweise kann das Strategie-Entwurfsmuster mit einer einfachen anonymen (Lambda-)Funktion
in den meisten modernen Programmiersprachen (auch C++) implementiert werden.


#### Ungerechtfertigte Verwendung

„*Wenn Sie nur einen Hammer haben, sieht alles aus wie ein Nagel.*“

Dies ist das Problem, das viele Anfänger verfolgt, die sich gerade mit Entwurfsmustern vertraut gemacht haben.
Nachdem sie etwas über Muster gelernt haben, versuchen sie, diese überall anzuwenden, selbst in Situationen,
in denen einfacherer Code gut funktionieren  würde.

---

[Zurück](Readme.md)

---
