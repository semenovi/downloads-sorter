#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <Windows.h>
#include <WinInet.h>
#include <nlohmann/json.hpp>

#pragma comment(lib, "Wininet.lib")

class ExtensionUpdater {
public:
  ExtensionUpdater();
  bool downloadExtensions();
  void classifyExtensions(const std::unordered_map<std::string, std::vector<std::string>>& existingCategories);
  std::unordered_map<std::string, std::vector<std::string>> getUpdatedCategories() const;

private:
  std::vector<std::string> downloadedExtensions;
  std::unordered_map<std::string, std::vector<std::string>> updatedCategories;
  std::wstring extensionsUrl;

  bool loadConfig();
  bool downloadFromUrl();
  void parseDownloadedData(const std::string& data);
};