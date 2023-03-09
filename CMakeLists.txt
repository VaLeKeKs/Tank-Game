cmake_minimum_required(VERSION 3.22)
project(Tanks)

set(CMAKE_CXX_STANDARD 20)
find_package(SFML COMPONENTS graphics REQUIRED)

add_executable(Tanks src/main.cpp src/Tank.cpp src/Tank.h src/Camera.cpp src/Camera.h src/Map.cpp src/Map.h src/Bullet.cpp src/Bullet.h)
target_link_libraries(Tanks PRIVATE sfml-graphics sfml-window)
