cmake_minimum_required( VERSION 3.15 )

project(FactoryMethod LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message( STATUS "CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME}" )
message( STATUS "PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}" )

include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
add_subdirectory(framework)
add_subdirectory(idcard)

add_executable( FactoryMethod main.cpp )
target_link_libraries( FactoryMethod idcard framework )

