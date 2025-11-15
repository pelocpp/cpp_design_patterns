# Simulation einer Verkehrsampel (*TrafficLight*)

#### Lösung

Das hier beschriebene Problem ist ein typischer Anwendungsfall des *State* Entwurfsmusters.
Der Zustand einer Ampel setzt sich im einfachsten Fall aus den drei Phasen Rot, Grün und Geld
zusammen. Einen Zustand sollte man beschreiben können und man sollte von einem Zustand
zum nächsten wechseln können. Dies wird in der Schnittstelle `ITrafficLightState` abstrakt beschrieben:

```cpp
class ITrafficLightState
{
public:
    virtual void changeState(TrafficLight* light) = 0;
    virtual void reportState() const = 0;
};
```

An der Methode `changeState` erkennen wir, dass auf die Ampel selbst (*Context*-Klasse des Patterns)
eine Art Rückverweis auf das *Context*-Objekt zu übergeben ist - in unserem Beispiel
die Verkehrsampel, modelliert mit einer Klasse `TrafficLight`:

```cpp
class TrafficLight
{
private:
    ITrafficLightState* m_state;

public:
    void setState(ITrafficLightState* state);
    ITrafficLightState* getState();

    void change();
    void show() const;
};
```

<img src="dp_traffic_light.svg" width="800">

Abbildung 1: Schematische Darstellung des *State* Patterns im Anwendungsfall *Traffic Light*.


Damit erhalten wir nun die Simulation einer Verkehrsampel auf Basis des *State*-Patterns
wie folgt:


*Beispiel*:

```cpp
std::cout << "TrafficLight: Variant 01" << std::endl;

TrafficLight trafficLight;
trafficLight.setState(new RedLight());
trafficLight.show();
std::this_thread::sleep_for(std::chrono::seconds(1));

while (true)
{
    trafficLight.change();
    trafficLight.show();
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
```

#### Quellcode

Der Quellcode liegt in drei Varianten vor:

  * Variante mit *Raw* Pointer

  * Variante mit *Smart* Pointer

  * Variante mit *Smart* Pointer und *Singleton* Entwurfsmuster

In der dritten Variante wird das Problem gelöst, das pro Zustandswechsel
immer ein neues Zustandsobjekt benötigt wird. 
Dies lässt sich mit dem *Singleton* Entwurfsmuster besser lösen.

[Siehe hier](../TrafficLight01/Main01.cpp) und weitere Dateien im selben Verzeichnis.


---

[Zurück](Readme.md)

---
