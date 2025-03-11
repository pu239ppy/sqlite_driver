cmake_minimum_required(VERSION 3.10)
project(SQLIteDriver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(sqlitedriverlib
    sqlitewriter.cpp
    sqlitereader.cpp

)

target_link_libraries(sqlitedriverlib PRIVATE
    sqlite3
)

add_executable(sqlitedriver sqlitedriver.m.cpp)
target_link_libraries(sqlitedriver
    sqlitedriverlib
)

target_include_directories(sqlitedriver PRIVATE
    "."
)
