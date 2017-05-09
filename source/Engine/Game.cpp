#include "Engine/Game.hpp"

void Game::Run() {
    Initialize();
    LoadContent();
    while (!Window.ShouldClose) {
        Update(0.0f);
        Draw(0.0f);
    }
    UnloadContent();
    Dispose();
}
