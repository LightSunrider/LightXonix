#include "Engine/Engine.hpp"

#include <GLFW/glfw3.h>

using namespace le;
using namespace glm;

signed main() {
    Window window(800, 600, "LightXonix");
    Camera camera;

    Shader::PreprocSettings preprocSettings;
    preprocSettings.Definitions.insert(std::make_pair("POINT_LIGHTS", "1"));
    preprocSettings.IncludePath = "Shaders/";

    Shader phongShader = Shader("Shaders/PhongShader.vs", "Shaders/PhongShader.fs", preprocSettings);
    Shader skyboxShader = Shader("Shaders/SkyboxShader.vs", "Shaders/SkyboxShader.fs", preprocSettings);

    Texture simpleTexture("Textures/simple.dds");
    Texture skyboxTexture("Textures/skybox.dds");
    Texture emptyTexture;

    PhongMaterial phongMaterial(phongShader, simpleTexture, emptyTexture, 64.0f);
    SkyboxMaterial skyboxMaterial(skyboxShader, skyboxTexture);

    PointLight pointLights[1];
    pointLights[0] = PointLight();

    Mesh cubeMesh("Models/cube.obj");
    Mesh skyboxMesh("Models/skybox.obj");

    Model cubeModel(cubeMesh, &phongMaterial);
    Model skyboxModel(skyboxMesh, &skyboxMaterial);

    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    vec2 lastPos = window.Input.GetCursorPosition();
    auto ProcessInput = [&]() {
        if (window.Input.IsKeyPressed(Key::ESCAPE)) {
            window.Close();
            return;
        }

        if (window.Input.IsKeyPressed(Key::W)) {
            camera.transform.position += camera.transform.Forward() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::S)) {
            camera.transform.position -= camera.transform.Forward() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::A)) {
            camera.transform.position += camera.transform.Right() * deltaTime * 10.0f;
        }
        if (window.Input.IsKeyPressed(Key::D)) {
            camera.transform.position -= camera.transform.Right() * deltaTime * 10.0f;
        }

        vec2 cursorPos = window.Input.GetCursorPosition() - lastPos;
        lastPos = window.Input.GetCursorPosition();

        float pitch = cursorPos.y * deltaTime * 10.0f;
        float yaw = cursorPos.x * deltaTime * 10.0f;

        quat quatPitch = angleAxis(radians(pitch), vec3(1, 0, 0));
        quat quatYaw = angleAxis(radians(yaw), vec3(0, 1, 0));

        camera.transform.rotation = normalize(quatPitch * camera.transform.rotation * quatYaw);
    };

    GameObject cubeObjects[] = {
        GameObject(Transform(vec3(0.0f, 0.0f, -2.0f))),   GameObject(Transform(vec3(2.0f, 5.0f, -15.0f))),
        GameObject(Transform(vec3(-1.5f, -2.2f, -2.5f))), GameObject(Transform(vec3(-3.8f, -2.0f, -12.3f))),
        GameObject(Transform(vec3(2.4f, -0.4f, -3.5f))),  GameObject(Transform(vec3(-1.7f, 3.0f, -7.5f))),
        GameObject(Transform(vec3(1.3f, -2.0f, -2.5f))),  GameObject(Transform(vec3(1.5f, 2.0f, -2.5f))),
        GameObject(Transform(vec3(1.5f, 0.2f, -1.5f))),   GameObject(Transform(vec3(-1.3f, 1.0f, -1.5f)))
    };

    GameObject skyboxObject;
    skyboxObject.transform.scale = vec3(500.0f);

    glEnable(GL_DEPTH_TEST);

    window.MakeContextCurrent();
    while (!window.ShouldClose()) {
        float currentFrame = (float) glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        window.PollEvents();
        ProcessInput();

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.Update(deltaTime);

        phongShader.Use();

        pointLights[0].Use(0, phongShader);
        phongMaterial.Use();

        for (uint i = 0; i < 10; i++) {
            cubeModel.Draw(&cubeObjects[i], &camera);
        }

        skyboxObject.transform.position = camera.transform.position;
        skyboxModel.Draw(&skyboxObject, &camera);

        window.SwapBuffers();
        lastFrame = currentFrame;
    }
    window.Close();

    return 0;
}
