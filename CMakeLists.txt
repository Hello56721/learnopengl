cmake_minimum_required(VERSION 3.16)

project("LearnOpenGL")

# Notify the user that building on Apple based devices are currently not supported
if (APPLE)
    message(WARNING "Building on Apple based devices are currently not fully supported. You may experience problems")
endif()

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

# Find the libraries
find_package("GLAD")
find_package("GLFW")
find_package("GLM")
find_package("STB")

# Add the include directories
include_directories("${GLAD_INCLUDE_DIR}" "${GLFW_INCLUDE_DIR}" "${GLM_INCLUDE_DIR}" "${STB_INCLUDE_DIR}" "include")

# Place GLAD into it's own library
add_library("glad" "${GLAD_SOURCE_FILE}")

# Add the executable
add_executable("learn-opengl")

add_subdirectory("src")
add_subdirectory("include")

# Link the system specific libraries
if(UNIX AND NOT APPLE)
    target_link_libraries("learn-opengl" "glad" "${GLFW_LIBRARY}" "GL" "X11" "pthread" "Xrandr" "dl")
elseif(WIN32)
    target_link_libraries("learn-opengl" "glad" "${GLFW_LIBRARY}" "gdi32" "opengl32")
elseif(APPLE)
    target_link_libraries("learn-opengl" "glad" "${GLFW_LIBRARY}")
endif()