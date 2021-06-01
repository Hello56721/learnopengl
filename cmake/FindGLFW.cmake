include("FindPackageHandleStandardArgs")

# Find the include directory
find_path(
    GLFW_INCLUDE_DIR
    NAMES "GLFW/glfw3.h"
    PATHS "${CMAKE_SOURCE_DIR}/deps/glfw/include"
    DOC "Absolute path to GLFW's include directory"
)

# Find the source file
find_file(
    GLFW_LIBRARY
    NAMES "libglfw3.a" "libglfw3dll.a" "libglfw.so" "glfw3.lib"
    PATHS "${CMAKE_SOURCE_DIR}/deps/glfw/lib"
    DOC "Absolute path to GLFW's library (usually libglfw3.a, glfw3.lib, or libglfw.so)"
)

# Set the package as found
find_package_handle_standard_args("GLFW" DEFAULT_MSG GLFW_LIBRARY GLFW_INCLUDE_DIR)