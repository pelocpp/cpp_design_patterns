# Pointer to Implementation (*Pimpl*)

#### Lösung

###### Verfahrensanweisung zur Umstrukturierung von Klasse `Control`

Strukturieren Sie die Klasse `Control` so um, dass sie keinerlei private Instanzvariablen oder -methoden besitzt,
natürlich mit Ausnahme eines *Pimpl*-Zeigers. Das Ziel soll es sein, dass die interne Realisierung der Klasse `Control` 
noch Änderungen unterworfen sein kann, man aber alle anderen C++-Dateien, die die  `Control`-Klasse verwenden wollen,
von (überflüssigen) Neuübersetzungen ausnehmen möchte.

Nehmen Sie die Umstrukturierung in folgenden Schritten vor:

  1. Fügen Sie alle privaten Mitglieder, sowohl Daten als auch Methoden, in eine
     separate Hilfsklasse ein. Benennen Sie diese Klasse `ControlPimpl`.

  2. Ergänzen Sie in der Header-Datei der Ausgangsklasse eine *Forward*-Deklaration für die `ControlPimpl` wie folgt:

```cpp
    // file Control.h:
    class ControlPimpl;
```

  3. Deklarieren Sie in der Ausgangsklasse einen Zeiger auf die
    `ControlPimpl`-Klasse auf Basis einer `std::unique_ptr`-Variablen. Dies sollte die einzige 
    private Instanzvariablen der Ausgangsklasse sein:


```cpp
class Control {
private:
    // single property: opaque pointer / pointer to impl
    std::unique_ptr<ControlPimpl> m_pimpl;

public:
    // public class interface
    Control();
    void setText(std::string);
    void resize(const int width, const int height);
    void show();
    void hide();
};
```

  4. Fügen Sie die `ControlPimpl`-Klassendefinition in der Quelldatei der Ausgangsklasse ein.
    Übernehmen Sie alle Instanzvariablen (Eigenschaften und Methoden, sowohl `public` als auch `private`)
    direkt in die `ControlPimpl`-Klassendefinition:

```cpp
class ControlPimpl {
private:
    std::string m_text;
    int m_width;
    int m_height;
    bool m_visible;

    void draw();

public:
    ControlPimpl() : m_text(""), m_width(0), m_height(0), m_visible(true) {}

    void setText(std::string text);
    void resize(const int width, const int height);
    void show();
    void hide();
};
```

  5. Die öffentliche Schnittstelle (`public`) der Ausgangsklasse *spiegeln* Sie mit entprechenden Aufrufen an der *Pimpl*-Klasse wider,
    um so gewissermaßen die öffentliche Schnittstelle (`public`) der Ausgangsklasse an die *Pimpl*-Klasse durchzuschleusen.

```cpp
void Control::setText(std::string text)
{
    m_pimpl->setText(text);
}
...
...
```

  6. Die private Schnittstelle (`private`) der Ausgangsklasse implementieren Sie wie gewünscht bzw. erforderlich.
     Nachträgliche Änderungen haben keine Auswirkungen auf Benutzer der Ausgangsklasse:

```cpp
void ControlPimpl::draw()
{
    std::cout
        << "control "
        << std::endl
        << " visible: "
        << std::boolalpha
        << m_visible
        << std::noboolalpha
        << std::endl
        << " size: "
        << m_width
        << ", "
        << m_height
        << std::endl
        << " text: "
        << m_text
        << std::endl;
}
```

  7. Die *Pimpl*-Klasse wird im Konstruktor der Ausgangsklasse instanziiert:

```cpp
Control::Control() : m_pimpl(std::make_unique<ControlPimpl>()) {}
```

#### Quellcode


###### Hauptaufgabe:

Siehe [Control.h](../Pimpl02/Control.h) und [Control.cpp](../Pimpl02/Control02.cpp) sowie [Client.cpp](../Pimpl02/Client02.cpp).

###### Zusatzaufgabe 1: Kopier- und Verschiebesemantik

Siehe [Control.h](../Pimpl03/Control.h) und [Control.cpp](../Pimpl03/Control03.cpp) sowie [Client.cpp](../Pimpl03/Client03.cpp).

###### Zusatzaufgabe 2: Aufteilung des Projekts in mehrere Dateien

Siehe [Control.h](../Pimpl04/Control.h), [ControlPimpl.h](../Pimpl04/ControlPimpl.h),
[Control.cpp](../Pimpl04/Control04.cpp) und [ControlPimpl.cpp](../Pimpl04/ControlPimpl04.cpp) sowie [Client.cpp](../Pimpl04/Client04.cpp).

---

[Zurück](Readme.md)

---
