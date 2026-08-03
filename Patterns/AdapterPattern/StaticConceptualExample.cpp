// ===========================================================================
// StaticConceptualExample.cpp - Adapter Pattern
// ===========================================================================

#include <concepts>
#include <format>
#include <print>
#include <string>

// 1. C++20 Concept ersetzt das klassische abstrakte Interface (ITarget)
// Jede Klasse, die eine Methode 'request()' hat, die einen std::string zurückgibt, 
// erfüllt automatisch dieses Concept. Keine Vererbung nötig!
template<typename T>
concept TargetConcept = requires(const T c) {
    { c.request() } -> std::same_as<std::string>;
};

// 2. Das normale Target (benötigt keine Basisklasse mehr)
class Target {
public:
    std::string request() const {
        return "Target: The target's default behavior.";
    }
};

// 3. Der unpassende Adaptee (bleibt unverändert)
class Adaptee {
public:
    std::string specificRequest() const {
        return ".eetpadA eht fo roivaheb laicepS";
    }
};

// 4. Der Compile-Time Adapter (Template-basiert)
// Er nimmt den Typ des Adaptee als Template-Parameter auf (Kompilation via Composition)
template <typename TAdaptee>
class CompileTimeAdapter {
private:
    TAdaptee m_adaptee; // Liegt direkt auf dem Stack (kein Heap/Smart-Pointer-Overhead)

public:
    // Konstruktor nimmt den Adaptee entgegen (oder erzeugt ihn per Default)
    explicit CompileTimeAdapter(TAdaptee adaptee)
        : m_adaptee{ std::move(adaptee) }
    {}

    // Der Adapter bietet die vom Client geforderte 'request()'-Methode an
    std::string request() const {
        std::string original = m_adaptee.specificRequest();

        std::reverse(original.begin(), original.end());

        return std::format("Adapter: (TRANSLATED) {}", original);
    }
};

// 5. Der Client-Code nutzt das Concept statt eines Zeigers/einer Referenz auf ein Interface
// Der Compiler optimiert diesen Aufruf oft so weit, dass er komplett "inlined" wird.
template <TargetConcept T>
static void clientCode(const T& target) {
    std::println("{}", target.request());
}

void test_static_conceptual_example() {

    // Beispiel 1: Direktes Arbeiten mit dem Target
    std::println("Client: Working with standard Target");
    Target normalTarget;
    clientCode(normalTarget); // Erfüllt TargetConcept

    // Beispiel 2: Arbeiten mit dem Adaptee über den Compile-Time Adapter
    std::println("Client: Working with Adaptee via CompileTimeAdapter:");
    Adaptee oldAdaptee;

    // Der Typ des Adapters wird automatisch (oder explizit) deduziert
    CompileTimeAdapter adapter(std::move(oldAdaptee));

    clientCode(adapter); // Erfüllt ebenfalls TargetConcept
}

// ===========================================================================
// End-of-File
// ===========================================================================
