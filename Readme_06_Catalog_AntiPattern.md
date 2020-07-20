# Katalog der Anti-Pattern

## Überblick

Neben Entwurfsmustern gibt es auch so genannte Anti-Entwurfsmuster: Hierunter verstehen wir offensichtlich
(bekannte) Vorgehensweisen in der Software-Entwicklung, denen bereits zu Beginn des Entwicklungsprozesses
schlechte Aussichten auf eine qualitativ gelungenge Architektur bescheinigt werden kann:


| Anti-Pattern | Kurzbeschreibung |
|:-------------- |----|
| The Blob | Steht für eine einzelne Klasse, die die Verarbeitung monopolisiert und andere sekundäre Klassen, die letzen Endes nur Daten kapseln. |
| Continuous Obsolescence | Kontinuierliche Veralterung / Beschreibt eine Technologie, die sich so schnell ändert, dass Entwickler Probleme haben, mit den aktuellen Softwareversionen Schritt zu halten und Kombinationen von Produktversionen zu finden, die zusammenarbeiten. |
| Lava Flow | Das *Lava Flow* Anti Pattern ist häufig in Systemen zu finden, die aus der Forschung heraus entstanden sind, aber in der Produktion gelandet sind. Es ist gekennzeichnet durch lavaartige "Flüsse" früherer Entwicklungsversionen, die über die Codelandschaft verstreut sind und sich nun zu einer basaltartigen, unbeweglichen, im Allgemeinen nutzlosen Codemasse verhärtet haben, an die sich niemand mehr erinnern kann. |
| Ambiguous Viewpoint | Objektorientierte Analyse- und Entwurfsmodelle (OOA&D) werden häufig dargestellt, ohne den vom Modell dargestellten Gesichtspunkt zu klären (Geschäfts-, Spezifikations- oder Implementierungsstandpunkt). |
| Functional Decomposition | Resultat von nicht objektorientierten Entwicklern, die eine Anwendung in einer objektorientierten Sprache entwerfen und implementieren. |
| Poltergeists | Poltergeister sind Klassen mit begrenzten Verantwortlichkeiten und Rollen, die im System benötigt werden. Daher ist ihr effektiver Lebenszyklus recht kurz. Poltergeister überladen Software-Design und erzeugen unnötige Abstraktionen. Sie sind übermäßig komplex, schwer zu verstehen und schwer zu pflegen. |
| Boat Anchor | Unter einem „*Bootsanker*“ („*Boat Anchor*“) versteht man Software (oder Hardware), die im aktuellen Projekt keinen nützlichen Zweck erfüllt. Oft ist der „*Bootsanker*“ eine kostspielige Anschaffung, was den Kauf noch ironischer macht. |
| Golden Hammer | Eine vertraute Technologie oder ein bekanntes Konzept, das zwanghaft auf (zu viele) Softwareprobleme angewendet wird. |
| Dead End | Die direkte Änderung von kommerzieller Software oder wiederverwendbarer Software führt zu erheblichen Aufwendungen in der Wartung eines Softwaresystems. Das „*Dead End*“ wird durch Ändern einer wiederverwendbaren Komponente erreicht, wenn die geänderte Komponente nicht mehr vom Lieferanten gewartet und unterstützt wird. |
| Spaghetti Code | Ad-hoc-Softwarestrukturen machen es schwierig, die Software zu erweitern und und den Code zu optimieren. „*Spaghetti-Code*“ zeugt von Software, die nur sehr wenig Softwarestruktur enthält. Codierung und progressive Erweiterungen beeinträchtigen die Softwarestruktur in einem solchen Ausmaß, dass die Struktur selbst für den ursprünglichen Entwickler nicht klar genug ist, wenn dieser für längere Zeit von der Software entfernt ist. |
| Input Kludge | Ein *Input Kludge* - zu deutsch etwa "Eingabe-Flickschusterei, -Behelfslösung" ist eine Art von Fehler in der Software (ein Anti-Pattern), bei dem einfache Benutzereingaben nicht richtig behandelt werden. |
| Walking through a Minefield | Der Gebrauch von Software, die zum Kunden ausgeliefert wurde, kann mit dem Gehen durch ein Minenfeld verglichen werden. Dieses Mini-Anti-Muster ist auch bekannt als *Nothing Works* oder *Do You Believe in Magic*? In freigegebenen Softwareprodukten treten zahlreiche Fehler auf. Experten schätzen, dass der ursprüngliche Quellcode zwei bis fünf Fehler pro Codezeile enthält. Dies bedeutet, dass der Code zwei oder mehr Änderungen pro Zeile erfordert, um alle Fehler zu beseitigen. |
| Cut-and-Paste Programming | Durch das Kopieren von Quellanweisungen wiederverwendeter Code führt zu erheblichen Wartungsproblemen. |
| Mushroom Management | In einigen Software-Architekturkreisen gibt es eine explizite Richtlinie, die besagt, dass Systementwickler von den Endbenutzern des Systems zu isolieren sind. Anforderungen werden aus zweiter Hand von Vermittlern weitergeleitet, einschließlich Architekten, Managern oder Anforderungsanalysten. „*Mushroom Management*“ legt zugrunde, dass die Anforderungen sowohl vom Endbenutzer als auch von den Entwicklern gut verstanden werden. Ferner wird davon ausgegangen, dass die Anforderungen stabil sind. |

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

## Einige Antipattern im Detail

#### Input Kludge 

##### Beschreibung

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


#### Interface Bloat

##### Beschreibung

*Interface Bloat*, von Bjarne Stroustrup auch als *Fat Interfaces* und von Martin Fowler als *Refused Bequests* bezeichnet,
sind Interfaces (Zusammenfassung mehrerer Methodenschnittstellen), die zu viele Methoden in einer einzigen Schnittstelle integrieren.
Wollte man eine derartige Schnittstelle implementieren, stellt man fast, dass die meisten Klassen auf Grund der Komplexität der Schnittstelle
keine Realisierung bereitstellen können.

##### Abhilfe

Folge dem "Interface Segregation" Prinzip: Das Prinzip besagt, dass im Bereich der Softwareentwicklung kein
Entwickler einer Klasse gezwungen werden sollte, Methoden zu implementieren, die er nicht verwendet/benötigt.

Das "Interface Segregation Principle" (ISP) teilt sehr große Schnittstellen in kleinere und spezifischere Schnittstellen auf,
sodass Clients nur die für sie interessanten Methoden kennen müssen.
Solche geschrumpften Schnittstellen werden auch Rollenschnittstellen (role interfaces) genannt. 

Die Intention von ISP ist es, eine Menge von Klassen entkoppeln zu können und somit flexibler interagieren zu können in Bezug auf
"Klassen umgestalten, ändern und neu bereitstellen"

ISP ist eines der fünf SOLID-Prinzipien des objektorientierten Designs!

#### Race Conditions

##### Beschreibung

Unter einer "Race-Condition" versteht man im Ablauf eines multi-threading / multi-processing Programms eine Situation,
die auftritt, wenn versucht wird, zwei oder mehr Funktionen/Methoden gleichzeitig ("parallel") auszuführen.
Aufgrund der Art des Geräts oder Systems müssen die Vorgänge jedoch sequentiell ausgeführt werden,
um korrekt ausgeführt zu werden.

##### Abhilfe

Mutex.

---

[Zurück](Readme.md)

---


#### Weiterarbeit

Ein interessantes Anti-Pattern zu einfachen Datenstrukturen findet sich unter

[Simple data structures](https://arne-mertz.de/2018/12/simple-data-structures/) (Abruf am 20.07.2020)
