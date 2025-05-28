// ===========================================================================
// ISP.cpp // Interface Segregation Principle 
// ===========================================================================

#include <iostream>
#include <string>
#include <cassert>

namespace InterfaceSegregationPrinciple01
{
    class Document {};

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
    class Document {};

    /* ---------------------- Interfaces ------------------- */
    class IPrinter {
    public:
        virtual void print(Document& doc) = 0;
    };

    class IScanner {
    public:
        virtual void scan(Document& doc) = 0;
    };

    class IFaxMachine {
    public:
        virtual void fax(Document& doc) = 0;
    };

    class IMachine : public IPrinter, public IScanner, public IFaxMachine {};

    /*  ---------------------- Implementation ------------------- */
    class Printer : public IPrinter {
    public:
        void print(Document& doc) override { };
    };

    class Scanner : public IScanner {
    public:
        void scan(Document& doc) override { };
    };

    class FaxMachine : public IFaxMachine {
    public:
        void fax(Document& doc) override { };
    };

    class Machine : public IMachine {
    public:
        IPrinter&    m_printer;
        IScanner&    m_scanner;
        IFaxMachine& m_faxmachine;

        Machine(IPrinter& printer, IScanner& scanner, IFaxMachine& faxmachine)
            : m_printer{ printer }, m_scanner{ scanner }, m_faxmachine{ faxmachine } {}

        void print(Document& doc) override {
            m_printer.print(doc);
        }

        void scan(Document& doc) override {
            m_scanner.scan(doc);
        }

        void fax(Document& doc) override {
            m_faxmachine.fax(doc);
        }
    };
}

static void test_anti_conceptual_example_isp()
{
    using namespace InterfaceSegregationPrinciple01;

    Document doc{};

    MultiFunctionPrinter printer;
    printer.fax(doc);    // works

    Scanner scanner;
    scanner.fax(doc);    // does not work !!!
}

static void test_conceptual_example_isp()
{
    using namespace InterfaceSegregationPrinciple02;

    Document doc;

    Printer printer;
    Scanner scanner;
    FaxMachine faxmachine;

    Machine machine{ printer , scanner , faxmachine };

    machine.scan(doc);   // works

    machine.fax(doc);    // works too
}

void test_isp()
{
    test_anti_conceptual_example_isp();
    test_conceptual_example_isp();
}

// ===========================================================================
// End-of-File
// ===========================================================================
