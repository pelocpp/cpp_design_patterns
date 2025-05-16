// =====================================================================================
// CodeConverter.cpp
// =====================================================================================

// Original in Repository Case Studies

#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include <ostream>
#include <stdexcept>
#include <iomanip>
#include <sstream>

#include <windows.h>
#include <numeric>

// https://stackoverflow.com/questions/14762456/getclipboarddatacf-text

namespace Clipboard {

    const std::string_view Version{
        "Code-Converter of C++ Code Snippets - Version 1.01 (31.05.2021)\n"
        "Copyright (C) 2021 Peter Loos"
    };

    // non RAII conformant solution
    static int transformText_Deprecated() {

        // open the clipboard, and empty it. 
        if (!::OpenClipboard((HWND)0))
            return -1;

        // get handle of clipboard object for ANSI text
        HANDLE data = ::GetClipboardData(CF_TEXT);
        if (data == nullptr)
            return -1;

        // lock the handle to get the actual text pointer
        char* m_text = static_cast<char*>(::GlobalLock(data));
        if (m_text == nullptr)
            return -1;

        // save text in a string class instance
        std::string text{ m_text };
        std::cout << "TEXT: " << text << std::endl;

        // release lock
        ::GlobalUnlock(data);

        // release clipboard
        ::CloseClipboard();

        return 1;
    }

    // =====================================================================================

    // RAII conformant solution
    class RAIIClipboard
    {
    public:
        RAIIClipboard() {
            if (!::OpenClipboard((HWND)0)) {
                throw std::runtime_error("Can't open clipboard.");
            }
        }

        ~RAIIClipboard() {
            ::CloseClipboard();
        }

        // prevent copy semantics
        RAIIClipboard(const RAIIClipboard&) = delete;
        RAIIClipboard& operator=(const RAIIClipboard&) = delete;
    };

    class RAIIClipboardReader
    {
    public:
        // prevent copy semantics
        RAIIClipboardReader(const RAIIClipboardReader&) = delete;
        RAIIClipboardReader& operator=(const RAIIClipboardReader&) = delete;

        explicit RAIIClipboardReader()
        {
            RAIIClipboard clipboard;

            m_data = ::GetClipboardData(CF_TEXT);
            if (m_data == nullptr) {
                throw std::runtime_error("ERROR GetClipboardData!");
            }

            m_text = static_cast<const char*>(::GlobalLock(m_data));
            if (m_text == nullptr) {
                // take care of formerly allocated resources (!)
                ::GlobalFree(m_data);
                throw std::runtime_error("ERROR GlobalLock!");
            }
        }

        std::string getText() const { return m_text; }

        ~RAIIClipboardReader() {
            if (m_data != nullptr) {
                ::GlobalUnlock(m_data);
            }
        }

    private:
        HANDLE      m_data;
        const char* m_text;
    };

    class RAIIClipboardWriter
    {
    public:
        // prevent copy semantics
        RAIIClipboardWriter(const RAIIClipboardWriter&) = delete;
        RAIIClipboardWriter& operator=(const RAIIClipboardWriter&) = delete;

        explicit RAIIClipboardWriter(const std::string& text) {

            // allocate a buffer for the text
            size_t len{ text.size() };

            m_data = ::GlobalAlloc(GMEM_MOVEABLE, len + 1);
            if (m_data == nullptr) {
                throw std::runtime_error("ERROR GlobalAlloc!");
            }

            m_text = static_cast<char*>(::GlobalLock(m_data));
            if (m_text == nullptr) {
                // take care of formerly allocated resources (!)
                ::GlobalFree(m_data);
                throw std::runtime_error("ERROR GlobalLock!");
            }

            // copy the text
            std::memcpy(m_text, text.c_str(), len);
            m_text[len] = 0;

            {
                RAIIClipboard clipboard;
                ::EmptyClipboard();
                ::SetClipboardData(CF_TEXT, m_data);
            }
        }

        ~RAIIClipboardWriter() {
            if (m_text != nullptr) {
                ::GlobalUnlock(m_data);
            }

            if (m_data != nullptr) {
                ::GlobalFree(m_data);
            }
        }

    private:
        HGLOBAL m_data;
        char* m_text;
    };

    class CodeConverter
    {
    private:
        std::vector<std::string> m_code;
        std::string m_text;
        std::string m_conv;

    public:
        CodeConverter() = delete;

        explicit CodeConverter(std::string text) : m_text(text) {};

        // public interface
        void setText(const std::string& text) { m_text = text; }
        std::string getText() { return m_conv; }

        void parseInput()
        {
            try
            {
                if (m_text.empty()) {
                    std::cout << "Empty Clipboard !!!" << std::endl;
                    return;
                }

                std::string pattern{ "\r\n" };
                std::string::iterator it{ m_text.begin() };

                size_t first{};
                size_t len{};
                size_t index{};

                while ((index = m_text.find_first_of(pattern, first)) != std::string::npos) {

                    len = index - first;
                    std::string line{ m_text.substr(first, len) };
                    m_code.push_back(line);
                    first = index + 2; // skipping '\r' and '\n'
                }

                // retrieve last line
                std::string line{ m_text.substr(first) };
                if (!line.empty()) {
                    m_code.push_back(line);
                }
            }
            catch (const std::exception& e)
            {
                std::cerr << "ERROR: " << e.what() << std::endl;
            }
        }

        void addLineNumbers() {

            // assuming no code blocks longer than 1000 lines :-)
            int indent{ (m_code.size() < 100) ? 2 : 3 };

            m_conv = std::accumulate(
                m_code.begin(),
                m_code.end(),
                std::string(""),
                [indent, counter = 0](const std::string& first, const std::string& next) mutable -> std::string {

                    counter++;
                    std::ostringstream ss;
                    ss << std::setfill('0') << std::setw(indent)
                        << counter << ": " << next << std::endl;

                    return first + ss.str();
                }
            );
        }

        void printStats() {
            std::cout << Version << std::endl;
            std::cout << "Converted " << m_code.size() << " lines!" << std::endl;
            std::cout << "Press <enter> to quit ... " << std::endl;
        }
    };

    static void transformText() {
        try
        {
            std::string code{};

            {
                RAIIClipboardReader reader;
                code = reader.getText();
            }

            CodeConverter conv{ code };
            conv.parseInput();
            conv.addLineNumbers();
            conv.printStats();

            {
                std::string convertedText{ conv.getText() };
                RAIIClipboardWriter writer{ convertedText };
            }

            // lock console window on the desktop
            char ch;
            std::cin >> ch;
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }
    }
}

void code_converter()
{
    using namespace Clipboard;

    transformText_Deprecated();
    transformText();
}

// =====================================================================================
// End-of-File
// =====================================================================================
