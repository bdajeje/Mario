project(Mario)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Release)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

FILE(GLOB_RECURSE INCLUDE_FILES "src/*.hpp")
FILE(GLOB_RECURSE SOURCE_FILES "src/*.cpp")
add_executable(${PROJECT_NAME} ${INCLUDE_FILES} ${SOURCE_FILES})

# Linking libraries
target_link_libraries(${PROJECT_NAME} -pthread
                                      -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
                                      -lboost_regex -lboost_filesystem -lboost_system)

# For C++11 functionnalities
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
