cmake_minimum_required(VERSION 3.20)

project(SortingAlgorithms)

set(CMAKE_GENERATOR_PLATFORM Visual Studio 15 2017 Win64)
set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(SortingAlgorithms main.cpp)

target_link_libraries(SortingAlgorithms sfml-graphics sfml-audio)

file(COPY ${CMAKE_SOURCE_DIR}/src/Pictures/dvd.png DESTINATION "${CMAKE_BINARY_DIR}/src/")