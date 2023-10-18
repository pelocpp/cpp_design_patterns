# Active Object Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: *Concurrency Pattern*

###### In einem Satz:

&ldquo;*Active Object* ist ein *Concurrency Pattern*, bei dem man versucht, den Aufruf einer Methode von ihrer Ausführung zu trennen.&rdquo;

#### Ziel / Absicht:

Das *Active Object* entkoppelt den Methodenaufruf von der Methodenausführung.
Der Methodenaufruf wird im Kontext des Client-Threads ausgeführt,
die Methodenausführung selbst in einem Thread des *Active Objects*.

Das *Active Object* verwaltet (mindestens) einen Thread (Kontrollthread) und eine Liste (Warteschlange)
von Objekten, die einen Methodenaufruf beschreiben und die auszuführen sind.

Ein Methodenaufruf eines Clients reiht einen *Request* in der Warteschlange des *Active Objects* ein (auch als *ActivationList* bezeichnet).
Derartige *Requests* können bei der Ausführung an einen Server weitergeleitet werden.

Das Pattern wurde maßgeblich von *Douglas C. Schmidt* von der Vanderbilt University entwickelt.
Er beschreibt es in dem Buch
[Pattern-Oriented Software Architecture: Volume 2: Patterns for Concurrent and Networked Objects](https://www.amazon.de/Pattern-Oriented-Software-Architecture-Concurrent-Networked/dp/0471606952)
auf folgende Weise:

  > Das *Active Object Pattern* entkoppelt die Methodenausführung vom Methodenaufruf,
  um die Parallelität zu verbessern und den synchronisierten Zugriff auf Objekte zu vereinfachen,
  die sich in einem eigenen Kontrollthread befinden.

---

#### Struktur:

Die Schlüsselelemente des *Active Object* Patterns sind:

  * Proxy (oder auch Client) &ndash; Der Proxy stellt eine Schnittstelle für die öffentlichen Member-Funktionen
  des aktiven Objekts bereit. Der Proxy löst damit die Erstellung eines Request-Objekts
  in der *ActivationList* aus. Der Proxy läuft im Client-Thread.

  * Dispatch Queue (auch *ActivationList*) &ndash; Die Aktivierungsliste
  verwaltet die ausstehenden Anfragen. Die Aktivierungsliste entkoppelt den Thread des Clients
  vom Thread des aktiven Objekts. Der Proxy fügt Anforderungsobjekte ein und der Scheduler entfernt diese.
  Folglich muss der Zugriff auf die Aktivierungsliste serialisiert werden.

  * Scheduler &ndash; Der Scheduler läuft im Thread des aktiven Objekts und entscheidet, welche Anfrage aus der Aktivierungsliste als nächstes ausgeführt wird.

  * Result Handle (im Regelfall ein `std::future`-Objekt)  &ndash;
  Wenn der Request ein Ergebnis zurückgibt, erhält der Client zu diesem Zweck ein `std::future`-Objekt
  und kann dadurch das Ergebnis des Methodenaufrufs erhalten.
  Dieser Zugriff kann blockierend oder nicht-blockierend sein.

<img src="dp_active_object.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Active Object* Patterns.

---

#### Command Pattern

*Bemerkung*: Das *Active Object Pattern* weist Ähnlichkeiten zum *Command Pattern* auf. 
Im Prinzip beschreibt es eine Variante des *Command Patterns* ausgelegt für Nebenläufigkeit.

---

#### Conceptual Example:

Das konzeptionelle Beispiel soll in einer vereinfachenden Betrachtung
die Schlüsselelemente des *Active Object* Patterns vorstellen.

Es treten im *Active Object* ein Scheduler und eine so genannte *ActivationList* auf:
Unter einer *ActivationList* verstehen wir eine FIFO-Warteschlange,
die einzelne Methodenaufrufe verwaltet.

Das Beispiel ist mit C++ 11 Sprachmitteln realisiert.
Es orientiert sich stark an dem Beispiel aus
[Wikipedia](https://en.wikipedia.org/wiki/Active_object),
das dort in Java realisiert wird.

Das konzeptionelle Beispiel besitzt &ndash; in Folge seiner vereinfachenden Darstellung &ndash; einige Nachteile:

  * Client (Proxy) und *Active Object* werden durch dasselbe Objekt dargestellt.
  * Die Methodenaufrufe liefern keinen Ergebniswert zurück.

[Quellcode](../ConceptualExample.cpp)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[Revisiting the Active Object Pattern - with C++11 Closures](https://www.codeproject.com/Articles/991641/Revisiting-the-Active-Object-Pattern-with-Cplusplu).

Die anderen Beispiele orientieren sich an Beispiel aus dem Blog von Rainer Grimm:

[Active Object](https://www.modernescpp.com/index.php/active-object/)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
