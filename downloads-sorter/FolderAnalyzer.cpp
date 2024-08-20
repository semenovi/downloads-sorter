#include "FolderAnalyzer.h"
#include <algorithm>
#include <iostream>

FolderAnalyzer::FolderAnalyzer(FileAnalyzer& fa) : fileAnalyzer(fa), totalFileCount(0) {}

std::string FolderAnalyzer::analyzeFolderType(const std::filesystem::path& folderPath) {
  resetAnalysis();
  analyzeFolder(folderPath);
  return determineFolderType();
}

void FolderAnalyzer::analyzeFolder(const std::filesystem::path& folderPath) {
  for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
    if (entry.is_regular_file()) {
      analyzeFile(entry.path());
    }
    else if (entry.is_directory()) {
      analyzeFolder(entry.path());
    }
  }
}

void FolderAnalyzer::analyzeFile(const std::filesystem::path& filePath) {
  std::string fileType = fileAnalyzer.getCategoryForFile(filePath);
  fileTypeCounts[fileType]++;
  totalFileCount++;
}

std::string FolderAnalyzer::determineFolderType() {
  if (totalFileCount == 0) {
    return "empty";
  }

  std::string dominantType;
  int maxCount = 0;
  for (const auto& [type, count] : fileTypeCounts) {
    if (count > maxCount) {
      maxCount = count;
      dominantType = type;
    }
  }

  double dominantRatio = static_cast<double>(maxCount) / totalFileCount;
  if (dominantRatio > 0.7) {
    return dominantType;
  }
  else {
    return "mixed";
  }
}

void FolderAnalyzer::resetAnalysis() {
  fileTypeCounts.clear();
  totalFileCount = 0;
}