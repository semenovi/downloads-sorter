#include "ExtensionUpdater.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

ExtensionUpdater::ExtensionUpdater() {
  loadConfig();
}

bool ExtensionUpdater::loadConfig() {
  std::ifstream configFile("extsrc.json");
  if (!configFile.is_open()) {
    std::wcerr << L"Failed to open extsrc.json" << std::endl;
    return false;
  }

  nlohmann::json config;
  configFile >> config;

  std::string url = config["extensions_url"];
  extensionsUrl = std::wstring(url.begin(), url.end());

  return true;
}

bool ExtensionUpdater::downloadExtensions() {
  return downloadFromUrl();
}

bool ExtensionUpdater::downloadFromUrl() {
  HINTERNET hInternet = InternetOpenW(L"ExtensionUpdater", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
  if (!hInternet) {
    std::wcerr << L"Failed to open WinINet" << std::endl;
    return false;
  }

  HINTERNET hConnect = InternetOpenUrlW(hInternet, extensionsUrl.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
  if (!hConnect) {
    std::wcerr << L"Failed to connect to URL" << std::endl;
    InternetCloseHandle(hInternet);
    return false;
  }

  std::string buffer;
  char szData[1024];
  DWORD dwBytesRead;

  while (InternetReadFile(hConnect, szData, sizeof(szData) - 1, &dwBytesRead) && dwBytesRead > 0) {
    szData[dwBytesRead] = '\0';
    buffer += szData;
  }

  InternetCloseHandle(hConnect);
  InternetCloseHandle(hInternet);

  parseDownloadedData(buffer);
  return true;
}

void ExtensionUpdater::parseDownloadedData(const std::string& data) {
  try {
    nlohmann::json j = nlohmann::json::parse(data);

    for (const auto& [extension, info] : j.items()) {
      std::string lowerExt = extension;
      std::transform(lowerExt.begin(), lowerExt.end(), lowerExt.begin(),
        [](unsigned char c) { return std::tolower(c); });
      downloadedExtensions.push_back("." + lowerExt);
    }
  }
  catch (nlohmann::json::parse_error& e) {
    std::cerr << "JSON parsing error: " << e.what() << std::endl;
  }
}

void ExtensionUpdater::classifyExtensions(const std::unordered_map<std::string, std::vector<std::string>>& existingCategories) {
  updatedCategories = existingCategories;

  for (const auto& ext : downloadedExtensions) {
    bool classified = false;
    for (const auto& [category, extensions] : existingCategories) {
      if (std::find(extensions.begin(), extensions.end(), ext) != extensions.end()) {
        classified = true;
        break;
      }
    }
    if (!classified) {
      updatedCategories["other"].push_back(ext);
    }
  }
}

std::unordered_map<std::string, std::vector<std::string>> ExtensionUpdater::getUpdatedCategories() const {
  return updatedCategories;
}