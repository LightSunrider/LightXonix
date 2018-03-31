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
    ${PROJECT_RES_MODELS}
    ${PROJECT_RES_SHADERS}
    ${PROJECT_RES_TEXTURES}
    "CMakeLists.txt"
)

source_group(TREE "${PROJECT_SOURCE_DIR}/resources" PREFIX "resources" FILES ${PROJECT_RES})

target_sources(${PROJECT_NAME} PRIVATE ${PROJECT_RES})

set(PROJECT_RES ${PROJECT_RES} PARENT_SCOPE)
