cmake_minimum_required(VERSION 3.8)

#Source files
set(PROJECT_SRC
    "source/CMakeLists.txt"

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

    "source/Engine/Camera.hpp"

    "source/Engine/InputSystem.cpp"
    "source/Engine/InputSystem.hpp"
    "source/Engine/KeyMap.hpp"

    "source/Engine/GameObject.hpp"

    "source/Engine/Mesh.cpp"
    "source/Engine/Mesh.hpp"
)
#----------

set(PROJECT_SRC ${PROJECT_SRC} PARENT_SCOPE)

set(_FORMAT_PROJECT_SRC ${PROJECT_SRC})
list(REMOVE_ITEM _FORMAT_PROJECT_SRC "source/CMakeLists.txt")
set(_FORMAT_PROJECT_SRC ${_FORMAT_PROJECT_SRC} PARENT_SCOPE)
