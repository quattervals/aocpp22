cmake_minimum_required(VERSION 3.22)

project(
  aocpp
  LANGUAGES CXX
  VERSION 0.1
  DESCRIPTION "Advent of Code 22 with C++")


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Set a default build type if none was specified
set(default_build_type "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
    STRING "Choose the type of build." FORCE)
endif()

if(CMAKE_FIND_ROOT_PATH)
  message(STATUS "Appending install prefix to root path")
  list(APPEND CMAKE_FIND_ROOT_PATH ${PROJECT_SOURCE_DIR})
endif()




add_library(common INTERFACE)

add_subdirectory(${PROJECT_SOURCE_DIR}/app)

add_executable(${PROJECT_NAME} target.cpp)

target_include_directories(common INTERFACE
  ${PROJECT_SOURCE_DIR}/app/

)
target_link_libraries(${PROJECT_NAME} PUBLIC libApp common)

enable_testing()
add_subdirectory(test)
