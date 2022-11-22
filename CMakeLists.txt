cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
project(RobotRPG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

set(SOURCE_FILES src/main.cpp src/game.cpp src/robot.cpp src/item.cpp)
add_executable(RobotRPG ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS}, include)
target_link_libraries(RobotRPG sfml-system sfml-window sfml-graphics sfml-audio)