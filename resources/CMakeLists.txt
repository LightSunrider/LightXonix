cmake_minimum_required(VERSION 3.8)

# Models
set(PROJECT_RES_MODELS
    "resources/Models/cube.obj"
    "resources/Models/skybox.obj"
)
# ----------

# Shaders
set(PROJECT_RES_SHADERS
    "resources/Shaders/PhongShader.vs"
    "resources/Shaders/PhongShader.fs"

    "resources/Shaders/SkyboxShader.vs"
    "resources/Shaders/SkyboxShader.fs"

    "resources/Shaders/Light/PointLight.glsl"
    "resources/Shaders/Material/PhongMaterial.glsl"
)
# ----------

# Textures
set(PROJECT_RES_TEXTURES
    "resources/Textures/simple.dds"
    "resources/Textures/skybox.dds"
)
# ----------

set(PROJECT_RES
    "resources/CMakeLists.txt"
    ${PROJECT_RES_MODELS}
    ${PROJECT_RES_SHADERS}
    ${PROJECT_RES_TEXTURES}
)

set(PROJECT_RES ${PROJECT_RES} PARENT_SCOPE)

set(PROJECT_RES_SHADERS ${_FORMAT_PROJECT_RES_SHADERS} PARENT_SCOPE)
