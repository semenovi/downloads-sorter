#include "DownloadsSorter.h"
#include <iostream>

void DownloadsSorter::run(const std::string& path) {
  std::cout << "DIR analysis: " << path << std::endl;
  FileAnalyzer::analyzeDirectory(path);
}