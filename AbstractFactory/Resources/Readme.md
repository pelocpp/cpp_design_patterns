# Abstract Factory

## Wesentliche Merkmale

##### Kategorie: Erzeugungsmuster / *Creational Pattern*

#### Ziel / Absicht:

Das *Abstract Factory* Pattern ist ein Entwurfsmuster,
mit dem Gruppen verwandter Objekte erstellt werden können,
ohne dass die genauen konkreten Klassen angegeben werden müssen, die verwendet werden sollen.
Eine von mehreren Factory-Klassen generiert die jeweiligen Objektmengen.

#### Struktur (UML):

<img src="dp_abstract_factory.png" width="600">

Abbildung 1: Schematische Darstellung des *Abstract Factory* Entwurfsmusters.

#### 'Real-World' Example:

Im  'Real-World' Beispiel zu diesem Entwurfsmuster wird
die Herstellung verschiedener Fahrzeugtypen verschiedener Hersteller betrachtet.
Es gibt eine abstrakte Fabrikschnittstelle namens `IVehicleFactory` (*abstract Factory*)
und zwei konkrete Fabrikimplementierungen namens `FordFactory`  und `MitsubishiFactory`. 
`IVehicleFactory` verfügt über drei Methoden `createEconomyCar`, `createRacingCar` und `createSUV`,
mit denen `Vehicle`-Objekte zurückgegeben werden.
Die Klasse `Vehicle` ist eine abstrakte Basisklasse für alle konkreten Produkte.

---

[Zurück](../../Readme_05_Catalog.md)

---
