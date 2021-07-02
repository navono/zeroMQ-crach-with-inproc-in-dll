cmake_minimum_required(VERSION 3.15)
project(cppDemo)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-DDYNALO_IMPORT_SYMBOLS)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(demo main.cpp)

target_include_directories(demo PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(demo ${CONAN_LIBS})

if (MSVC)
    # disable warning as error
    target_compile_options(demo PRIVATE "/WX-" )
    add_definitions(-DNOMINMAX)
else()
    # lots of warnings and all warnings as errors
    target_compile_options(demo PRIVATE "-Wall -Wextra -pedantic -Werror")
endif()

add_subdirectory(foo)