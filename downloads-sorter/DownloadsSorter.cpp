#include "DownloadsSorter.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>

DownloadsSorter::DownloadsSorter() : folderAnalyzer(fileAnalyzer) {}

void DownloadsSorter::run(const std::string& path) {
  std::wcout << L"Analyzing directory: " << std::wstring(path.begin(), path.end()) << std::endl << std::endl;

  std::string folderType = folderAnalyzer.analyzeFolderType(path);
  std::wcout << L"Folder type: " << std::wstring(folderType.begin(), folderType.end()) << std::endl << std::endl;

  auto groupedFiles = fileAnalyzer.analyzeDirectory(path);

  std::wcout << L"File type distribution:" << std::endl;
  for (const auto& [category, files] : groupedFiles) {
    double percentage = (static_cast<double>(files.size()) / groupedFiles.size()) * 100.0;
    std::wcout << std::setw(15) << std::left << std::wstring(category.begin(), category.end())
      << L": " << files.size() << L" files ("
      << std::fixed << std::setprecision(2) << percentage << L"%)" << std::endl;
  }
  std::wcout << std::endl;

  std::wcout << L"Detailed file list:" << std::endl;
  for (const auto& [category, files] : groupedFiles) {
    std::wcout << std::wstring(category.begin(), category.end()) << L":" << std::endl;
    for (const auto& file : files) {
      std::wcout << L"  - " << std::wstring(file.begin(), file.end()) << std::endl;
    }
    std::wcout << std::endl;
  }
}