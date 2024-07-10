#include "DownloadsSorter.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

void DownloadsSorter::run(const std::string& path) {
  std::wcout << L"Analyzing directory: " << std::wstring(path.begin(), path.end()) << std::endl << std::endl;

  auto groupedFiles = analyzer.analyzeDirectory(path);

  for (const auto& [category, files] : groupedFiles) {
    std::wcout << std::setw(15) << std::left << std::wstring(category.begin(), category.end()) << L": " << files.size() << L" files" << std::endl;
    for (const auto& file : files) {
      std::wcout << L"  - " << std::wstring(file.begin(), file.end()) << std::endl;
    }
    std::wcout << std::endl;
  }
}