cmake_minimum_required(VERSION 3.16)

project("LearnOpenGL")

# Use the latest version of C and C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Tell CMake where to find the scripts to find the depedencies
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Turn on high warning level
if (MSVC)
    add_compile_options("/W4")
    add_link_options("/W4")
else()
    add_compile_options("-Wall" "-pedantic")
    add_link_options("-Wall" "-pedantic")
endif()

# Find GLAD and put it into it's own library
find_package("GLAD")
add_library("glad" "${GLAD_SOURCE_FILE}")

find_package("GLFW")

add_executable("learn-opengl")

add_subdirectory("src")