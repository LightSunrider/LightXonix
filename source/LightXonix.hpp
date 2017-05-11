#include "Engine/Game.hpp"
#include <GLFW/glfw3.h>

class LightXonix : public Game {
    void Initialize() override {}

    void LoadContent() override {}

    void Update(float elapsed) override {}

    void Draw(float elapsed) override {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void UnloadContent() override {}

    void Dispose() override {}
};
