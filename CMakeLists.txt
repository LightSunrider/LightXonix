cmake_minimum_required(VERSION 3.8)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")
add_definitions("-std=c++14")

project(LightXonix)

set(EXECUTABLE_NAME "LightXonix")
include_directories("${PROJECT_SOURCE_DIR}/source/")

# Source files
set(SOURCE_CODE 
    "source/Main.cpp"

    "source/Engine/Engine.hpp"

    "source/Engine/Types.hpp"

    "source/Engine/Window.cpp"
    "source/Engine/Window.hpp"

    "source/Engine/Shader.cpp"
    "source/Engine/Shader.hpp"

    "source/Engine/Exception.hpp"

    "source/Engine/Texture.cpp"
    "source/Engine/Texture.hpp"

    "source/Engine/Camera.cpp"
    "source/Engine/Camera.hpp"
    
    "source/Engine/InputSystem.cpp"
    "source/Engine/InputSystem.hpp"
    "source/Engine/KeyMap.hpp"

    "source/Engine/GameObject.hpp"
)
source_group(TREE "${PROJECT_SOURCE_DIR}/source" PREFIX "source" FILES ${SOURCE_CODE})
# ------------

# Resource files
#  Shaders
set(PROJECT_RESOURCES_SHADERS
    "resources/Shaders/simple.vert"
    "resources/Shaders/simple.frag"
)
#  Textures
set(PROJECT_RESOURCES_TEXTURES
    "resources/Textures/simple.dds"
)

set(PROJECT_RESOURCES
    ${PROJECT_RESOURCES_SHADERS}
    ${PROJECT_RESOURCES_TEXTURES}
)
source_group(TREE "${PROJECT_SOURCE_DIR}/resources" PREFIX "resources" FILES ${PROJECT_RESOURCES})
# ------------

# Other files
set(OTHER_PROJECT_FILES
    ".clang-format"
    ".clang-format-ignore"
    ".editorconfig"
    ".gitignore"
    "License.md"
)
source_group("other" FILES ${OTHER_PROJECT_FILES})
# ------------

add_executable(${EXECUTABLE_NAME} ${SOURCE_CODE} ${PROJECT_RESOURCES} ${OTHER_PROJECT_FILES})
set_target_properties(${EXECUTABLE_NAME} PROPERTIES 
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/resources/"
    VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/resources/"
)
# ------------

# GLFW
find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} glfw)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})

# gl3w
find_package(gl3w REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} gl3w)

# glm
find_package(glm REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} glm)


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION "${PROJECT_SOURCE_DIR}/binary")

# Clang_Format target
option(CLANG_FORMAT_TARGET "Initialize Clang_Format target" OFF)
if(${CLANG_FORMAT_TARGET})
    find_program(CLANG_FORMAT_EXE "clang-format")
    if (CLANG_FORMAT_EXE)
        set(CLANG_FORMAT_FILES ${SOURCE_CODE} ${PROJECT_RESOURCES_SHADERS})
        file(STRINGS ".clang-format-ignore" CLANG_FORMAT_IGNORE)
        foreach(i ${CLANG_FORMAT_IGNORE})
            list(REMOVE_ITEM CLANG_FORMAT_FILES ${i})
        endforeach()

        add_custom_target(
            "CLANG_FORMAT" 
            COMMAND "clang-format" -i -style=file ${CLANG_FORMAT_FILES}
            WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
        )
        set_property(TARGET "CLANG_FORMAT" PROPERTY FOLDER "CMake")
    endif()
endif()
