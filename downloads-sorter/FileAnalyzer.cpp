#include "FileAnalyzer.h"
#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <Windows.h>

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

std::unordered_map<std::string, std::vector<std::wstring>> FileAnalyzer::analyzeDirectory(const std::string& path) {
  std::unordered_map<std::string, std::vector<std::wstring>> groupedFiles;

  for (const auto& entry : std::filesystem::directory_iterator(path)) {
    if (entry.is_regular_file()) {
      std::string category = getCategoryForFile(entry.path());
      std::wstring fileName = entry.path().filename().wstring();
      groupedFiles[category].push_back(fileName);
    }
  }

  return groupedFiles;
}