#include "StateMenu.h"

using namespace Entropy;

bool StateMenu::init()
{
    return true;
}

void StateMenu::input(Graphics::Window& window)
{
    // Close window on KEY_ESCAPE been pressed
    if (window.getKeyPressed(Graphics::GLKeys::KEY_ESCAPE))
        window.setShouldClose(true);
}

void StateMenu::render()
{
}

Entropy::GameState* StateMenu::update(GameState* gameState)
{
    return this;
}
