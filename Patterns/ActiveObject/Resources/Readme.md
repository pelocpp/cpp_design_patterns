# Active Object Pattern

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

## Wesentliche Merkmale

#### Kategorie: *Concurrency Pattern*

###### In einem Satz:

&ldquo;*Active Object* ist ein *Concurrency Pattern*, bei dem wir versuchen, den Aufruf einer Methode von ihrer Ausführung zu trennen.&rdquo;

#### Ziel / Absicht:

Das *Active Object* entkoppelt den Methodenaufruf von der Methodenausführung.
Der Methodenaufruf wird im Kontext des Client-Threads ausgeführt,
die Methodenausführung jedoch in einem Thread des *Active Objects*.

Das *Active Object* verwaltet (mindestens) einen Thread (Kontrollthread) und eine Liste (Warteschlange)
von Methodenanforderungsobjekten, die auszuführen sind.

Ein Methodenaufruf des Clients reiht seine Anfrage in der Warteschlange (auch als *ActivationList* bezeichnet)
des *Active Objects* ein, die Anfrage kann bei Ausführung an einen Server weitergeleitet werden.

In der Regel stellt ein *aktives Objekt* synchrone Methoden bereit
und führt die korrespondierenden Methodenaufrufe asynchron aus.
Ein aktives Objekt verfügt normalerweise über einen eigenen Kontrollthread.

Das Pattern wurde maßgeblich von *Douglas C. Schmidt* von der Vanderbilt University entwickelt.
Er beschreibt es in dem Buch
[Pattern-Oriented Software Architecture: Volume 2: Patterns for Concurrent and Networked Objects](https://www.amazon.de/Pattern-Oriented-Software-Architecture-Concurrent-Networked/dp/0471606952)
auf folgende Weise:

  * Das *Active Object Pattern* entkoppelt die Methodenausführung vom Methodenaufruf,
  um die Parallelität zu verbessern und den synchronisierten Zugriff auf Objekte zu vereinfachen,
  die sich in eigenen Kontrollthreads befinden.

---

#### Struktur:

Die Schlüsselelemente des *Active Object* Patterns sind:

  * Proxy (oder auch Client) &ndash; Der Proxy stellt eine Schnittstelle für die öffentlichen Member-Funktionen
  des aktiven Objekts bereit. Der Proxy löst damit die Erstellung eines Request-Objekts
  in der *ActivationList* aus. Der Proxy läuft im Client-Thread.

  * Dispatch Queue (auch *ActivationList*) &ndash; Die Aktivierungsliste
  verwaltet die ausstehenden Anfragen. Die Aktivierungsliste entkoppelt den Thread des Clients
  vom Thread des aktiven Objekts. Der Proxy fügt das Anforderungsobjekt ein und der Scheduler entfernt es.
  Folglich muss der Zugriff auf die Aktivierungsliste serialisiert werden.

  * Scheduler &ndash; Der Scheduler läuft im Thread des aktiven Objekts und entscheidet, welche Anfrage aus der Aktivierungsliste als nächstes ausgeführt wird.

  * Result Handle (im Regelfall ein `std::future`-Objekt)  &ndash;
  Wenn der Request ein Ergebnis zurückgibt, erhält der Client zu diesem Zweck ein `std::future`-Objekt
  und kann dadurch das Ergebnis des Methodenaufrufs erhalten.
  Dieser Zugriff kann blockierend oder nicht-blockierend sein.

<img src="dp_active_object.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Active Object* Patterns.

---

#### Conceptual Example:

Das konzeptionelle soll in einer vereinfachenden Betrachtung
die Schlüsselelemente des *Active Object* Patterns vorstellen.

Es treten im *Active Object* ein Scheduler und eine so genannte *ActivationList* auf:
Unter einer *ActivationList* verstehen wir eine FIFO-Warteschlange,
die einzelne Methodenaufrufe verwaltet.

Das Beispiel ist mit C++ 11 Sprachmitteln realisiert.
Es orientiert sich stark an dem Beispiel aus
[Wikipedia](https://en.wikipedia.org/wiki/Active_object),
das dort in Java realisiert wird.

Das konzeptionelle Beispiel besitzt &ndash; in Folge einer vereinfachenden Darstellung &ndash; folgende Nachteile:

  * Client (Proxy) und *Active Object* werden durch dasselbe Objekt dargestellt.
  * Die Methodenaufrufe liefern keinen Ergebniswert zurück.

[Quellcode](../ConceptualExample.cpp)

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---

**Ab hier altes Zeugs**


---

## FAQs

*Frage*: Unterschied zwischen *Proxy*- und *Decorator*-Pattern?

  * Das *Proxy*-Pattern stellt im Wesentlichen dieselbe oder sogar eine verfeinfachte Schnittstelle dar.

  * Das *Decorator*-Pattern bewirkt eine Verfeinerung in der Ausgestaltung einer Schnittstelle.

---

## Literaturhinweise

Die Anregungen zum konzeptionellen Beispiel finden Sie unter

[Revisiting the Active Object Pattern - with C++11 Closures](https://www.codeproject.com/Articles/991641/Revisiting-the-Active-Object-Pattern-with-Cplusplu).


HIER ALTES ZEUGS

und 

[https://www.codeproject.com](https://www.codeproject.com/Articles/438922/Design-Patterns-2-of-3-Structural-Design-Patterns#Proxy)

vor.

Die beiden Beispiele &ldquo;Property Proxy&ldquo; und &ldquo;Virtual Proxy&ldquo;
stammen aus dem [Blog von Vishal Chovatiya](http://www.vishalchovatiya.com/proxy-design-pattern-in-modern-cpp/).

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
