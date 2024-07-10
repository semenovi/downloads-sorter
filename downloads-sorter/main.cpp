#include "DownloadsSorter.h"
#include <iostream>
#include <Windows.h>
#include <fcntl.h>
#include <io.h>

int main(int argc, char* argv[]) {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  _setmode(_fileno(stdout), _O_U8TEXT);

  if (argc != 2) {
    std::wcerr << L"Usage: " << argv[0] << L" <directory_path>" << std::endl;
    return 1;
  }

  DownloadsSorter sorter;
  sorter.run(argv[1]);

  return 0;
}