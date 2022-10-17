cmake_minimum_required(VERSION 3.24)

project(my_cpp_template)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})

set(DIVISIBLE_INSTALL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(DIVISIBLE_INSTALL_BIN_DIR ${PROJECT_SOURCE_DIR}/bin)
#set(DIVISIBLE_INSTALL_LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

#set(DIVISION_HEADERS_DIR ${PROJECT_SOURCE_DIR}/src/division)

include_directories(${DIVISIBLE_INSTALL_INCLUDE_DIR})
#include_directories(${DIVISION_HEADERS_DIR})
set(SOURCE_FILES ./src/main.cpp)

add_executable(my_cpp_template ${SOURCE_FILES})
install(TARGETS my_cpp_template DESTINATION ${DIVISIBLE_INSTALL_BIN_DIR})

#add_subdirectory(src)
#add_subdirectory(test)


