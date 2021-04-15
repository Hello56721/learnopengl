find_path(
    STB_INCLUDE_DIR
    NAMES "stb_image.h"
    PATHS "${CMAKE_SOURCE_DIR}/deps/stb"
    DOC "Absolute path to STB's include directory"
)

include("FindPackageHandleStandardArgs")
find_package_handle_standard_args(STB DEFAULT_MSG STB_INCLUDE_DIR)