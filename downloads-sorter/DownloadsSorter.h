#pragma once
#include "FileAnalyzer.h"
#include <string>

class DownloadsSorter {
public:
  void run(const std::string& path);
private:
  FileAnalyzer analyzer;
};