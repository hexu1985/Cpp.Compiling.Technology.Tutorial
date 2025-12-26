# set minimum cmake version                                                                                                                                            
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(plugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# build plugins
add_subdirectory(dictionaries)

# build client 
set(SRC_LIST client.cpp dictionary_manager.cpp)

add_executable(client ${SRC_LIST})
target_link_libraries(client dl)
