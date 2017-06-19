cmake_minimum_required(VERSION 3.8)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif ()

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

    "source/Engine/GameWindow.cpp"
    "source/Engine/GameWindow.hpp"

    "source/Engine/Shader.cpp"
    "source/Engine/Shader.hpp"

    "source/Engine/Exception.hpp"
)
source_group(TREE "${PROJECT_SOURCE_DIR}/source" PREFIX "source" FILES ${SOURCE_CODE})

# Resource files
set(PROJECT_RESOURCES
    #Shaders
    "resources/Shaders/simple.vert"
    "resources/Shaders/simple.frag"
)
source_group(TREE "${PROJECT_SOURCE_DIR}/resources" PREFIX "resources" FILES ${PROJECT_RESOURCES})

add_executable(${EXECUTABLE_NAME} ${SOURCE_CODE} ${PROJECT_RESOURCES})
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

# GLEW
find_package(GLEW REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} GLEW::glew_s)

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
        file(GLOB_RECURSE ALL_CXX_SOURCE_FILES *.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI] *.frag *.vert)
        add_custom_target("CLANG_FORMAT" COMMAND "clang-format" -i -style=file ${ALL_CXX_SOURCE_FILES})
        set_property(TARGET "CLANG_FORMAT" PROPERTY FOLDER "CMake")
    endif ()
endif()
