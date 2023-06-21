cmake_minimum_required(VERSION 3.20)
project(Intersection_of_triangles)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
       GIT_REPOSITORY https://github.com/SFML/SFML.git
      GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)


include_directories(${PROJECT_SOURCE_DIR}/src/point)
include_directories(${PROJECT_SOURCE_DIR}/src/triangle)
include_directories(${PROJECT_SOURCE_DIR}/src/draw)


add_executable(Programming main.cpp src/point/point.cpp src/polygon/polygon.cpp src/draw/draw.cpp)
target_link_libraries(Intersection_of_triangles sfml-graphics)

