cmake_minimum_required(VERSION 3.8)

set(DEPENDENCES_PATH "${PROJECT_SOURCE_DIR}/dependences")

# GLFW
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")
set(GLFW_INSTALL OFF CACHE INTERNAL "")

add_subdirectory("${DEPENDENCES_PATH}/glfw")

set_target_properties(glfw PROPERTIES FOLDER "Dependences")
# ----------

# glad
add_subdirectory("${DEPENDENCES_PATH}/glad")

set_target_properties(glad PROPERTIES FOLDER "Dependences")
# ----------

# glm
add_subdirectory("${DEPENDENCES_PATH}/glm")

set_target_properties(glm_dummy PROPERTIES FOLDER "Dependences")
# ----------
