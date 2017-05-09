#pragma once

#include "Engine/GameWindow.hpp"

class Game {
public:
    void Run();

private:
    GameWindow Window;

    virtual void Initialize() = 0;
    virtual void LoadContent() = 0;
    virtual void Update(float elapsed) = 0;
    virtual void Draw(float elapsed) = 0;
    virtual void UnloadContent() = 0;
    virtual void Dispose() = 0;
};
