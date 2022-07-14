// ===========================================================================
// Factory a.k.a. Simple Factory Pattern // Documents
// ===========================================================================

#include <iostream>
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>

namespace DocumentsExample {

    struct IDocument 
    {
        virtual ~IDocument() = default;
        virtual std::vector<std::string> getText() = 0;
    };

    class PdfDocument : public IDocument 
    {
    public:
        explicit PdfDocument() {}
        explicit PdfDocument(std::string path) {}

        std::vector<std::string> getText() override {
            return { "Text from PDF" };
        }
    };

    class HtmlDocument : public IDocument 
    {
    public:
        explicit HtmlDocument() {}
        explicit HtmlDocument(std::string path) {}

        std::vector<std::string> getText() override {
            return { "Text from HTML" };
        }
    };

    class OdtDocument : public IDocument 
    {
    public:
        explicit OdtDocument() {}
        explicit OdtDocument(std::string path) {}

        std::vector<std::string> getText() override { 
            return { "Text from ODT" }; 
        }
    };

    // non recommendable implementation
    std::unique_ptr<IDocument> open(std::string path) 
    {
        if (path.ends_with(".pdf"))
            return std::make_unique<PdfDocument>(path);

        if (path.ends_with(".html")) 
            return std::make_unique<HtmlDocument>(path);

        return nullptr;
    }

    class DocumentFactory
    {
    public:
        using DocumentType = std::unique_ptr<IDocument>;

        using ConcreteOpener = std::function<DocumentType(std::string)>;

        void Register(const std::string& extension, const ConcreteOpener& opener) {
            openerByExtension.emplace(extension, opener);
        }

        DocumentType open(std::string path) {
            auto last_dot = path.find_last_of('.');
            if (last_dot != std::string::npos) {
                auto extension = path.substr(last_dot + 1);
                auto& opener = openerByExtension.at(extension);
                auto document = opener(path);
                return document;
            }
            else {
                throw std::invalid_argument{ "Trying to open a file with no extension" };
            }
        }

    private:
        std::unordered_map<std::string, ConcreteOpener> openerByExtension;
    };
}

void test_documents()
{
    using namespace DocumentsExample;

    auto document_opener = DocumentFactory{};

    document_opener.Register(
        "pdf",
        [](auto path) -> DocumentFactory::DocumentType {
            return std::make_unique<PdfDocument>(path);
        }
    );

    document_opener.Register(
        "html",
        [](auto path) -> DocumentFactory::DocumentType {
            return std::make_unique<HtmlDocument>(path);
        }
    );

    document_opener.Register(
        "odt",
        [](auto path) -> DocumentFactory::DocumentType {
            return std::make_unique<OdtDocument>(path);
        }
    );

    auto document = document_opener.open("file.odt");

    std::cout << document->getText().front();
}

// ===========================================================================
// End-of-File
// ===========================================================================
