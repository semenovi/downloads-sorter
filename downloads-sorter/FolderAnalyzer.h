#pragma once
#include "FileAnalyzer.h"
#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

class FolderAnalyzer {
public:
  FolderAnalyzer(FileAnalyzer& fileAnalyzer);
  std::string analyzeFolderType(const std::filesystem::path& folderPath);
  std::unordered_map<std::string, std::string> analyzeFirstLevelSubdirectories(const std::filesystem::path& folderPath);

private:
  FileAnalyzer& fileAnalyzer;
  std::unordered_map<std::string, int> fileTypeCounts;
  int totalFileCount;

  void analyzeFolder(const std::filesystem::path& folderPath);
  void analyzeFile(const std::filesystem::path& filePath);
  std::string determineFolderType();
  void resetAnalysis();
};
