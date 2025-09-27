cmake_minimum_required(VERSION 3.10)
project(arachne_filesystem)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(arachne_filesystem ${SOURCES})

find_package(Curses REQUIRED)
target_link_libraries(arachne_filesystem PRIVATE ${CURSES_LIBRARIES})

target_compile_options(arachne_filesystem PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS arachne_filesystem DESTINATION bin)
