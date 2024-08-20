#include "DownloadsSorter.h"
#include "ExtensionUpdater.h"
#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

void printUsage(const char* programName) {
  std::wcerr << L"Usage:" << std::endl;
  std::wcerr << L"  " << programName << L" <directory_path>" << std::endl;
  std::wcerr << L"  " << programName << L" --update-extensions" << std::endl;
}

int main(int argc, char* argv[]) {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  _setmode(_fileno(stdout), _O_U8TEXT);
  _setmode(_fileno(stderr), _O_U8TEXT);

  if (argc != 2) {
    printUsage(argv[0]);
    return 1;
  }

  std::string arg = argv[1];

  if (arg == "--update-extensions") {
    ExtensionUpdater updater;
    if (updater.downloadExtensions()) {
      DownloadsSorter sorter;
      auto existingCategories = sorter.getFileCategories();
      updater.classifyExtensions(existingCategories);
      auto updatedCategories = updater.getUpdatedCategories();
      sorter.updateFileCategories(updatedCategories);
    }
    else {
      std::wcerr << L"Failed to update extensions." << std::endl;
      return 1;
    }
  }
  else {
    DownloadsSorter sorter;
    sorter.run(arg);
  }

  return 0;
}