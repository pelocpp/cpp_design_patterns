# Katalog der Anti-Pattern

TODO: 

Ebenfalls einführen

https://arne-mertz.de/2018/12/simple-data-structures/

als Anti-Pattern

Neben Entwurfsmustern gibt es auch so genannte Anti-Entwurfsmuster: Hierunter verstehen wir offensichtlich
(bekannte) Vorgehensweisen in der Software-Entwicklung, denen bereits zu Beginn des Entwicklungsprozesses
schlechte Aussichten auf eine qualitativ gelungenge Architektur bescheinigen kann:

| Anti-Pattern | Kurzbeschreibung |
|:-------------- |----|
| The Blob | TBD |
| Continuous Obsolescence | TBD |
| Lava Flow | TBD |
| Ambiguous Viewpoint | TBD |
| Functional Decomposition | TBD |
| Poltergeists | TBD |
| Boat Anchor | TBD |
| Golden Hammer | TBD |
| Dead End | TBD |
| Spaghetti Code | TBD |
| Input Kludge | TBD |
| Walking through a Minefield | TBD |
| Cut-and-Paste Programming | TBD |
| Mushroom Management | TBD |

Tabelle 1. Anti-Pattern

Weitere Anti-Pattern:

| Anti-Pattern | Kurzbeschreibung |
|:-------------- |----|
| God Object | TBD |
| Input Kludge | TBD |
| Interface Bloat | TBD |
| Race Conditions | TBD |
| Circular Dependency | TBD |
| Copy and Paste Programming | TBD |

Tabelle 2. Weitere Anti-Pattern


## Input Kludge 

#### Beschreibung

Ein *Input Kludge* - zu deutsch etwa "Eingabe-Flickschusterei, -Behelfslösung" ist eine Art von Fehler in der Software (ein Anti-Pattern),
bei dem einfache Benutzereingaben nicht richtig behandelt werden.
Dies kann zu Abstürzen beim Pufferüberlauf führen.

Bekannteste Vertreter:

  * CRT (C-Runtime-Library)

```cpp
strcpy 
```

  * SQL Injection

```cpp
<form action=‘index.php’ method="post">
    <input type="email" name="email" required="required"/>
    <input type="password" name="password"/>
    <input type="checkbox" name="remember_me" value="Remember me"/>
    <input type="submit" value="Submit"/>
</form>
```

Siehe eine Beschreibung hier:

[SQL Injection Tutorial](https://www.guru99.com/learn-sql-injection-with-practical-example.html)

#### Abhilfe

## Interface Bloat

#### Beschreibung

*Interface Bloat*, von Bjarne Stroustrup auch als *Fat Interfaces* und von Martin Fowler als *Refused Bequests* bezeichnet,
sind Interfaces (Zusammenfassung mehrerer Methodenschnittstellen), die zu viele Methoden in einer einzigen Schnittstelle integrieren.
Wollte man eine derartige Schnittstelle implementieren, stellt man fast, dass die meisten Klassen auf Grund der Komplexität der Schnittstelle
keine Realisierung bereitstellen können.

#### Abhilfe

Folge dem "Interface Segregation" Prinzip: Das Prinzip besagt, dass im Bereich der Softwareentwicklung kein
Entwickler einer Klasse gezwungen werden sollte, Methoden zu implementieren, die er nicht verwendet/benötigt.

Das "Interface Segregation Principle" (ISP) teilt sehr große Schnittstellen in kleinere und spezifischere Schnittstellen auf,
sodass Clients nur die für sie interessanten Methoden kennen müssen.
Solche geschrumpften Schnittstellen werden auch Rollenschnittstellen (role interfaces) genannt. 

Die Intention von ISP ist es, eine Menge von Klassen entkoppeln zu können und somit flexibler interagieren zu können in Bezug auf
"Klassen umgestalten, ändern und neu bereitstellen"

ISP ist eines der fünf SOLID-Prinzipien des objektorientierten Designs!

## Race Conditions

#### Beschreibung

Unter einer "Race-Condition" versteht man im Ablauf eines multi-threading / multi-processing Programms eine Situation,
die auftritt, wenn versucht wird, zwei oder mehr Funktionen/Methoden gleichzeitig ("parallel") auszuführen.
Aufgrund der Art des Geräts oder Systems müssen die Vorgänge jedoch sequentiell ausgeführt werden,
um korrekt ausgeführt zu werden.

#### Abhilfe

Mutex.

---

[Zurück](Readme.md)

---


