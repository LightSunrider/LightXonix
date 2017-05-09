cmake_minimum_required(VERSION 3.7)

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
set(Index_SOURCE_CODE
    "source/Main.cpp"
    "source/LightXonix.hpp"
    )
source_group("Game" FILES ${Index_SOURCE_CODE})

set(Engine_SOURCE_CODE
    "source/Engine/Game.cpp"
    "source/Engine/Game.hpp"

    "source/Engine/GameWindow.cpp"
    "source/Engine/GameWindow.hpp"
    )
source_group("Engine" FILES ${Engine_SOURCE_CODE})

set(SOURCE_CODE ${Index_SOURCE_CODE} ${Engine_SOURCE_CODE})
# Resource files
set(Shaders_RESOURCES
    "resources/Shaders/simple.vert"
    "resources/Shaders/simple.frag"
    )

source_group("Resources\\Shaders" FILES ${Shaders_RESOURCES})

set(PROJECT_RESOURCES ${Shaders_RESOURCES})

add_executable(${EXECUTABLE_NAME} ${SOURCE_CODE} ${PROJECT_RESOURCES})
# ------------

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})

# GLFW
find_package(glfw3 3.2 REQUIRED)
target_link_libraries(${EXECUTABLE_NAME} glfw)

# OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${OPENGL_LIBRARIES})

# GLEW
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIR})
target_link_libraries(${EXECUTABLE_NAME} ${GLEW_LIBRARY})
add_definitions("-DGLEW_STATIC")

# glm
find_package(glm REQUIRED)
include_directories(${glm_INCLUDE_DIRS})


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION "${PROJECT_SOURCE_DIR}/binary")

# Clang-format target
file(GLOB_RECURSE
    ALL_CXX_SOURCE_FILES
    *.[chi]pp *.[chi]xx *.cc *.hh *.ii *.[CHI]
    )

# Adding Clang_Format target if executable is found
find_program(CLANG_FORMAT "clang-format")
if (CLANG_FORMAT)
    add_custom_target(
        Clang_Format
        COMMAND clang-format -i -style=file ${ALL_CXX_SOURCE_FILES}
    )
endif ()
set_property(TARGET Clang_Format PROPERTY FOLDER "CMake")
