# Entwurfsprinzipien (SOLID)

[Zurück](../Readme.md)

---

#### Grundlagen 

*Abstrakte Klassen* und *Schnittstellen* werden beide verwendet,
um Abstraktionen zu erreichen.

Einen Überblick zu abstrakten Klassen und Schnittstellen
finden Sie [hier](../Patterns/AbstractClassVsInterface/Resources/Readme.md).

---


Neben *Entwurfsmustern* gibt es in der Softwareentwicklung auch *Entwurfsprinzipien*.
Hierunter versteht man Prinzipien, die die Erzeugung wartbarer und erweiterbarer Software ermöglichen.

#### Robert Cecil Martin 

Fünf der bekanntesten dieser Prinzipien - **SOLID** - wurden von Robert Cecil Martin formuliert,
einem US-amerikanischen Softwareentwickler, IT-Berater und Schriftsteller.

Interessant sind unter anderem viele seiner Aussagen zum Altern von Software:

  * Auch Software unterliegt einem Alterungsprozess
  * Symptome des Alterungsprozesses:
    * Änderungen sind schwer einzupflegen
    * Anpassungen an geänderte Programmumgebungen wie z. B. Frameworks sind schwer durchzuführen
  * &bdquo;Software verrottet und stinkt&rdquo; (Robert C. Martin)
  * Grund: Zu viele Abhängigkeiten im Design
  * Starke Kopplung der Software-Komponenten führt dazu, dass bei Änderungen unerwünschte Nebeneffekte auftreten

Die Folge: Laufendes Refactoring oder komplette Neuentwicklung der Software sinnvoll!

Gute Software soll

  * erweiterbar,
  * korrekt,
  * stabil,
  * so einfach wie möglich und
  * verständlich dokumentiert sein.

sein. Um die genannten Ziele erreichen zu können, gibt es
Prinzipien und Konzepte, die beim Entwurf einzuhalten sind.
Diese kann man folgendermaßen unterteilen:

  * Prinzipien zum Entwurf von Systemen
  * Prinzipien zum Entwurf einzelner Klassen
  * Prinzipien zum Entwurf miteinander kooperierender Klassen

---

#### SOLID

Robert C. Martin - auch unter den Spitznamen &bdquo;*Uncle Bob*&rdquo; bzw. &bdquo;*that guy from ObjectMentor*&rdquo; bekannt - 
fasste eine wichtige Gruppe von Prinzipien zur
Erzeugung wartbarer und erweiterbarer Software unter dem Begriff
**SOLID** zusammen. Dieser Begriff soll andeuten, dass diese Prinzipien für
das Schreiben hochwertiger Software unabdingbar sind. Robert C. Martin
erklärte diese Prinzipien zu den wichtigsten Entwurfsprinzipien:

  * [**S**ingle Responsibility Prinzip (SRP)](../Patterns/SOLID/Resources/SingleResponsibilityPrinciple.md)
  * [**O**pen-Closed Prinzip (OCP)](../Patterns/SOLID/Resources/OpenClosedPrinciple.md)
  * [**L**iskovsches Substitutionsprinzip (LSP)](../Patterns/SOLID/Resources/LiskovSubstitutionPrinciple.md)
  * [**I**nterface Segregationsprinzip (ISP)](../Patterns/SOLID/Resources/InterfaceSegregationPrinciple.md)
  * [**D**ependency Inversion Prinzip (DIP)](../Patterns/SOLID/Resources/DependencyInversionPrinciple.md)

Im Überblick betrachtet lassen sich diese Prinzipien wie folgt zusammenfassen:

  * *Single Responsibility Prinzip*:<br/>Die Regel besagt, dass es für jede Klasse nur einen Grund für Veränderung geben darf &ndash; anders gesagt, jede Klasse solle nur genau eine fachliche Verantwortlichkeit abdecken.
  * *Open Closed Prinzip*:<br/>Klassen sollten sich erweitern lassen, ohne dass sich dadurch ihr Verhalten ändert. Eine Klasse sollte also offen für Erweiterung, aber geschlossen hinsichtlich der Änderungen sein.
  * *Liskovsches Substitutionsprinzip*:<br/>Dass sich eine abgeleitete Klasse stets so zu verhalten habe, wie die zugrunde liegende Basisklasse, fordert das LSP. Das Ziel ist, jederzeit an Stelle der Superklasse eine Subklasse ohne semantische Änderungen verwenden zu können.
  * *Interface Segregation Prinzip*:<br/>Große Interfaces sind auf mehrere kleine aufzuteilen, sodass ein Verwender nur genau jene Interfaces implementieren muss, die tatsächlich notwendig sind.
  * *Dependency Inversion Prinzip*:<br/>Abhängigkeiten sollten stets von konkreten zu abstrakten Modulen verlaufen, sodass konkrete Implementierungen leichter auszutauschen sind und sich voneinander entkoppeln lassen.

---

#### Weitere Entwurfsprinzipien

SOLID ist bei weitem nicht die einzige Gruppe von Prinzipien für den Entwurf von Software.
Um den Charakter eines einführenden Textes nicht zu verlassen,
führe ich in tabellarischer Form - und vor allem ohne jeglichen Anspruch auf Vollständigkeit -
weitere Entwurfsprinzipien aus:

| Entwurfsprinzip | Kurzbeschreibung |
|:-------|----|
| **KISS** | &bdquo;Keep it simple and stupid&rdquo; - Strebe zu einem Problem immer eine möglichst einfache Lösung an. |
| **DRY** | &bdquo;Don't repeat yourself&rdquo; - Redundant vorhandener Quellcode ist nur aufwändig einheitlich zu pflegen. Bei Systemen, die dem DRY-Prinzip treu sind, brauchen Änderungen nur an einer Stelle vorgenommen zu werden. |
| **YAGNI** | &bdquo;You aren't gonna need it&rdquo; - &bdquo;Implementiere Dinge immer dann, wenn Du sie tatsächlich brauchst, niemals, wenn Du nur der Meinung bist, dass Du sie brauchst!&rdquo; |
| **Separation of Concerns** | Das &bdquo;Separation of Concerns&rdquo; (**SoC**) Prinzip ist eines der grundlegendsten Prinzipien in der Softwareentwicklung. Es ist so wichtig, dass zwei der fünf SOLID-Prinzipien (*Single Responsibility* und *Interface Segregation*) direkte Ableitungen von diesem Konzept sind. Die Aussage des Prinzips ist einfach: Schreiben Sie Ihr Programm nicht als einen festen Block, sondern teilen Sie den Code in Blöcke auf, die winzige Teile des Systems sind, die jeweils einen einfachen, unterschiedlichen Auftrag ausführen. |

Tabelle 1. Weitere Entwurfsprinzipien.

---

## Literaturhinweise

[My 5 Favorite Software Design Principles](https://dev.to/pluralsight/my-5-favorite-software-design-principles-4ech)

---

[Zurück](../Readme.md)

---

