// ===========================================================================
// ActiveObject_01.cpp // Active Object Pattern
// ===========================================================================

#include <iostream>
#include <thread>
#include <future>
#include <mutex>
#include <algorithm>
#include <tuple>
#include <chrono>

namespace ActivatorObject01
{
    class Adder
    {
    public:
        Adder(int summand1, int summand2) 
            : m_summand1{ summand1 }, m_summand2{ summand2 } {}

        std::tuple<int, int, int> operator() () {

            std::cout << "adding " << m_summand1 << " and " << m_summand2 << " ... " << std::endl;

            auto result = std::make_tuple(
                m_summand1, 
                m_summand2,
                m_summand1 + m_summand2
            );

            return result;
        }

    private:
        int m_summand1;
        int m_summand2;
    };

    class ActiveObject 
    {
    private:
        std::packaged_task<std::tuple<int, int, int>()> m_activationElement;
        std::mutex m_activationListMutex;

    public:

        std::future<std::tuple<int, int, int>> enqueueTask(int summand1, int summand2) {

            Adder adder{ summand1, summand2 };

            std::packaged_task<std::tuple<int, int, int>()> task (adder);

            auto future = task.get_future();

            {
                std::lock_guard<std::mutex> lockGuard{ m_activationListMutex };

                m_activationElement = std::move(task);
            }

            return future;
        }

        void run() {

            std::jthread j{ [this] () { runSingleTask(); } };
        }

    private:

        void runSingleTask() {

            std::lock_guard<std::mutex> lockGuard(m_activationListMutex);

            if (m_activationElement.valid()) {

                m_activationElement();
            }
        }
    };
}

void test_active_object_01()
{
    using namespace ActivatorObject01;

    std::cout << "Active Object - Simple Approach" << std::endl;

    ActiveObject activeObject;

    auto future = activeObject.enqueueTask(3, 5);

    // start the active object
    activeObject.run();

    // continue working in the client thread
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // get the result from the future
    auto [first, second, sum] = future.get();

    std::cout << first << " + " << second << " = " << sum << std::endl;
    std::cout << "Done." << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
