#include "FolderAnalyzer.h"
#include <algorithm>
#include <iostream>
#include <sstream>

FolderAnalyzer::FolderAnalyzer(FileAnalyzer& fa) : fileAnalyzer(fa), totalFileCount(0) {}

std::string FolderAnalyzer::analyzeFolderType(const std::filesystem::path& folderPath) {
  resetAnalysis();
  analyzeFolder(folderPath);
  return determineFolderType();
}

std::unordered_map<std::string, std::string> FolderAnalyzer::analyzeFirstLevelSubdirectories(const std::filesystem::path& folderPath) {
  std::unordered_map<std::string, std::string> subdirectoryTypes;

  for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
    if (entry.is_directory()) {
      std::string subFolderType = analyzeFolderType(entry.path());
      subdirectoryTypes[entry.path().filename().string()] = subFolderType;
    }
  }

  return subdirectoryTypes;
}

void FolderAnalyzer::analyzeFolder(const std::filesystem::path& folderPath) {
  for (const auto& entry : std::filesystem::recursive_directory_iterator(folderPath)) {
    if (entry.is_regular_file()) {
      analyzeFile(entry.path());
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

  std::vector<std::pair<std::string, int>> sortedTypes(fileTypeCounts.begin(), fileTypeCounts.end());
  std::sort(sortedTypes.begin(), sortedTypes.end(),
    [](const auto& a, const auto& b) { return a.second > b.second; });

  std::string dominantType = sortedTypes[0].first;
  double dominantRatio = static_cast<double>(sortedTypes[0].second) / totalFileCount;

  if (dominantRatio > 0.7) {
    return dominantType;
  }
  else {
    std::ostringstream oss;
    for (size_t i = 0; i < std::min(size_t(3), sortedTypes.size()); ++i) {
      if (i > 0) oss << ", ";
      oss << sortedTypes[i].first;
    }
    return oss.str();
  }
}

void FolderAnalyzer::resetAnalysis() {
  fileTypeCounts.clear();
  totalFileCount = 0;
}