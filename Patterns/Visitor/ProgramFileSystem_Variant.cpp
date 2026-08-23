// ===========================================================================
// ProgramFileSystem_Variant.cpp // Filesystem Test // Visitor Pattern
// ===========================================================================

#include <cstddef>
#include <filesystem>
#include <format>
#include <memory>
#include <print>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace {

    class File
    {
    public:
        File() = default;

        File(std::string name, std::size_t size)
            : m_name{ std::move(name) }, m_size{ size }
        {}

        [[nodiscard]]
        const std::string& name() const noexcept { return m_name; }

        [[nodiscard]]
        std::size_t size() const noexcept { return m_size; }

    private:
        std::string m_name;
        std::size_t m_size{};
    };

    // forward declaration
    class Directory;

    // A directory contains FileSystemElements. 
    // Therefore, we first need a wrapper.
    using FileSystemElement = std::variant<File, std::unique_ptr<Directory>>;

    class Directory
    {
    public:
        Directory() = default;

        explicit Directory(std::string name)
            : m_name{ std::move(name) }
        {}

        [[nodiscard]]
        const std::string& name() const noexcept { return m_name; }

        [[nodiscard]]
        const std::vector<FileSystemElement>& children() const noexcept
        {
            return m_contents;
        }

        void addFile(File file)
        {
            m_contents.emplace_back(std::move(file));
        }

        void addDirectory(std::unique_ptr<Directory> directory)
        {
            m_contents.emplace_back(std::move(directory));
        }

    private:
        std::string m_name;
        std::vector<FileSystemElement> m_contents;
    };

    // ===========================================================================

    class PrintVisitor
    {
    public:
        void operator()(const File& file)
        {
            std::print("{:>{}}", "", m_depth);
            std::println("File: {} ({} bytes)", file.name(), file.size());
        }

        void operator()(const std::unique_ptr<Directory>& directory)
        {
            m_depth += 2;

            std::print("{:>{}}", "", m_depth);
            std::println("Directory: {}", directory->name());

            for (const auto& child : directory->children()) {
                std::visit(*this, child);
            }

            m_depth -= 2;
        }

    private:
        std::size_t m_depth{};
    };

    class SizeVisitor
    {
    public:
        void operator()(const File& file)
        {
            m_totalSize += file.size();
        }

        void operator()(const std::unique_ptr<Directory>& directory)
        {
            for (const auto& child : directory->children()) {
                std::visit(*this, child);
            }
        }

        [[nodiscard]]
        std::size_t totalSize() const noexcept { return m_totalSize; }

    private:
        std::size_t m_totalSize{};
    };
}

// ===========================================================================

static void exploreDirectory(const std::filesystem::path& path, Directory& currentDir) {

    if (!std::filesystem::exists(path) || !std::filesystem::is_directory(path)) {
        return;
    }

    // std::filesystem::directory_iterator throws exceptions in case of permission issues;
    // using std::error_code allows it to run more robustly.
    std::error_code ec;

    for (const auto& entry : std::filesystem::directory_iterator(path, ec)) {

        const std::filesystem::path filename = entry.path().filename();

        if (entry.is_directory()) {

            // 1. create a new subdirectory object (store the raw pointer)
            auto subDirPtr = std::make_unique<Directory>(filename.string());

            // 2. create a reference of this object
            Directory& subDirRef = *subDirPtr;

            // 3. transfer ownership of this subdirectory to the current directory
            currentDir.addDirectory(std::move(subDirPtr));

            // 4. do recursion using the path and the reference of the subdirectory object
            exploreDirectory(entry.path(), subDirRef);
        }
        else if (entry.is_regular_file()) {

            std::error_code sizeErr;
            std::uintmax_t filesize = std::filesystem::file_size(entry, sizeErr);

            // in case of read errors regarding file size (e.g., system files), fallback to 0.
            if (sizeErr) {
                filesize = 0;
            }

            // 1. create a new File object
            File file{ filename.string(), static_cast<std::size_t>(filesize) };

            // 2. transfer ownership of this file object to the current directory
            currentDir.addFile(file);}
    }
}

// ===========================================================================


// directory with less files, no subdirectories
// 
// Absolute path:
// constexpr const char* path1 =
//    R"(C:\Development\GitHub_Cpp_Repositories\Cpp_Design_Patterns\Patterns\CompositePattern\Resources)";

constexpr const char* path1 = R"(..\..\Patterns\CompositePattern\Resources)";

// directory without many files and subdirectories
// Absolute path:
//constexpr const char* path2 =
//    R"(C:\Development\GitHub_Cpp_Repositories\Cpp_Design_Patterns\Patterns\CompositePattern\x64)";

constexpr const char* path2 = R"(..\..\Patterns\CompositePattern\x64)";

// plain composite pattern
static void test_filesystem_example_using_variant_01() {

    std::string source{ path2 };
    std::filesystem::path path{ source };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", source);
    }
    else {
        Directory root{ source };
        exploreDirectory(path, root);
    }
}

// composite pattern & visitor pattern (printing)
static void test_filesystem_example_using_variant_02() {

    std::string source{ path2 };
    std::filesystem::path path{ source };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", source);
    }
    else {
        auto rootDirPtr = std::make_unique<Directory>(source);

        exploreDirectory(path, *rootDirPtr);

        FileSystemElement rootElement{ std::move(rootDirPtr) };

        PrintVisitor visitor;

        std::visit(visitor, rootElement);
    }
}

// composite pattern & visitor pattern (calculating total size)
static void test_filesystem_example_using_variant_03() {

    std::string source{ path2 };
    std::filesystem::path path{ source };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", source);
    }
    else {
        auto rootDirPtr = std::make_unique<Directory>(source);

        exploreDirectory(path, *rootDirPtr);

        FileSystemElement rootElement{ std::move(rootDirPtr) };

        SizeVisitor visitor;

        std::visit(visitor, rootElement);

        std::println("Total size: {} bytes.", visitor.totalSize());
    }
}

void test_filesystem_example_using_variant() {

    test_filesystem_example_using_variant_01();  // just composite pattern
    test_filesystem_example_using_variant_02();  // composite pattern & visitor pattern (printing)
    test_filesystem_example_using_variant_03();  // composite pattern & visitor pattern (calculating total size)
}

// ===========================================================================
// End-of-File
// ===========================================================================
