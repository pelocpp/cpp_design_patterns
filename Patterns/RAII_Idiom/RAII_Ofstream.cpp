// =====================================================================================
// RAII_Ofstream.cpp
// =====================================================================================

#include <string>
#include <mutex>
#include <iostream>
#include <fstream>
#include <stdexcept>

// See also:  
// https://stackoverflow.com/questions/4802494/do-i-need-to-close-a-stdfstream/4802506

namespace RAIIDemoOfstream {

    static void writeToFile(const std::string& message)
    {
        // mutex to protect file access (shared across threads)
        static std::mutex mtex;

        // lock mutex before accessing file
        std::scoped_lock<std::mutex> lock(mtex);

        // try to open file
        std::ofstream file("example.txt");
        if (!file.is_open())
            throw std::runtime_error("unable to open file");

        // write message to file
        file << message << std::endl;

        // a) file will be closed 1st when leaving scope (regardless of exception)
        // b) mutex will be unlocked 2nd (from lock destructor) when leaving
        //    scope (regardless of exception)

        // fstream (rsp. ofstream) is a proper RAII object:
        // it does close automatically at the end of the scope,
        // and there is absolutely no need whatsoever to call close manually
        // when closing at the end of the scope is sufficient.
    }

    static void test () {
        writeToFile("Dies ist eine Zeile");
    }
}

void test_ofstream_example()
{
    using namespace RAIIDemoOfstream;
    test();
}

// =====================================================================================
// End-of-File
// =====================================================================================
