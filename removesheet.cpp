#include <iostream>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <shlobj.h>

namespace fs = std::filesystem;

void deleteRandomFile(const std::wstring& directory) {
    std::vector<fs::path> files;

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (fs::is_regular_file(entry.path())) {
            files.push_back(entry.path());
        }
    }

    if (files.empty()) {
        std::wcout << L"Нет файлов в директории " << directory << std::endl;
        return;
    }

    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int randomIndex = std::rand() % files.size();
    fs::path randomFile = files[randomIndex];

    try {
        std::wcout << L"Удаление случайного файла: " << randomFile.wstring() << std::endl;
        if (DeleteFileW(randomFile.c_str())) {
            std::wcout << L"Файл успешно удален." << std::endl;
        } else {
            std::wcerr << L"Ошибка при удалении файла: " << GetLastError() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::wcerr << L"Ошибка при удалении файла: " << e.what() << std::endl;
        return;
    }

    HRESULT hr = SHEmptyRecycleBinW(nullptr, nullptr, SHERB_NOCONFIRMATION | SHERB_NOPROGRESSUI | SHERB_NOSOUND);
    if (SUCCEEDED(hr)) {
        std::wcout << L"Корзина успешно очищена." << std::endl;
    } else {
        std::wcerr << L"Ошибка при очистке корзины." << std::endl;
    }
}

int main() {
    std::wstring directory = L"C:\\your_path_here";

    deleteRandomFile(directory);

    return 0;
}
