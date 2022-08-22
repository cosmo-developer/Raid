cmake_minimum_required(VERSION 3.10)

project(Raid)

add_subdirectory("third-party/raylib")
add_subdirectory("third-party/imgui")

add_executable(raiddev "src/raid_main.cpp")