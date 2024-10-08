#include "DownloadsSorter.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <filesystem>

DownloadsSorter::DownloadsSorter() : folderAnalyzer(fileAnalyzer) {}

void DownloadsSorter::run(const std::string& path) {
  std::wcout << L"Analyzing directory: " << std::wstring(path.begin(), path.end()) << std::endl << std::endl;

  std::string folderType = folderAnalyzer.analyzeFolderType(path);
  std::wcout << L"Main folder type: " << std::wstring(folderType.begin(), folderType.end()) << std::endl << std::endl;

  auto groupedFiles = fileAnalyzer.analyzeDirectory(path);
  auto subdirectories = folderAnalyzer.analyzeFirstLevelSubdirectories(path);

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
      std::wcout << L"  - " << file << std::endl;
    }
    std::wcout << std::endl;
  }

  std::wcout << L"First-level subdirectories:" << std::endl;
  for (const auto& [subdirName, subdirType] : subdirectories) {
    std::wcout << L"  - " << std::wstring(subdirName.begin(), subdirName.end())
      << L" (Type: " << std::wstring(subdirType.begin(), subdirType.end()) << L")" << std::endl;
  }
  std::wcout << std::endl;
}

std::unordered_map<std::string, std::vector<std::string>> DownloadsSorter::getFileCategories() const {
  return fileAnalyzer.getFileCategories();
}

void DownloadsSorter::updateFileCategories(const std::unordered_map<std::string, std::vector<std::string>>& newCategories) {
  fileAnalyzer.updateFileCategories(newCategories);
  if (fileAnalyzer.saveFileCategories()) {
    std::wcout << L"File categories updated and saved successfully." << std::endl;
  }
  else {
    std::wcerr << L"Failed to save updated file categories." << std::endl;
  }
}