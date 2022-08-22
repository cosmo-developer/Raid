cmake_minimum_required(VERSION 3.10)

project(Raid)

add_subdirectory("third-party/raylib")

include_directories("include" "third-party/raylib/src")

add_executable(raiddev "src/raid_main.cpp")

target_link_libraries(raiddev raylib)