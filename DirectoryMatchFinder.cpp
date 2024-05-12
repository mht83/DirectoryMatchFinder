//////////////////////////////////////////////written by mht83/////////////////////////////////////////
#include <iostream>
#include <filesystem>
#include <regex>
#include <vector>

namespace fs = std::filesystem;

std::vector<fs::path> find_files_matching_regex(const fs::path& directory, const std::string& pattern) {
    std::vector<fs::path> matching_files;
    std::regex regex_pattern(pattern);

    if (!fs::is_directory(directory)) {
        std::cerr << "The provided path is not a valid directory.\n";
        exit(1);
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (fs::is_regular_file(entry) && std::regex_search(entry.path().filename().string(), regex_pattern)) {
            matching_files.push_back(entry.path());
        }
    }

    return matching_files;
}

int main() {
    std::string directory_path;
    std::string regex_pattern;
    std::cout << "Enter the directory path: ";
    std::cin >> directory_path;
    std::cout << "Enter the regular expression pattern: ";
    std::cin >> regex_pattern;

    auto matching_files = find_files_matching_regex(directory_path, regex_pattern);
    std::cout << "Files matching '" << regex_pattern << "':\n";
    for (const auto& file_path : matching_files) {
        std::cout << file_path << '\n';
    }

    return 0;
}
