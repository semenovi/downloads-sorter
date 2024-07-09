#include "FileAnalyzer.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

FileAnalyzer::FileAnalyzer() {
  loadFileCategories();
}

void FileAnalyzer::loadFileCategories() {
  std::ifstream configFile("file_categories.json");
  if (!configFile.is_open()) {
    throw std::runtime_error("Unable to open file_categories.json");
  }

  nlohmann::json config;
  configFile >> config;

  for (auto& [category, extensions] : config.items()) {
    for (const auto& ext : extensions) {
      fileCategories[ext] = category;
    }
  }
}

std::string FileAnalyzer::getCategoryForFile(const std::filesystem::path& filePath) {
  std::string extension = filePath.extension().string();
  auto it = fileCategories.find(extension);
  if (it != fileCategories.end()) {
    return it->second;
  }
  return "other";
}

std::unordered_map<std::string, std::vector<std::string>> FileAnalyzer::analyzeDirectory(const std::string& path) {
  std::unordered_map<std::string, std::vector<std::string>> groupedFiles;

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      std::string category = getCategoryForFile(entry.path());
      groupedFiles[category].push_back(entry.path().filename().string());
    }
  }

  return groupedFiles;
}