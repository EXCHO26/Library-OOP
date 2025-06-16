cmake_minimum_required(VERSION 3.14)
project(library)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Collect all source files
file(GLOB_RECURSE SOURCES
    main.cpp
    Repo/*/*.cpp
    Repo/*/Units/*.cpp
    Service/*.cpp
)

# Include directories
include_directories(
    Repo/Libr
    Repo/Libr/Units
    Repo/Users
    Repo/Users/Units
    Service
)

# Add the executable
add_executable(library ${SOURCES})