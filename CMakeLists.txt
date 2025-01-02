cmake_minimum_required(VERSION 3.5.0)
project(JumperBoii.out VERSION 0.1.0 LANGUAGES C CXX)

SET(CMAKE_CXX_STANDARD 20)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/)
include_directories(include include/game include/testing include/user_interface include/weapons)
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")

add_executable(JumperBoii.out ${SOURCES})

target_link_libraries(JumperBoii.out PRIVATE sfml-graphics sfml-window sfml-system)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
