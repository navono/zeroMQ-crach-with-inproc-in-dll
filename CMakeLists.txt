cmake_minimum_required(VERSION 3.15)
project(cppDemo)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DDYNALO_IMPORT_SYMBOLS)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(demo main.cpp)

target_link_libraries(demo ${CONAN_LIBS})

add_subdirectory(foo)