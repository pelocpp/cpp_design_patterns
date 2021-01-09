// =====================================================================================
// Clipboard.cpp
// =====================================================================================

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

    // non RAII conformant solution
    int transformText01() {

        // open the clipboard, and empty it. 
        if (!OpenClipboard((HWND)0))
            return -1;

        // get handle of clipboard object for ANSI text
        HANDLE data = GetClipboardData(CF_TEXT);
        if (data == nullptr)
            return -1;

        // lock the handle to get the actual text pointer
        char* m_text = static_cast<char*>(GlobalLock(data));
        if (m_text == nullptr)
            return -1;

        // save text in a string class instance
        std::string text { m_text };
        std::cout << "TEXT: " << text << std::endl;

        // release lock
        GlobalUnlock(data);

        // release clipboard
        CloseClipboard();

        return 1;
    }

    // RAII conformant solution
    class RAIIClipboard
    {
    public:
        RAIIClipboard() {
            if (!OpenClipboard((HWND)0))
                throw std::runtime_error("Can't open clipboard.");
        }

        ~RAIIClipboard() {
            CloseClipboard();
        }

        // prevent copy semantics
        RAIIClipboard(const RAIIClipboard&) = delete;
        RAIIClipboard& operator=(const RAIIClipboard&) = delete;
    };

    class RAIIClipboardReader
    {
    public:
        explicit RAIIClipboardReader() {

            RAIIClipboard clipboard;

            m_data = GetClipboardData(CF_TEXT);
            if (m_data == nullptr)
                throw std::runtime_error("ERROR GetClipboardData!");

            m_text = static_cast<const char*>(GlobalLock(m_data));
            if (m_text == nullptr)
                throw std::runtime_error("ERROR GlobalLock!");
        }

        // prevent copy semantics
        RAIIClipboardReader(const RAIIClipboardReader&) = delete;
        RAIIClipboardReader& operator=(const RAIIClipboardReader&) = delete;

        std::string getText() const {
            return std::string{ m_text };
        }

        ~RAIIClipboardReader() {
            if (m_data != nullptr)
                GlobalUnlock(m_data);
        }

    private:
        HANDLE m_data;
        const char* m_text;
    };

    class RAIIClipboardWriter
    {
    public:
        explicit RAIIClipboardWriter(const std::string& text) {

            // allocate a buffer for the text
            size_t len = text.size();

            m_data = GlobalAlloc(GMEM_MOVEABLE, len + 1);
            if (m_data == nullptr)
                throw std::runtime_error("ERROR GlobalAlloc!");

            m_text = static_cast<char*>(GlobalLock(m_data));
            if (m_text == nullptr)
                throw std::runtime_error("ERROR GlobalLock!");

            // copy the text
            memcpy(m_text, text.c_str(), len);
            m_text[len] = 0;

            RAIIClipboard clipboard;
            EmptyClipboard();
            SetClipboardData(CF_TEXT, m_data);
        }

        // prevent copy semantics
        RAIIClipboardWriter(const RAIIClipboardWriter&) = delete;
        RAIIClipboardWriter& operator=(const RAIIClipboardWriter&) = delete;

        ~RAIIClipboardWriter() {
            if (m_text != nullptr)
                GlobalUnlock(m_data);
            if (m_data != nullptr)
                GlobalFree(m_data);
        }

    private:
        HGLOBAL m_data{ nullptr};
        char* m_text{ nullptr };
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

        void parseInput() {
            try
            {
                if (m_text.empty()) {
                    std::cout << "Empty Clipboard !!!" << std::endl;
                    return;
                }

                std::string pattern{ "\r\n" };
                std::string::iterator it = m_text.begin();

                size_t first{};
                size_t len{};
                size_t index{};

                while ((index = m_text.find_first_of(pattern, first)) != std::string::npos) {

                    len = index - first;
                    std::string line = m_text.substr(first, len);
                    m_code.push_back(line);
                    first = index + 2; // skipping '\r' and '\n'
                    // std::cout << "Found: " << line << std::endl;
                }

                // retrieve last line
                std::string line = m_text.substr(first);
                // std::cout << "Last:  " << line << std::endl;

                if (! line.empty()) {
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
            int indent = (m_code.size() < 100) ? 2 : 3;

            m_conv = std::accumulate(
                std::begin(m_code),
                std::end(m_code),
                std::string(""), 
                [indent, counter = 0](const std::string& first, const std::string& next) mutable {
            
                counter++;
                std::ostringstream ss;
                ss << std::setfill('0') << std::setw(indent) 
                    << counter << ": " << next << std::endl;

                return first + ss.str();
            });
        }

        void printStats() {
            std::cout << "Code-Converter of C++ Code Snippets - Copyright (C) 2021 Peter Loos" << std::endl;
            std::cout << "Converted " << m_code.size() << " lines!" << std::endl;
        }
    };

    void transformText02() {
        try
        {
            RAIIClipboardReader reader;
            std::string code = reader.getText();
            CodeConverter conv{ code };
            conv.parseInput();
            conv.addLineNumbers();
            conv.printStats();
            std::string convertedText = conv.getText();
            RAIIClipboardWriter writer{ convertedText };
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl;
        }
    }
}

void transformText()
{
    using namespace Clipboard;

    //transformText01();
    //transformText02();
}

// =====================================================================================
// End-of-File
// =====================================================================================