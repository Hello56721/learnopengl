include("FindPackageHandleStandardArgs")

find_path(
    GLM_INCLUDE_DIR
    NAMES "glm/glm.hpp"
    PATHS "${CMAKE_SOURCE_DIR}/deps/glm"
    DOC "Absolute directory to GLM's include directory"
)

find_package_handle_standard_args(GLM DEFAULT_MSG GLM_INCLUDE_DIR)