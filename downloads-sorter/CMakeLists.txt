cmake_minimum_required(VERSION 3.10)
project(DownloadsSorter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(nlohmann_json)

add_executable(downloads_sorter
    main.cpp
    DownloadsSorter.cpp
    FileAnalyzer.cpp
)

target_link_libraries(downloads_sorter PRIVATE nlohmann_json::nlohmann_json)
target_include_directories(downloads_sorter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET downloads_sorter POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_SOURCE_DIR}/file_categories.json
    $<TARGET_FILE_DIR:downloads_sorter>/file_categories.json
)

set(DEFAULT_ARGS "\"C:/Users/user/Downloads\"")

set_target_properties(downloads_sorter PROPERTIES
    VS_DEBUGGER_COMMAND_ARGUMENTS "${DEFAULT_ARGS}"
    VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:downloads_sorter>"
)