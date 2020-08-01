#include "StateGame.h"

using namespace Entropy;

StateGame::StateGame() : GameState("Game", 2)
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
}

bool StateGame::init()
{
    return false;
}

void StateGame::input(Graphics::Window& window)
{
}

void StateGame::render()
{
}

GameState* StateGame::update(GameState* gameState)
{
    return gameState;
}
