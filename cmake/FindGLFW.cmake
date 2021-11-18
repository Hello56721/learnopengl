include("FindPackageHandleStandardArgs")

# Find the include directory
find_path(
    GLFW_INCLUDE_DIR
    NAMES "GLFW/glfw3.h"
    PATHS "${CMAKE_SOURCE_DIR}/deps/glfw/include"
    DOC "Absolute path to GLFW's include directory"
)

# Find the library file
if (MSVC)
    find_file(
        GLFW_LIBRARY
        NAMES "glfw3.lib" "glfw3dll.lib"
        PATHS "${CMAKE_SOURCE_DIR}/deps/glfw/build/src/Debug"
              "${CMAKE_SOURCE_DIR}/deps/glfw/build/Debug/src"
              "${CMAKE_SOURCE_DIR}/deps/glfw/build/src/Release"
              "${CMAKE_SOURCE_DIR}/deps/glfw/build/Release/src"
        DOC "Absolute path to GLFW's library (usually libglfw3.a, glfw3.lib, or libglfw.so)"
    )
else()
    if (WIN32)
        find_file(
            GLFW_LIBRARY
            NAMES "libglfw3.a" "libglfw3dll.a"
            PATHS "${CMAKE_SOURCE_DIR}/deps/glfw/build/src"
            DOC "Absolute path to GLFW's library (usually libglfw3.a, glfw3.lib, or libglfw.so)"
        )
    else()
        find_file(
            GLFW_LIBRARY
            NAMES "libglfw3.a" "libglfw.so.3"
            PATHS "${CMAKE_SOURCE_DIR}/deps/glfw/build/src"
                  "/usr/lib/x86_64-linux-gnu"
            DOC "Absolute path to GLFW's library (usually libglfw3.a, glfw3.lib, or libglfw.so)"
        )
    endif()
endif()

# Set the package as found
find_package_handle_standard_args("GLFW" DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_DIR)