#pragma once
#include "FileAnalyzer.h"
#include "FolderAnalyzer.h"
#include <string>

class DownloadsSorter {
public:
  DownloadsSorter();
  void run(const std::string& path);
private:
  FileAnalyzer fileAnalyzer;
  FolderAnalyzer folderAnalyzer;
};