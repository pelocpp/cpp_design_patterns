// ===========================================================================
// DepartmentStore.cpp
// ===========================================================================

#include <iostream>
#include <string>
#include <stdexcept>
#include <variant>

namespace DepartmentStoreExample {

    // ===========================
    // states

    namespace States {

        struct OutOfStock {};

        struct Available {
            int m_count;
        };

        struct NoMoreProduced {};
    }

    using State =
        std::variant<States::OutOfStock, States::Available, States::NoMoreProduced>;

    // ===========================
    // events

    namespace Events {

        struct DeliveryArrived {
            int m_count;
        };

        struct Purchased {
            int m_count;
        };

        struct Discontinued {};
    }

    static State onEvent(States::Available available, Events::DeliveryArrived delivered) {
        available.m_count += delivered.m_count;
        return available;
    }

    static State onEvent(States::Available available, Events::Purchased purchased) {
        available.m_count -= purchased.m_count;
        if (available.m_count > 0)
            return available;
        return States::OutOfStock{};
    }

    static State onEvent(States::OutOfStock depleted, Events::DeliveryArrived delivered) {
        return States::Available{ delivered.m_count };
    }

    template <typename S>
    State onEvent(S, Events::Discontinued) {
        return States::NoMoreProduced{};
    }

    // =====================================
    // state machine within department store

    template <class... Ts>
    struct Overload : Ts... { using Ts::operator()...; };

    template <class... Ts> Overload(Ts...)->Overload<Ts...>;

    class DepartmentStoreStateMachine {
    public:
        template <typename Event>
        void processEvent(Event&& event) {
            m_state = std::visit(
                Overload{
                    [&] (const auto& state) requires std::is_same<
                    decltype(onEvent(state, std::forward<Event>(event))), State>::value {
                        return onEvent(state, std::forward<Event>(event));
                    },
                    [](const auto& unsupported_state) -> State {
                        throw std::logic_error{"Unsupported state transition"};
                    }
                },
                m_state);
        }

        std::string reportCurrentState() {
            return std::visit(
                Overload{
                    [](const States::Available& state) -> std::string {
                        return std::to_string(state.m_count) + " items available";
                    },
                    [](const States::OutOfStock) -> std::string {
                        return "Item is temporarily out of stock";
                    },
                    [](const States::NoMoreProduced) -> std::string {
                        return "Item is no more produced";
                    }
                },
            m_state);
        }

    private:
        State m_state;
    };

    static void clientCode_01()
    {
        DepartmentStoreStateMachine fsm = DepartmentStoreStateMachine{};
        std::string report;

        std::cout << fsm.reportCurrentState() << std::endl;
        Events::DeliveryArrived eventDelivery = Events::DeliveryArrived{ 3 };
        fsm.processEvent(eventDelivery);
        std::cout << fsm.reportCurrentState() << std::endl;
        Events::Purchased eventPurchased = Events::Purchased{ 2 };
        fsm.processEvent(eventPurchased);
        report = fsm.reportCurrentState();
        std::cout << report << std::endl;
        eventDelivery = Events::DeliveryArrived{ 2 };
        fsm.processEvent(eventDelivery);
        report = fsm.reportCurrentState();
        std::cout << report << std::endl;
        eventPurchased = Events::Purchased{ 3 };
        fsm.processEvent(eventPurchased);
        report = fsm.reportCurrentState();
        std::cout << report << std::endl;
        Events::Discontinued discontinued = Events::Discontinued{};
        fsm.processEvent(discontinued);
        report = fsm.reportCurrentState();
        std::cout << report << std::endl;
        eventDelivery = Events::DeliveryArrived{ 1 };
        // fsm.processEvent(eventDelivery);
        std::cout << std::endl;
    }

    static void clientCode_02()
    {
        auto fsm = DepartmentStoreStateMachine{};
        std::cout << fsm.reportCurrentState() << std::endl;
        fsm.processEvent(Events::DeliveryArrived {3});
        std::cout << fsm.reportCurrentState() << std::endl;
        fsm.processEvent(Events::Purchased {2});
        std::cout << fsm.reportCurrentState() << std::endl;
        fsm.processEvent(Events::DeliveryArrived {2});
        std::cout << fsm.reportCurrentState() << std::endl;
        fsm.processEvent(Events::Purchased {3});
        std::cout << fsm.reportCurrentState() << std::endl;
        fsm.processEvent(Events::Discontinued {});
        std::cout << fsm.reportCurrentState() << std::endl;
        // fsm.processEvent(DeliveryArrived{1});
    }
}

void test_departmentstore_example()
{
    using namespace DepartmentStoreExample;
    clientCode_01();
    clientCode_02();
}

// ===========================================================================
// End-of-File
// ===========================================================================
