# Observer Pattern

---

[Zurück](../../Readme.md)

---

// https://refactoring.guru/design-patterns/observer/cpp/example#example-0




Etwas zur Realisieurng mit den Shared Pointer sagen:

a)  Wie mache ich das, wenn ich in der Klasse nen shared Poitner haben möchget:

mit 
 public std::enable_shared_from_this<Observer> und

DAs ist dann die dritte Variante

mIT der Methoden

        //void removeMeFromTheList() {
        //    std::shared_ptr<Observer> me = shared_from_this();
        //    m_subject->detach(me);
        //    std::cout << "Observer \"" << m_number << "\" removed from the list.\n";
        //}

Achtung; Der Aufruf shared_from_this geht aber nur, wenn es von dem Objekt bvereits einen Shared Pointer gibt.
Deshalb ist die Methoden XXX realisierbar, aber nicht das Gegenstück beim Anmelden ....

also 

  * erste Variante: klassich
  * zweite mit shared pointer
  * dritte mit shared_from_this


