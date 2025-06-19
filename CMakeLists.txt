cmake_minimum_required(VERSION 3.14)
project(library)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES 
    "main.cpp"
    "Repo/*/*.cpp"
    "Repo/*/Units/*.cpp"
    "Service/*.cpp"
    "Action/*.cpp"
    "Action/Units/*.cpp"
    "Action/Units/SessionCommand.cpp"
    "Action/Units/InfoCommand.cpp"
    "Action/Units/AddCommand.cpp"
    "Action/Units/RemoveCommand.cpp"
    "Action/Units/FindCommand.cpp"
    "Action/Units/ChangeCommand.cpp"
    "Action/Units/TakeCommand.hpp"
    "Action/Units/ReturnCommand.hpp"
)

include_directories(
    .
    Repo/Libr
    Repo/Libr/Units
    Repo/Users
    Repo/Users/Units
    Service
    Action
    Action/Units
)

add_executable(library ${SOURCES})