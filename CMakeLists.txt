cmake_minimum_required(VERSION 3.11)
project(DSA_Game_Project VERSION 0.1.0 LANGUAGES C CXX)

add_subdirectory(src)


add_executable(build main.cpp)

target_include_directories(build PUBLIC "${PROJECT_BINARY_DIR}/include")
target_link_libraries(build raylib)

include(CTest)
enable_testing()

