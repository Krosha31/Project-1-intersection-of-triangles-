cmake_minimum_required(VERSION 3.20)
project(Test)

set(CMAKE_CXX_STANDARD 20)

#
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)



include_directories(${PROJECT_SOURCE_DIR}/src/point)
include_directories(${PROJECT_SOURCE_DIR}/src/triangle)
include_directories(${PROJECT_SOURCE_DIR}/src/draw)
include_directories(${PROJECT_SOURCE_DIR}/src/polygon)


add_executable(Programming test.cpp)
target_link_libraries(Programming gtest)


include(GoogleTest)
