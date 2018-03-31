cmake_minimum_required(VERSION 3.8)

set(DEPENDENCES_PATH "${PROJECT_SOURCE_DIR}/dependences")

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

add_subdirectory("${DEPENDENCES_PATH}/glfw")
# ----------

# glad
set(GLAD_PROFILE "core" CACHE INTERNAL "")
set(GLAD_API "gl=3.3" CACHE INTERNAL "")
set(GLAD_NO_LOADER ON CACHE INTERNAL "")
set(GLAD_EXTENSIONS
    "GL_EXT_texture_compression_s3tc"
CACHE INTERNAL "")

add_subdirectory("${DEPENDENCES_PATH}/glad")

set(GLAD_INCLUDE_DIRS ${GLAD_INCLUDE_DIRS} PARENT_SCOPE)
# ----------

# glm
add_subdirectory("${DEPENDENCES_PATH}/glm")
# ----------
