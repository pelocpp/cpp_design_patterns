# Dependency Inversion Prinzip

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---

## Wesentliche Merkmale


#### Ziel / Absicht:

  * &ldquo;High-Level&rdquo;-Module sollten nicht von &ldquo;Low-Level&rdquo;-Modulen abhängen. Beide sollten von Abstraktionen abhängen.
  * Abstraktionen sollten nicht von Details abhängen. Details sollten von Abstraktionen abhängen.

Die obigen Zeilen mögen zunächst kryptisch erscheinen, wir versuchen sie anhand eines Beispiels zu erläutern:

Was versteht man eigentlich unter &ldquo;High-Level&rdquo;- und &ldquo;Low-Level&rdquo;-Modulen?

  * &ldquo;High-Level&rdquo;-Module: Beschreiben Operationen, die abstrakter Natur sind und komplexere Logik enthalten. Diese
    Module orchestrieren typischerweise die &ldquo;Low-Level&rdquo;-Module in einer Anwendung.

  * &ldquo;Low-Level&rdquo;-Module: beschreiben Implementierungen in einer spezifischeren und individuelleren Weise
    und legen den Fokus mehr auf die Details der Anwendung.
    Diese Module werden von den &ldquo;High-Level&rdquo;-Modulen verwendet.

#### Beispiel: Violating the Dependency Inversion Principle

```cpp
```

Erkennen Sie die Nachteile dieser Implementierung?

  * Wenn zu einem späteren Zeitpunkt in der Klasse `Relationships` der Container der Beziehungen von `std::vector`
    zu `std::`set` oder einem anderen Container geändert wird, kann dies Auswirkungen auf Klasse `FamilyTree` haben:
    Dies stellt definitiv kein gutes Design dar!

  * &ldquo;Low-Level&rdquo;-Module, z.B. Klasse `Relationships` hängen direkt vom &ldquo;High-Level&rdquo;-Modul ab (hier: Klasse `FamilyTree`).
    Dies stellt eine Verletzung von DIP dar.

Stattdessen sollten wir vom &ldquo;Low-Level&rdquo;-Modul eine Abstraktion erstellen und &ldquo;Low-Level&rdquo;- und &ldquo;High-Level&rdquo;-Module an diese Abstraktion binden.
Betrachten Sie die folgende Lösung:

#### Beispiel: Respecting the Dependency Inversion Principle

```cpp
```

###### Beachten Sie an dem Quellcode:

  * Egal, ob der Name des &ldquo;Low-Level&rdquo;-Moduls oder eines in diesem Modul enthaltenen Sub-Containers selbst sich ändert,
    das &ldquo;High-Level&rdquo;-Modul oder andere Quellcode-Anteile, die dem Dependency Inversion Prinzip folgten, bleiben intakt.

  * Das Dependency Inversion Prinzip (DIP) legt nahe, dass die flexibelsten Systeme diejenigen sind, in denen sich Quellecodeabhängigkeiten
    nur auf Abstraktionen, nicht auf Konkretisierungen beziehen!


#### Vorteile des *Dependency-Inversion-Prinzips*

Effektiv gesehen reduziert das Dependency Inversion Prinzip (DIP) die Kopplung zwischen verschiedenen Codeteilen.
Wir erhalten auf diese Weise wiederverwendbaren Code.

---

Die Anregungen zu diesem Beispiel finden Sie in

[Open Closed Principle in C++](http://www.vishalchovatiya.com/open-closed-principle-in-cpp-solid-as-a-rock/)

von Vishal Chovatija.

---

[Zurück](../../../Resources/Readme_03_Design_Principles.md)

---


