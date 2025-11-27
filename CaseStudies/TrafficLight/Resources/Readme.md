# Simulation einer Verkehrsampel (*TrafficLight*)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

#### Aufgabe

Schreiben Sie ein C++-Programm, dass die drei Phasen einer Verkehrsampel (Rot, Grün, Gelb)
in einer Konsolen-Anwendung simuliert. Nach jedem Phasenwechsel soll in der Konsole
eine entsprechende Ausgabe erscheinen:

*Ausgabe*:

```cpp
TrafficLight: Variant 01
Red Light
Green Light
Yellow Light
Red Light
Green Light
... 
... 
... 
```

Welches klassische Entwurfsmuster bietet sich zur Realisierung an?

###### Zusatzaufgabe 1

Vielleicht ist es Ihnen schon aufgefallen:
Die meisten Menschen in Deutschland denken, dass eine Ampel nur drei verschiedene Schaltphasen hat, nämlich grün, gelb und rot!
Das ist aber verkehrt, nach rot wird die Ampel nicht wieder gelb sondern **rot-gelb**!

Erweitern Sie die vorliegende Lösung so, dass sie vier Ampelphasen besitzt.

###### Zusatzaufgabe 2

Zusätzlich zum eigentlich zu wählenden Entwurfsmuster bietet sich in der 
Realisierung ein zweites Entwurfsmuster an: Das *Singleton* Muster.

Erstellen Sie eine zweite Realisierung, die die erste Implementierung
um die Integration des *Singleton* Musters ergänzt.

---

#### Lösung

[Siehe hier](Solution.md)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---
