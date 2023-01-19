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
    private:
        std::string m_path;

    public:
        PdfDocument(std::string path) : m_path{ path } {}

        std::vector<std::string> getText() override {
            return { "Text from PDF" };
        }
    };

    class HtmlDocument : public IDocument 
    {
    private:
        std::string m_path;

    public:
        HtmlDocument(std::string path) : m_path{ path } {}

        std::vector<std::string> getText() override {
            return { "Text from HTML" };
        }
    };

    class OdtDocument : public IDocument 
    {
    private:
        std::string m_path;

    public:
        OdtDocument(std::string path) : m_path{ path } {}

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

    template <typename T>
    using DocumentType = std::unique_ptr<T>;

    using Document = DocumentType<IDocument>;

    using DocumentReader = std::function<Document(std::string)>;

    class DocumentFactory
    {
    private:
        std::unordered_map<std::string, DocumentReader> m_readers;

    public:
        void add(const std::string& extension, const DocumentReader& reader) {
            m_readers.emplace(extension, reader);
        }

        Document open(std::string path) {
            auto lastDot = path.find_last_of('.');
            if (lastDot != std::string::npos) {
                std::string extension = path.substr(lastDot + 1);
                DocumentReader& reader = m_readers.at(extension);
                Document document = reader(path);
                return document;
            }
            else {
                throw std::invalid_argument{ "Trying to open a file with no extension" };
            }
        }
    };
}

void test_documents()
{
    using namespace DocumentsExample;

    auto factory = DocumentFactory{};

    factory.add(
        "pdf",
        [](auto path) -> Document {
            return std::make_unique<PdfDocument>(path);
        }
    );

    factory.add(
        "html",
        [](auto path) -> Document {
            return std::make_unique<HtmlDocument>(path);
        }
    );

    factory.add(
        "odt",
        [](auto path) -> Document {
            return std::make_unique<OdtDocument>(path);
        }
    );

    Document document = factory.open("file.odt");

    std::cout << document->getText().front();
}

// ===========================================================================
// End-of-File
// ===========================================================================
