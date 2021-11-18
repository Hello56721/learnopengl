cmake_minimum_required(VERSION 3.16)

project("LearnOpenGL")

# Notify the user that building on Apple based devices are currently not supported
if (APPLE)
    message(WARNING "Building on Apple based devices are currently not fully supported. You may experience problems")
endif()

# Use the latest version of C and C++
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)

# Set the output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
endif()
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

# Add the .out extension to linux executables
if (UNIX AND NOT APPLE)
    set(CMAKE_EXECUTABLE_SUFFIX .out)
endif()

if (UNIX AND NOT APPLE)
    add_compile_definitions(LEARNOPENGL_SYSTEM_LINUX)
elseif(WIN32)
    add_compile_definitions(LEARNOPENGL_SYSTEM_WINDOWS)
elseif(APPLE)
    add_compile_definitions(LEARNOPENGL_SYSTEM_APPLE)
endif()

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

# Find the libraries
find_package("GLFW")

# Add the include directories
include_directories(
    "deps/GLAD/include"
    "${GLFW_INCLUDE_DIR}"
    "deps/glm"
    "deps/stb"
)

# Place GLAD into it's own library
add_library("glad" "deps/GLAD/src/glad.c")

# Add the executable
add_executable("learnopengl")

add_subdirectory("src")

# Link the system specific libraries
if(UNIX AND NOT APPLE)
    target_link_libraries("learnopengl" "glad" "${GLFW_LIBRARY}" "GL" "X11" "pthread" "Xrandr" "dl")
elseif(WIN32)
    target_link_libraries("learnopengl" "glad" "${GLFW_LIBRARY}" "gdi32" "opengl32")
elseif(APPLE)
    target_link_libraries("learnopengl" "glad" "${GLFW_LIBRARY}")
endif()