include("FindPackageHandleStandardArgs")

# Find the include directory
find_path(
    GLAD_INCLUDE_DIR
    NAMES "glad/glad.h"
    PATHS "${CMAKE_SOURCE_DIR}/deps/glad/include"
    DOC "Absolute path to GLAD's include directory"
)

# Find the source file
find_file(
    GLAD_SOURCE_FILE
    NAMES "glad.c"
    PATHS "${CMAKE_SOURCE_DIR}/deps/glad/src"
    DOC "Absolute path to GLAD's source file (usually glad.c)"
)

# Set the package as found
find_package_handle_standard_args("GLAD" DEFAULT_MSG GLAD_SOURCE_FILE GLAD_INCLUDE_DIR)