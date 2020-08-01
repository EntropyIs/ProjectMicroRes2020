#include "StatePause.h"

using namespace Entropy;

bool StatePause::init()
{
    return false;
}

void StatePause::input(Graphics::Window& window)
{
}

void StatePause::render()
{
}

GameState* StatePause::update(GameState* gameState)
{
    return gameState;
}
