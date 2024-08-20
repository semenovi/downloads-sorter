#pragma once
#include <string>
#include <filesystem>
#include <unordered_map>
#include <vector>

class FileAnalyzer {
public:
  FileAnalyzer();
  std::unordered_map<std::string, std::vector<std::wstring>> analyzeDirectory(const std::string& path);
  std::string getCategoryForFile(const std::filesystem::path& filePath);
  std::unordered_map<std::string, std::vector<std::string>> getFileCategories() const;
  void updateFileCategories(const std::unordered_map<std::string, std::vector<std::string>>& newCategories);
  bool saveFileCategories() const;

private:
  std::unordered_map<std::string, std::string> fileCategories;
  std::unordered_map<std::string, std::vector<std::string>> categorizedExtensions;
  void loadFileCategories();
  void updateFileCategoriesMap();
};