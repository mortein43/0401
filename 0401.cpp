#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <future>


int loadFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr<< std::endl << "Неможливо відкрити файл: " << filename << std::endl;
        return 0;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    return content.size();
}

int main() {
    system("chcp 1251>nul");
    std::vector<std::string> files = { "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt" }; 

    std::vector<std::future<int>> futures;
    for (const auto& file : files) {
        futures.emplace_back(std::async(std::launch::async, loadFile, file));
    }

    int totalSize = 0;
    for (int i = 0; i < files.size(); ++i) {
        int fileSize = futures[i].get();
        totalSize += fileSize;
        std::cout << "Розмір файлу " << files[i] << " - " << fileSize << " символів." << std::endl;
    }
    std::cout << "Загальний розмір усіх файлів - " << totalSize << " символів." << std::endl;

    return 0;
}
