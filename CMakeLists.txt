cmake_minimum_required(VERSION 3.10)
project(arachne_filesystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(arachne_filesystem
    src/main.cpp
    src/FileManager.cpp
    src/UI.cpp
    src/Input.cpp
)

find_package(Curses REQUIRED)
target_link_libraries(arachne_filesystem PRIVATE ${CURSES_LIBRARIES})
