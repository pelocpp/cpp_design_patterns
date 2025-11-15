# Versenden von Benachrichtigungen

#### Aufgabe

Wir betrachten ein C++-Programm, das das Versenden von Benachrichtigungen auf 
verschiedene Arten betrachtet. Im Speziellen soll eine Nachricht als SMS oder als EMail
versendet werden können. 

Der eigentliche Vorgang des Versendens einer Benachrichtigung soll dabei in seinem Aufbau
bzw. in seinen Teilfunktionalitäten immer derselbe sein. Wir nennen diese Methode `notify`:

```cpp
void notify(std::string text);
```

In unserer Beispielanwendung sollen für das Versenden einer Benachrichtigung prinzipiell
Header-Informationen, Trailer-Informationen, die Nachricht selbst sowie Informationen von Protokollparametern
betrachtet werden. Die jeweiligen Methoden, die diese Werte bereitstellen, könnten so aussehen:

```cpp
virtual std::string getNotificationHeader() = 0;
virtual std::string getNotificationTrailer() = 0;
virtual std::string getProtocolDetails() = 0;
virtual void sendText(std::string) = 0;
```

Welches klassische Entwurfsmuster bietet sich zur Realisierung an?

Simulieren Sie zwei Verfahren zum Versenden von Benachrichtigungen anhand zweier Klassen
`MailNotificationSender` und `SmsNotificationSender`.

Welcher Klasse ist die Methode `notify` zuzuordnen?

Schreiben Sie eine Testfunktion, die Ihre Realisierung testet.

##### Zusatzaufgabe:

Im Lösungsteil dieser Aufgabe finden Sie den Quelltext der `MailNotificationSender`-Klasse vor.
Benutzen Sie diese Klasse als Anregung, um davon ausgehend eine zweite Klasse `SmsNotificationSender` 
zu realisieren.

Beachten Sie bei einer SMS: Im klassischen *Short Message Service Protocol* kann eine Nachricht
nicht länger als 160 Zeichen sein.

#### Lösung

[Siehe hier](Solution.md)

---

[Zurück](../../../Resources/Readme_08_CaseStudies.md)

---

