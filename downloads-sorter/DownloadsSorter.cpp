#include "DownloadsSorter.h"
#include <iostream>
#include <iomanip>

void DownloadsSorter::run(const std::string& path) {
  std::cout << "Analyzing directory: " << path << std::endl << std::endl;

  auto groupedFiles = analyzer.analyzeDirectory(path);

  for (const auto& [category, files] : groupedFiles) {
    std::cout << std::setw(15) << std::left << category << ": " << files.size() << " files" << std::endl;
    for (const auto& file : files) {
      std::cout << "  - " << file << std::endl;
    }
    std::cout << std::endl;
  }
}