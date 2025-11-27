# Ein Textprozessor

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

#### Aufgabe

Wir betrachten in dieser Aufgabe die Implementierung eines Textprozessors,
zumindest in Ansätzen. Aufgabe dieses Textprozessors ist es,
unformatierten Text, also Zeichenketten entgegenzunehmen,
und diese formatiert auszugeben. Handelt es sich dabei um
eine Aufzählung mehrerer Zeichenketten (Liste von Zeichenketten),
dann sollten diese bei der Ausgabe so in Erscheinung treten:

  * just
  * like
  * this

Wenn Sie über verschiedene populäre Ausgabeformate nachdenken,
wissen Sie wahrscheinlich, dass 
Sie jedes Element einzeln mit einem zusätzlichen Markup ausgeben müssen.
Bei Textformaten wie HTML oder LaTeX muss die Liste zusätzlich
mit einem Anfangs-Tag gestartet und einem Ende-Tag beendet werden.
Man kann folglich die Beobachtung machen, dass die Verarbeitung von Listen - 
in welchem Format auch immer - ähnlich erfolgt,
die Art und Weise in der konkreten Ausgabe aber unterschiedlich ist.

#### Hinweise

##### Klasse `ListStrategy`:

Zur Abstrahierung einer konkreten Ausgabe einer Liste definieren wir drei Methoden `start`, `add` und `end`,
wie die eingangs gemachten Überlegungen nahelegen.
Definieren Sie eine Klasse `ListStrategy`,
die diese drei Methoden mit den folgenden Schnittstellen beschreibt:

```cpp
void start(std::ostringstream&);
void addListItem(std::ostringstream&, const std::string& item);
void end(std::ostringstream&);
```

Die Ausgabe des Textprozessors soll dabei in ein Objekt des Typs
`ostringstream` erfolgen.

##### Klasse `HtmlListStrategy`:

Realisieren Sie eine Klasse `HtmlListStrategy`, die die Schnittstelle
`ListStrategy` implementiert. Beachten Sie dabei:
In HTML wird eine Liste mit dem Tag `<ul>` eingeleitet
und mit dem Tag `</ul>` abgeschlossen.
Die einzelnen Elemente der Aufzählung sind in `<li>` bzw. `</li>` einzuschließen.

##### Klasse `MarkdownListStrategy`:

Realisieren Sie eine Klasse `MarkdownListStrategy`, die die Schnittstelle
`ListStrategy` implementiert. Beachten Sie dabei:
In Markdown kennen Listen kein Anfangs- und Endetag.
Die einzelnen Elemente der Aufzählung sind mit zwei führenden Blanks und einem Stern `*` einzuleiten.

##### Klasse `TextProzessor`:

Die Klasse `TextProzessor` kann Ausgaben in verschiedenen Formaten tätigen.
Zur Unterscheidung bietet sich ein Aufzählungstyp an:

```cpp
enum class OutputFormat
{
    Markdown,
    Html
};
```

Mindestens drei öffentliche Methoden muss die Klasse `TextProzessor` besitzen:

```cpp
void setOutputFormat(std::unique_ptr<ListStrategy>&&)
void outputList(const std::vector<std::string>&);
void print();
```

Mit `setOutputFormat` vermerkt sich das `TextProzessor`-Objekt intern,
in welchem Format die Textverarbeitung zu erfolgen hat.
Die Methode `outputList` nimmt eine Liste von Zeichenketten entgegen,
die eine Aufzählung bilden. `print` schließlich gibt den Text
auf der Konsole aus. 

---

#### Lösung

[Siehe hier](Solution.md)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---
