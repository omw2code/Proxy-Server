cmake_minimum_required(VERSION 3.22)
project("Proxy")

# Compiler configurations
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Packages
find_package(Boost REQUIRED)

# Process sub dirs
add_subdirectory(src)