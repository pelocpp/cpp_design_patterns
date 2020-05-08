#include <string>  
#include <iostream>  
#include <sstream>  
#include <filesystem>  


// 


namespace fs = std::filesystem;

std::uintmax_t ComputeFileSize(const fs::path& pathToCheck)
{
    if (fs::exists(pathToCheck) && fs::is_regular_file(pathToCheck))
    {
        std::error_code err = std::error_code{};
        auto filesize = fs::file_size(pathToCheck, err);
        if (filesize != static_cast<uintmax_t>(-1))
            return filesize;
    }

    return static_cast<uintmax_t>(-1);
}

void DisplayFileInfo(const std::filesystem::directory_entry& entry, std::string& lead, std::filesystem::path& filename)
{
    std::cout << lead << " " << filename << ", " << ComputeFileSize(entry) << "\n";
}

void DisplayDirectoryTreeImp(const fs::path& pathToShow, int level)
{
    if (fs::exists(pathToShow) && fs::is_directory(pathToShow))
    {
        auto lead = std::string(level * 3, ' ');
        for (const auto& entry : fs::directory_iterator(pathToShow))
        {
            auto filename = entry.path().filename();
            if (fs::is_directory(entry.status()))
            {
                std::cout << lead << "[+] " << filename << "\n";
                DisplayDirectoryTreeImp(entry, level + 1);
                std::cout << "\n";
            }
            else if (fs::is_regular_file(entry.status()))
                DisplayFileInfo(entry, lead, filename);
            else
                std::cout << lead << " [?]" << filename << "\n";
        }
    }
}

// adapted from Modern C++ Programming Cookbook
void DisplayDirectoryTree(const fs::path& pathToShow)
{
    DisplayDirectoryTreeImp(pathToShow, 0);
}

void test_03(std::string path)
{
    fs::path current;
    if (path.empty()) {
        current = fs::current_path();
    }
    else {
        current = { path };
    }

//    fs::path current = fs::current_path();
    DisplayDirectoryTree(current);
}
