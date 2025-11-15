# Genehmigungssystem

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall des *Chain of Responsibility* Entwurfsmusters.

Die Aufgabenstellung könnte man in einer Kaskade von `if… else if… else… endif` Bedingungsanweisungen umsetzen.
Eine objektorientierte Version dieser Anweisungsfolge ist das *Chain of Responsibility* Entwurfsmuster.
Dieses Muster definiert eine Kette von Empfängerobjekten, die die Verantwortung haben,
eine Anfrage zu bearbeiten oder an den nächsten Empfänger in der Kette weiterzuleiten, falls einer vorhanden ist.
Das folgende Klassendiagramm zeigt eine mögliche Implementierung des Entwurfsmuster für dieses Problem:

<img src="dp_chain_of_responsibility_pattern.svg" width="800">

Abbildung 1: Schematische Darstellung des *Chain of Responsibility* Patterns im Anwendungsfall *Approval System*.


`Employee` ist eine Klasse, die einen Mitarbeiter im Unternehmen repräsentiert.
Ein Mitarbeiter kann einen direkten Vorgesetzten haben,
der mit einem Aufruf der Methode `setDirectManager` festgelegt wird.
Jeder Mitarbeiter hat einen Namen und eine Rolle, die seine Verantwortlichkeiten und Berechtigungen definieren.
`Role` ist eine abstrakte Basisklasse für mögliche Rollen und hat eine rein virtuelle (*pure virtual*)
Methode `getApprovalLimit`, die Klassen wie `EmployeeRole`,
`TeamManagerRole`, `DepartmentManagerRole` und `CEORole` überschreiben, um auf diese Weise
zum Ausdruck zu bringen, bis zu welchem Betrag ein Mitarbeiter Ausgaben genehmigen darf.
Die `approve`-Methode aus der Klasse `Employee` dient dem Zweck, einen Mitarbeiter eine Ausgabe genehmigen zu lassen.
Wenn die Rolle des Mitarbeiters dies ihm ermöglicht, gibt er die Ausgabe frei.
Andernfalls wird die Anforderung an den direkten Manager weitergeleitet, sofern dieser vorhanden ist.


*Beispiel*:

```cpp
std::unique_ptr<Role> role1 = std::make_unique<EmployeeRole>();
std::shared_ptr<Employee> cliff = 
    std::make_shared<Employee>("Cliff Booth", std::move(role1));

std::unique_ptr<Role> role2 = std::make_unique<TeamManagerRole>();
std::shared_ptr<Employee> rick = 
    std::make_shared<Employee>("Rick Dalton", std::move(role2));

std::unique_ptr<Role> role3 = std::make_unique<DepartmentManagerRole>();
std::shared_ptr<Employee> randy =
    std::make_shared<Employee>("Randy Miller", std::move(role3));

std::unique_ptr<Role> role4 = std::make_unique<CEORole>();
std::shared_ptr<Employee> marvin = 
    std::make_shared<Employee>("Marvin Shwarz", std::move(role4));

cliff->setDirectManager(rick);
rick->setDirectManager(randy);
randy->setDirectManager(marvin);

cliff->approve(Expense{ 500, "Magazins" });
rick->approve(Expense{ 5000, "Hotel Accomodation" });
randy->approve(Expense{ 50000, "Conference costs" });
marvin->approve(Expense{ 200000, "New Truck" });
```


*Ausgabe*:

```cpp
Cliff Booth approved expense 'Magazins', cost=500
Rick Dalton approved expense 'Hotel Accomodation', cost=5000
Randy Miller approved expense 'Conference costs', cost=50000
Marvin Shwarz approved expense 'New Truck', cost=200000
```

---

#### Quellcode

[Siehe hier](../ApprovalSystem.cpp)

---

[Zurück](Readme.md)

---
