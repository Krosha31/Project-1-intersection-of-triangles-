cmake_minimum_required(VERSION 3.20)
project(Programming)

set(CMAKE_CXX_STANDARD 20)

#
include(FetchContent)
#FetchContent_Declare(
#        googletest
#        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
#)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#FetchContent_MakeAvailable(googletest)
#
FetchContent_Declare(SFML
       GIT_REPOSITORY https://github.com/SFML/SFML.git
      GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)


include_directories(${PROJECT_SOURCE_DIR}/src/point)
include_directories(${PROJECT_SOURCE_DIR}/src/triangle)
include_directories(${PROJECT_SOURCE_DIR}/src/draw)


add_executable(Programming main.cpp src/point/point.cpp src/triangle/triangle.cpp)
target_link_libraries(Programming sfml-graphics gtest)

#  sfml-graphics
include(GoogleTest)
