// ===========================================================================
// ActiveObject_01.cpp // Active Object Pattern
// ===========================================================================

#include <iostream>
#include <utility>
#include <thread>
#include <future>
#include <mutex>
#include <deque>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <tuple>

namespace ActivatorObject02
{
    class SumRange {
    private:
        size_t m_a;
        size_t m_b;

    public:
        SumRange(size_t a, size_t b) : m_a{ a }, m_b{ b } {}

        std::tuple<size_t, size_t, size_t> operator() () {

            size_t sum{};
            for (size_t i{ m_a }; i != m_b; ++i) {
                sum += i;
            }
            return std::make_tuple(m_a, m_b, sum);
        }
    };

    class ActiveObject {

    private:
        std::deque<std::packaged_task<std::tuple<size_t, size_t, size_t>()>> m_activationList;

        std::mutex m_mutex;

    public:

        std::future<std::tuple<size_t, size_t, size_t>> enqueueTask(size_t a, size_t b) {

            SumRange range{ a, b };

            std::packaged_task<std::tuple<size_t, size_t, size_t>()> task(range);

            auto future = task.get_future();

            {
                std::lock_guard<std::mutex> lockGuard{ m_mutex };

                m_activationList.push_back(std::move(task));
            }

            return future;
        }

        void run() {

            std::jthread jt([this] {

                while (!runNextTask())
                    ;
                }
            );
        }

    private:

        bool runNextTask() {

            std::lock_guard<std::mutex> lockGuard(m_mutex);

            auto isEmpty = m_activationList.empty();

            if (!isEmpty) {

                auto task{ std::move(m_activationList.front()) };

                m_activationList.pop_front();

                task();
            }

            return isEmpty;
        }


    };

    //std::future<std::vector<std::future<std::tuple<size_t, size_t, size_t>>>>

    //    getFutures(ActiveObject& activeObject, int numberPrimes) {

    //    return std::async([&activeObject, numberPrimes] {

    //        std::vector<std::future<std::tuple<size_t, size_t, size_t>>> futures;

    //        auto randNumbers = getRandNumbers(numberPrimes);        // (3)

    //        for (auto numb : randNumbers) {
    //            futures.push_back(activeObject.enqueueTask(numb));  // (5)
    //        }

    //        return futures;
    //        });
    //}


    // Name ist schlecht .. Singular wäre besser ...

    std::future<std::vector<std::future<std::tuple<size_t, size_t, size_t>>>>

        getFutures(ActiveObject& activeObject, size_t start, size_t length, size_t count) {

            return std::async([=, &activeObject] () mutable {

                std::vector<std::future<std::tuple<size_t, size_t, size_t>>> futures;
                // resize

                for (size_t i{}; i != count; ++i) {

                    std::future<std::tuple<size_t, size_t, size_t>> future 
                        = activeObject.enqueueTask(start, start + length);

                    start += length;

                    futures.push_back(std::move(future));
                }

                return futures;
            }
        );
    }

}



void test_active_object_02()
{
    using namespace ActivatorObject02;

    std::cout << "Active Object  II" << std::endl;

    ActiveObject activeObject{};

    // enqueue work concurrently 

 //   size_t start{ 1 };
 //   size_t length{ 100 };
 ////   size_t coint;

    //auto client1 = getFutures(activeObject, 1,    200, 5);  // range from 1 to 1000
    //auto client2 = getFutures(activeObject, 1000, 200, 5);  // range from 1000 to 2000
    //auto client3 = getFutures(activeObject, 2000, 200, 5);  // range from 2000 to 3000

    auto client1 = getFutures(activeObject,    1, 100, 10);  // range from 1 to 1000
    auto client2 = getFutures(activeObject, 1001, 100, 10);  // range from 1000 to 2000
    auto client3 = getFutures(activeObject, 2001, 100, 10);  // range from 2000 to 3000

    // retrieve futures 
    auto futures1 = client1.get();
    auto futures2 = client2.get();
    auto futures3 = client3.get();

    // copy all futures into a single container
    std::vector<std::future<std::tuple<size_t, size_t, size_t>>> futures;

    std::for_each(
        std::begin(futures1),
        std::end(futures1),
        [&] (auto& future) {
            futures.push_back(std::move(future));
        }
    );

    std::for_each(
        std::begin(futures2),
        std::end(futures2),
        [&](auto& future) {
            futures.push_back(std::move(future));
        }
    );

    std::for_each(
        std::begin(futures3),
        std::end(futures3),
        [&](auto& future) {
            futures.push_back(std::move(future));
        }
    );

    std::cout << "stopper ..." << std::endl;

    //// put all futures together                                 // (10)
    //futures.insert(futures.end(), std::make_move_iterator(futures2.begin()),
    //    std::make_move_iterator(futures2.end()));

    //futures.insert(futures.end(), std::make_move_iterator(futures3.begin()),
    //    std::make_move_iterator(futures3.end()));

    //futures.insert(futures.end(), std::make_move_iterator(futures4.begin()),
    //    std::make_move_iterator(futures4.end()));

    //futures.insert(futures.end(), std::make_move_iterator(futures5.begin()),
    //    std::make_move_iterator(futures5.end()));

    // run the promises                        
    activeObject.run();

    // get the results from the futures
    std::vector<std::tuple<size_t, size_t, size_t>> futureResults;
    futureResults.reserve(futures.size());

    for (auto& future : futures) { 
        futureResults.push_back(future.get()); 
    }

    // calculate final sum result
    size_t totalSum{};

    std::for_each(
        futureResults.begin(),
        futureResults.end(),
        [&](const auto& tuple){
        
            auto partialSum = std::get<2>(tuple);
            totalSum += partialSum;
        }
    );

    std::cout << "TotalSum: " << totalSum << std::endl;  // expecting 500'500

    std::cout << "Done." << std::endl;
}

// ===========================================================================
// End-of-File
// ===========================================================================
