#include "FileAnalyzer.h"
#include <iostream>

void FileAnalyzer::analyzeDirectory(const std::string& path, int depth) {
  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    printIndent(depth);
    std::cout << entry.path().filename().string();
    if (entry.is_directory()) {
      std::cout << " (DIR)";
    }
    std::cout << std::endl;

    if (entry.is_directory()) {
      analyzeDirectory(entry.path().string(), depth + 1);
    }
  }
}

void FileAnalyzer::printIndent(int depth) {
  for (int i = 0; i < depth; ++i) {
    std::cout << "  ";
  }
}