#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>

class FileAnalyzer {
public:
  FileAnalyzer();
  std::unordered_map<std::string, std::vector<std::wstring>> analyzeDirectory(const std::string& path);
  std::string getCategoryForFile(const std::filesystem::path& filePath); // Перемещено в public

private:
  std::unordered_map<std::string, std::string> fileCategories;
  void loadFileCategories();
};