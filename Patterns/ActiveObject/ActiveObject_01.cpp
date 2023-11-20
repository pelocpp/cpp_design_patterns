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

// ===========================================================================
// 
// This Example demonstrates the 'Active Object Pattern'
// pattern as compact as possible.
// The 'activation list' queue consist of a single element.
// The scheduler runs a single task, but:
// A result value is returned from the 'Active Object' to the client.

// ===========================================================================

namespace ActivatorObject01
{
    class Adder
    {
    public:
        Adder(int a, int b) : m_a{ a }, m_b{ b } {}

        std::tuple<int, int, int> operator() () {

            std::cout << "adding " << m_a << " and " << m_b << " ... " << std::endl;

            auto result = std::make_tuple(m_a, m_b, m_a + m_b);

            return result;
        }

    private:
        int m_a;
        int m_b;
    };

    class ActiveObject 
    {
    private:
        std::packaged_task<std::tuple<int, int, int>()> m_activationElement;

        std::mutex m_mutex;

    public:

        std::future<std::tuple<int, int, int>> enqueueTask(int a, int b) {

            Adder adder{ a, b };

            std::packaged_task<std::tuple<int, int, int>()> task (adder);

            auto future = task.get_future();

            {
                std::lock_guard<std::mutex> lockGuard{ m_mutex };

                m_activationElement = std::move(task);
            }

            return future;
        }

        void run() {

            std::jthread jt { [this] () { runSingleTask(); } };
        }

    private:

        void runSingleTask() {

            std::lock_guard<std::mutex> lockGuard(m_mutex);

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
