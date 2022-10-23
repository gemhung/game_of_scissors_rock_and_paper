cmake_minimum_required(VERSION 3.24)

project(game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(GAME_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(GAME_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)

include_directories(${GAME_INSTALL_INCLUDE_DIR})
set(SOURCE_FILES ./src/main.cpp)

add_executable(game ${SOURCE_FILES})
install(TARGETS game DESTINATION ${GAME_INSTALL_BIN_DIR})

add_subdirectory(test)


