cmake_minimum_required(VERSION 3.11)
project(DSA_Game_Project VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_subdirectory(src)


add_executable(build main.cpp "src/Entity.cpp")

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
  include(FetchContent)
  FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
  )
  FetchContent_GetProperties(raylib)
  if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
  endif()
endif()

set(RAYGUI_VERSION 4.0)
find_package(raygui ${RAYGUI_VERSION} QUIET)
if(NOT raygui_FOUND)
 include(FetchContent)
 FetchContent_Declare(
    raygui
    URL https://github.com/raysan5/raygui/archive/refs/tags/4.0.tar.gz
 )
 FetchContent_GetProperties(raygui)
 if (NOT raygui_POPULATED)
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raygui)
  endif()
endif()
option(BUILD_RAYGUI_EXAMPLES "Build the examples." OFF)


target_include_directories(build PUBLIC include "${raygui_SOURCE_DIR}/src")
include_directories(include "${raygui_SOURCE_DIR}/src")
target_link_libraries(build raylib)

include(CTest)
enable_testing()

