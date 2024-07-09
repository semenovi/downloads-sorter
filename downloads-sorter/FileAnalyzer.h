#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>

class FileAnalyzer {
public:
  FileAnalyzer();
  std::unordered_map<std::string, std::vector<std::string>> analyzeDirectory(const std::string& path);

private:
  std::unordered_map<std::string, std::string> fileCategories;
  void loadFileCategories();
  std::string getCategoryForFile(const std::filesystem::path& filePath);
};