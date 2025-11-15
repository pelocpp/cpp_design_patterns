# Observable Vector Container

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

#### Aufgabe

Schreiben Sie eine Klassenschablone, die sich wie die Standardklasse `std::vector` verhält,
aber registrierte Objekte über interne Zustandsänderungen informieren kann.
Die Klasse sollte mindestens die folgenden Operationen bereitstellen:

  * Verschiedene Konstruktoren zum Erstellen neuer Instanzen der Klasse,
  * Wertzuweisungsoperator `operator=` um dem Container Werte zuzuweisen,
  * Methode `push_back`, um ein neues Element am Ende des Containers hinzuzufügen,
  * Methode `pop_back`, um das letzte Element aus dem Container zu entfernen,
  * Methode `clear`, um alle Elemente des Containers zu entfernen,
  * Methode `size`, um die Anzahl der Elemente des Containers zu bestimmen sowie eine
  * Methode `empty`, die angibt, ob der Container leer ist oder Elemente enthält.

Bei einem Aufruf von 
`operator=`, `push_back`, `pop_back` und `clear` sind angemeldete Clients über den Statuswechse zu informieren.
Die Benachrichtigung sollte die Art der Änderung beschreiben und, falls dies der Fall ist,
den Index des Elements enthalten, das geändert wurde (z.B. Element hinzugefügt oder entfernt).

Welches klassische Entwurfsmuster bietet sich zur Realisierung an?

Schreiben Sie eine Testfunktion, die alle beschriebenen Methoden und Operatoren testet.

---

#### Lösung

[Siehe hier](Solution.md)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

