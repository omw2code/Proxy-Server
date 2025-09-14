cmake_minimum_required(VERSION 3.22)
project("Greek Backend")

# Compiler configurations
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Packages
find_package(Boost REQUIRED)

# Process sub dirs
add_subdirectory(src)