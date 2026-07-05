cmake_minimum_required(VERSION 3.10)

project(MemDB)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(memdb
    src/main.cpp
    src/Database.cpp
    src/Server.cpp
    src/LRUCache.cpp
)

find_package(Threads REQUIRED)

target_link_libraries(memdb Threads::Threads)