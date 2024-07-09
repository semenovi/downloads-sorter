// FileAnalyzer.h
#pragma once
#include <string>
#include <filesystem>

class FileAnalyzer {
public:
  static void analyzeDirectory(const std::string& path, int depth = 0);
private:
  static void printIndent(int depth);
};