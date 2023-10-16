// ===========================================================================
// ConceptualExample.cpp // Active Object Pattern
// ===========================================================================

#include <iostream>
#include <functional>
#include <thread>
#include <queue>
#include <mutex>

// ---------------------------------------------------------------------------
// OriginalClass is a standard class
// that provides two methods that set a double to be a certain value.
// This class does NOT conform to the active object pattern.

class OriginalClass
{
private:
    double val;
public:
    OriginalClass() : val(0) {}

    void doSomething() {
        val = 1.0;
    }

    void doSomethingElse() {
        val = 2.0;
    }
};

// ---------------------------------------------------------------------------
// Alternate implementation using an Active Object approach

using Operation = std::function<void()>;

class DispatchQueue {

    std::mutex m_mutex;
    std::queue<Operation> m_queue;
    std::condition_variable m_empty;

public:
    void put(Operation op) {
        std::lock_guard<std::mutex> raii_guard(m_mutex);
        m_queue.push(op);
        m_empty.notify_one();
    }

    Operation take() {
        std::unique_lock<std::mutex> raii_guard(m_mutex);
        m_empty.wait(raii_guard, [&] { return ! m_queue.empty(); });

        Operation op = m_queue.front();
        m_queue.pop();
        return op;
    }
};

class ActiveObject
{
private:
    DispatchQueue m_dispatchQueue;
    std::atomic<bool> m_done;
    std::unique_ptr<std::thread> m_runnable;
    double m_val;

public:
    // c'tors/ d'tor
    ActiveObject() : m_val{}, m_done{} {
        // Start the thread that this object will "occupy".
        // The public methods of this object will run in the 
        // context of this new thread
        m_runnable = std::make_unique<std::thread>(&ActiveObject::run, this);
    }

    ~ActiveObject() { m_runnable->join(); }

    // public interface
    void run() {
        while (! m_done) 
        {
            Operation op = m_dispatchQueue.take();

            op();
        }
    }

    // This is part of the public interface of this class.
    // Each method is composed of the actual code we want to execute,
    // and veneer code which queues our code.
    void doSomething()
    {
        std::cout << "doSomething" << std::endl;

        // This is the actual code to execute:
        // Store it in an std::function and push it to the FIFO
        auto task{ [&]() { m_val = 1.0; } };

        m_dispatchQueue.put(task);
    }

    void doSomethingElse()
    {
        std::cout << "doSomethingElse" << std::endl;

        // More compact syntax, but it may also be harder to read ...

        m_dispatchQueue.put( { [&]() { m_val = 2.0; } } );
    }
};

void test_conceptual_example_01()
{
    std::cout << "Active Object" << std::endl;

    ActiveObject active;
    active.doSomething();
    active.doSomethingElse();

    std::cout << "Done." << std::endl;
}

void test_conceptual_example()
{
    test_conceptual_example_01();
}

// ===========================================================================
// End-of-File
// ===========================================================================
