// ===========================================================================
// ProgramFileSystem.cpp // Filesystem Test // Visitor Pattern
// ===========================================================================

#include "File.h"
#include "Directory.h"

#include "PrintVisitor.h"
#include "SizeVisitor.h"

#include <cstdint>
#include <filesystem>
#include <memory>
#include <print>
#include <string>
#include <system_error>
#include <utility>

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

            // 3. transfer ownership to the current directory IFileComponent container
            currentDir.addFileComponent(std::move(subDirPtr));

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
            auto file = std::make_unique<File>(filename.string(), static_cast<std::size_t>(filesize));
            
            // 2. transfer ownership to the current directory IFileComponent container
            currentDir.addFileComponent(std::move(file));
        }
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
static void test_filesystem_example_01() {

    std::string source { path2 };
    std::filesystem::path path { source };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", source);
    }
    else {
        Directory root{ source };
        exploreDirectory(path, root);
    }
}

// composite pattern & visitor pattern (printing)
static void test_filesystem_example_02() {

    std::string source{ path2 };
    std::filesystem::path path{ source };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", source);
    }
    else {
        Directory root{ source };
        exploreDirectory(path, root);

        PrintVisitor visitor;
        root.accept(visitor);
    }
}

// composite pattern & visitor pattern (calculating total size)
static void test_filesystem_example_03() {

    std::string source{ path2 };
    std::filesystem::path path{ source };

    if (!std::filesystem::exists(path)) {
        std::println("Given path does not exist: {}", source);
    }
    else {
        Directory root{ source };
        exploreDirectory(path, root);

        SizeVisitor visitor;
        root.accept(visitor);

        std::println("Total size: {} bytes.", visitor.totalSize());
    }
}

void test_filesystem_example() {

    test_filesystem_example_01();  // just composite pattern
    test_filesystem_example_02();  // composite pattern & visitor pattern (printing)
    test_filesystem_example_03();  // composite pattern & visitor pattern (calculating total size)
}

// ===========================================================================
// End-of-File
// ===========================================================================
