cmake_minimum_required(VERSION 3.10)
project(DownloadsSorter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(downloads_sorter
    main.cpp
    DownloadsSorter.cpp
    FileAnalyzer.cpp
)

target_include_directories(downloads_sorter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
