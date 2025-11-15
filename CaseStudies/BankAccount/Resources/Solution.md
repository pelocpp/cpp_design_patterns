# Bankkonten eines Bankinstituts

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall des *Command Pattern* Entwurfsmusters.

Aus Grund von Demonstrationszwecken hat die `BankAccount`-Klasse
eine minimalistische Implementierung mit einem gewissen Startguthaben. 

Es gibt in dieser Klasse die beiden Methoden `deposit` und `withdraw`,
aber anstatt diese Methoden direkt zu verwenden,
erstellen wir eine separate Klasse `BankAccountCommand`, die sich als Backup von der abstrakten Klasse `Command`
ableitet.

In der Anwendung werden zwei `BankAccount`-Objekte angelegt
und simulieren die Überweisung von 300€ von einem Bankkonto auf ein anderes.

Jedes Kommando (`Command`) &ndash; sprich jedes `BankAccountCommand`-Objekt &ndash; bezieht sich auf ein bestimmtes Bankkonto,
so dass es weiß, auf welchem Konto es arbeiten soll.

Das folgende Klassendiagramm zeigt eine mögliche Implementierung des Entwurfsmuster für dieses Problem:

<img src="dp_bank_accounts.svg" width="700">

*Abbildung* 1: Schematische Darstellung des *Command* Patterns im Anwendungsfall &ldquo;*Bankkonten eines Bankinstituts*&rdquo;.

*Zusatzaufgabe*:

Betrachten Sie *Abbildung* 1 genau: Welches Manko erkennen Sie in der Klasse `Transactions`?
Wie könnten Sie dieses Manko beheben? Siehe dazu auch die Zusatzaufgabe weiter unten.

---

Im Quellcode finden Sie eine Umsetzung des Beispiels mit und ohne `Invoker`-Klasse vor.
Die etwas einfachere Variante (also ohne `Invoker`-Klasse) sieht so aus:

*Beispiel*:

```cpp
BankAccount ba1{ 1000 };
BankAccount ba2{ 1000 };

std::vector<std::shared_ptr<Command>> transactions
{
    std::make_shared<BankAccountWithdrawCommand>(ba1, 300),
    std::make_shared<BankAccountDepositCommand>(ba2, 300),
};

for (const auto& transaction : transactions) {
    transaction->execute();
}

std::cout << ba1.getBalance() << std::endl;
std::cout << ba2.getBalance() << std::endl;
```

*Ausgabe*:

```
700
1300
```

---

*Zusatzaufgabe*:

In der Klasse `Transactions` sollte der Vektor 

```cpp
std::vector<BankAccountCommand> m_transactions;
```

Elemente des Typs `Command` haben, also keine `BankAccountCommand`-Objekte.
Da die Klasse  `Command` abstrakt ist, müsste der Vektor Zeiger (Raw-Zeiger oder Smart Pointer) enthalten.

---

#### Quellcode

[Siehe hier](../BankAccount.cpp)

---

[Zurück](Readme.md)

---
