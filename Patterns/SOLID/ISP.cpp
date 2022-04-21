// ===========================================================================
// ISP.cpp // Interface Segregation Principle 
// ===========================================================================

#include <iostream>
#include <string>
#include <cassert>

namespace InterfaceSegregationPrinciple01
{
    class Document;

    class IMachine {
    public:
        virtual void print(Document& doc) = 0;
        virtual void fax(Document& doc) = 0;
        virtual void scan(Document& doc) = 0;
    };

    // ok
    class MultiFunctionPrinter : public IMachine {
    public:
        void print(Document& doc) override {
            // do printing ...
        }
        void fax(Document& doc) override {
            // do faxing ...
        }
        void scan(Document& doc) override {
            // do scanning ...
        }
    };

    // Not ok
    class Scanner : public IMachine {
    public:
        void print(Document& doc) override {
            throw std::runtime_error("printing not supported");
        }
        void fax(Document& doc) override {
            throw std::runtime_error("faxing not supported");
        }
        void scan(Document& doc) override {
            // do scanning ...
        }
    };
}

namespace InterfaceSegregationPrinciple02
{
    class Document;

    /* ---------------------- Interfaces ------------------- */
    class IPrinter {
    public:
        virtual void print(Document& doc) = 0;
    };

    class IScanner {
    public:
        virtual void scan(Document& doc) = 0;
    };

    class IMachine : public IPrinter, public IScanner {};

    /*  ---------------------- Implementation ------------------- */
    class Printer : public IPrinter {
    public:
        void print(Document& doc) override { };
    };

    class Scanner : public IScanner {
    public:
        void scan(Document& doc) override { };
    };

    class Machine : public IMachine {
    public:
        IPrinter& m_printer;
        IScanner& m_scanner;

        Machine(IPrinter& printer, IScanner& scanner)
            : m_printer{ printer }, m_scanner{ scanner } {}

        void print(Document& doc) override {
            m_printer.print(doc);
        }
        void scan(Document& doc) override {
            m_scanner.scan(doc);
        }
    };
}

void test_anti_conceptual_example_isp()
{
    using namespace InterfaceSegregationPrinciple01;
}

void test_conceptual_example_isp()
{
    using namespace InterfaceSegregationPrinciple02;
}

// ===========================================================================
// End-of-File
// ===========================================================================
