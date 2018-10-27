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

set(PROJECT_SRC_DIR "${PROJECT_SOURCE_DIR}/source")
set(PROJECT_RES_DIR "${PROJECT_SOURCE_DIR}/resources")
set(PROJECT_RES_DIR_BUILD "${CMAKE_CURRENT_BINARY_DIR}/resources")

add_subdirectory("source")
add_subdirectory("dependences")

file(GLOB_RECURSE PROJECT_RES "${PROJECT_RES_DIR}/*")

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SRC})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_RES})

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)

target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SRC_DIR})

source_group(TREE "${PROJECT_SRC_DIR}" PREFIX "Source" FILES ${PROJECT_SRC})
source_group(TREE "${PROJECT_RES_DIR}" PREFIX "Resources" FILES ${PROJECT_RES})

set_source_files_properties(${PROJECT_RES} PROPERTIES HEADER_FILE_ONLY ON)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink ${PROJECT_RES_DIR} ${PROJECT_RES_DIR_BUILD} 
    DEPENDS ${PROJECT_RES_DIR_BUILD}
    COMMENT "symbolic link created ${PROJECT_RES_DIR} => ${PROJECT_RES_DIR_BUILD}"
)

file(GLOB_RECURSE 
    _FORMAT_PROJECT_RES_SHADERS 
    "${PROJECT_RES_DIR}/*.vs"
    "${PROJECT_RES_DIR}/*.fs"
)

ClangFormatTarget(ON ${_FORMAT_PROJECT_SRC} ${_FORMAT_PROJECT_RES_SHADERS})

set(PROJECT_OTHER_FILES
    ".clang-format"
    ".editorconfig"
    ".gitignore"
    ".gitmodules"
    "License.md"
)

source_group("Other" FILES ${PROJECT_OTHER_FILES})
target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_OTHER_FILES})
set_source_files_properties(${PROJECT_OTHER_FILES} PROPERTIES HEADER_FILE_ONLY ON)
