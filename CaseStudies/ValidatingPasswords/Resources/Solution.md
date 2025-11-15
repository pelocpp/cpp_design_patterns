# Passwortcheck

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall für das &ldquo;Decorator Pattern&rdquo; Entwurfsmuster.
Dieses Entwurfsmuster ermöglicht das Hinzufügen von Verhalten zu einem Objekt, ohne andere Objekte desselben Typs zu beeinflussen.
Das wird erreicht durch das Einhüllen eines Objekts in ein anderes Objekt.
Mehrere dieser so genannten *Decorator*-Objekte lassen sich miteinander verknüpfen
(aufeinander stapeln), wobei jedes Mal eine neue Funktionalität hinzugefügt wird.
In unserem  Beispiel besteht die Funktionalität darin,
dass ein bestimmtes Passwort eine oder mehrere bestimmte Anforderung(en) erfüllen muss.

Das folgende Klassendiagramm beschreibt das *Decorator Pattern* Entwurfsmuster
zum Überprüfen von Kennwörtern:

<img src="dp_password_validator.svg" width="700">

Abbildung 1: Schematische Darstellung des *Decorator* Patterns im Anwendungsfall *Passwortcheck*.

`PasswordValidator` ist eine Basisklasse und verfügt über eine 
virtuelle Methode namens `validate` mit einem `std::string`-Parameter,
der ein zu überprüfendes Passwort entgegennimmt.
`LengthValidator` wird abgeleitet von `PasswordValidator`.
Diese Klasse implementiert die obligatorische Passwortanforderung bezüglich der Mindestlänge.
`PasswordValidatorDecorator` wird auch von `PasswordValidator` abgeleitet,
besitzt als Instanzvariable aber nur eine `PasswordValidator`-Referenz.
Die `validate`-Implementierung dieser Klasse delegiert den Aufruf einfach an `validate`-Methode
des referenzierten `PasswordValidator`-Objekts weiter.
Die anderen Klassen
`DigitPasswordValidator`, `SymbolPasswordValidator` und
`CasePasswordValidator` werden ebenfalls von der Klasse `PasswordValidatorDecorator` abgeleitet
und implementieren zusätzliche Anforderungen an die Passwortstärke.

Auf diese Weise können Sie ein `LengthValidator`-Objekt (Minimalanforderung)
wie folgt "*dekorieren*":

```cpp
std::unique_ptr<PasswordValidator> validator {
    std::make_unique<SymbolPasswordValidator>(
        std::make_unique<CasePasswordValidator>(
            std::make_unique<DigitPasswordValidator>(
                std::make_unique<LengthValidator>(8))))
};

bool valid { validator->validate("IchBinEinPasswort") };
```


#### Quellcode

[Siehe hier](../ValidatingPasswords.cpp)

---

[Zurück](Readme.md)

---
