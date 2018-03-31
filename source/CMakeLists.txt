cmake_minimum_required(VERSION 3.8)

# Source files
set(PROJECT_SRC
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
# ----------

source_group(TREE "${PROJECT_SOURCE_DIR}/source" PREFIX "source" FILES ${PROJECT_SRC})

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_SRC})
