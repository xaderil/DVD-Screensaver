cmake_minimum_required(VERSION 3.0)

project(dvdAnim)

set(CMAKE_GENERATOR_PLATFORM Visual Studio 15 2017 Win64) # MUST BE SET ACCORDING TO SFML VERSION
set(CMAKE_CXX_STANDARD 17)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML-2.5.1/lib/cmake/SFML) # MUST BE CHANGED TO THE CORRECT SFML LOCATION

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(dvdAnimation main.cpp)

target_link_libraries(dvdAnimation sfml-graphics)

file(COPY ${CMAKE_SOURCE_DIR}/src/Pictures/dvd.png DESTINATION "${CMAKE_BINARY_DIR}/src/")