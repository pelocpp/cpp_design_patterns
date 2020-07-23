# Observer Pattern

## Wesentliche Merkmale

#### Kategorie: *Behavioral Pattern*

#### Ziel / Absicht:

Das *Observer Pattern* ist ein Entwurfsmuster aus der Kategorie der *Behavioral Pattern*,
mit dem Sie einen Mechanismus für Benachrichtigungen definieren,
um Objekte über Ereignisse zu informieren, die in einem beobachteten Objekt auftreten.

#### Problem:

Betrachten wir als Szenario ein Beispiel mit zwei Arten von Objekten:
mehrere Kunden und ein Geschäft. Der Kunde ist an einem bestimmten Produkt interessiert,
das bald erhältlich sein soll.

Der Kunde kann das Geschäft jeden Tag aufsuchen oder die entsprechende WebSite konsultieren,
um die Verfügbarkeit des Produkts zu überprüfen.
Solange das Produkt aber noch gefertigt wird oder sich auf dem Versand zum Geschäft befindet,
sind all diese Nachfragen sinnlos.

Auf der anderen Seite könnte der Laden genau dann, wenn das Produkt abholbereit ist,
dem oder den interessierten Kunden eine Nachricht zukommen lassen. Auf diese Weise
ist die Information über die Verfügbarkeit am effizientesten gegeben.


#### Lösung:

Das Objekt, das den bereitzustellenden Status besitzt, wird häufig als "*Subject*" oder auch
"*Publisher*" bezeichnet. Diejenigen Objekte, die die Änderungen am Status des *Publishers* verfolgen,
werden als "*Subscriber*" oder auch "*Observer*" bezeichnet. Das Pendant eines "*Observers*"
kann man auch als "*Observable*" bezeichnen.

Das *Observer Pattern* sieht vor, dass das "*Subject*" einen Benachrichtigungsmechanismus der Gestalt aufweist, 
dass einzelne Objekte (*Subscriber*) sich für das Benachrichtigen von Ereignissen
an- und abmelden können.

Typischerweise lässt sich diese Funktionalität mit einer Liste (`std::list` oder ähnliches)
zum Speichern von Verweisen auf *Subscriber*-Objekte realisieren.
Dazu gehören dann meist zwei Methoden (zum Beispiel `register` und `unregister`, `add` und `remove` oder `attach` und `detach`),
um *Subscriber* zu dieser Liste hinzuzufügen und aus dieser wieder zu entfernen.


#### Struktur (UML):

<img src="dp_observer_01.png" width="400">

Abbildung 1: Schematische Darstellung des *Observer Pattern Musters*: An- und Abmelden.

<img src="dp_observer_02.png" width="500">

Abbildung 2: Schematische Darstellung des *Observer Pattern Musters*: Benachrichtigungen.

<img src="dp_observer_03.png" width="700">

Abbildung 3: Schematische Darstellung des *Observer Pattern Musters*: Abstraktion des Observers mittels Schnittstelle `IObserver`. 


#### Conceptual Example:

Die Anregung zum konzeptionellen Beispiel finden Sie unter

[https://refactoring.guru/design-patterns](https://refactoring.guru/design-patterns/observer/cpp/example#example-0)

vor.

**Hinweis**:

Das *Conceptual Example* liegt in drei Varianten vor:

  * Variante 1: klassisch - d.h. mit "raw"-Zeigern.
  * Variante 2: Mit `std::shared_ptr` Objekten.
  * Variante 3: Wie Variante 2, aber mit `std::enable_shared_from_this<>` Mechanismus.

In Variante 2 wird prinzipiell ohne "raw"-Zeiger gearbeitet, also so,
wie man es der "reinen Lehre" nach machen sollte. Dabei stellt sich aber eine Frage:
Wie erhalte ich von einem Objekt einen `std::shared_ptr`, desses Objekterzeugung
außerhalb meines Wirkungskreises liegt. Die Frage lautet also gewissermaßen:

```cpp
std::shared_ptr<IObserver> me = this;
```

Das geht so nicht, wie zu erwarten war. Es gibt aber den folgenden Weg:

```cpp
class Observer : public IObserver, public std::enable_shared_from_this<Observer> {
    ...
}
```

Die Klasse `Observer` leitet sich von einer Standard-Klasse `std::enable_shared_from_this<>` ab,
die genau zu diesem Zweck realisiert wurde.
Damit vererbt sie eine Methode `shared_from_this` an die Kindklasse.
Auf diese Weise kann man dann beispielsweise eine Methode `removeMeFromTheList`
wie folgt implementieren:

```cpp
void removeMeFromTheList() {
    std::shared_ptr<Observer> me = shared_from_this();
    m_subject->detach(me);
    std::cout << "Observer \"" << m_number << "\" removed from the list.";
}
```

**Achtung**: Der Aufruf `shared_from_this` ist aber nur dann zulässig,
wenn es von dem Objekt (hier: Klasse `Observer`) bereits einen Shared Pointer gibt!
Das muss nicht immer der Fall sein!
Deshalb ist in der vorliegenden Fallstudie zumindest eine Methode im Stile von `removeMeFromTheList` realisierbar,
aber nicht ein entsprechendes Gegenstück zum Anmelden. Weitere Details der Realisierung
entnehmen Sie bitte der dritten Variante des *Conceptual Example*.


#### Beginners Example:

#### 'Real-World' Beispiel:


## Literaturhinweise

*Hinweise*:

---

[Zurück](../../../Resources/Readme_05_Catalog.md)

---
