#pragma once
#include "FileAnalyzer.h"
#include "FolderAnalyzer.h"
#include <string>
#include <unordered_map>
#include <vector>

class DownloadsSorter {
public:
  DownloadsSorter();
  void run(const std::string& path);
  std::unordered_map<std::string, std::vector<std::string>> getFileCategories() const;
  void updateFileCategories(const std::unordered_map<std::string, std::vector<std::string>>& newCategories);

private:
  FileAnalyzer fileAnalyzer;
  FolderAnalyzer folderAnalyzer;
};