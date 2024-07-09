#include "DownloadsSorter.h"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " <directory_path>" << std::endl;
    return 1;
  }

  DownloadsSorter sorter;
  sorter.run(argv[1]);

  return 0;
}