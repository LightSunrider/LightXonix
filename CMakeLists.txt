cmake_minimum_required(VERSION 3.8)

include("cmake/ClangFormat.cmake")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

project(LightXonix)

add_executable(${PROJECT_NAME} "")

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

add_subdirectory("source")
add_subdirectory("resources")
add_subdirectory("dependences")

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SRC})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_RES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)

target_include_directories(${PROJECT_NAME} PRIVATE "source/")
target_include_directories(${PROJECT_NAME} PRIVATE ${GLAD_INCLUDE_DIRS})

source_group(TREE "${PROJECT_SOURCE_DIR}/source" PREFIX "Source" FILES ${PROJECT_SRC})
source_group(TREE "${PROJECT_SOURCE_DIR}/resources" PREFIX "Resources" FILES ${PROJECT_RES})

set_source_files_properties(${PROJECT_RES} PROPERTIES HEADER_FILE_ONLY ON)

ClangFormatTarget(ON ${_FORMAT_PROJECT_SRC} ${_FORMAT_PROJECT_RES_SHADERS})

# Other Files
set(PROJECT_OTHER_FILES
    ".clang-format"
    ".editorconfig"
    ".gitignore"
    ".gitmodules"
    "License.md"
)
# ------------

source_group("Other" FILES ${PROJECT_OTHER_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_OTHER_FILES})
set_source_files_properties(${PROJECT_OTHER_FILES} PROPERTIES HEADER_FILE_ONLY ON)
