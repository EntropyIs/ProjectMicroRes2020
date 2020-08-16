#include "StateVictory.h"

#include <Entropy/Math/Vec2.h>
#include <Entropy/Graphics/JoystickController.h>

using namespace Entropy;

bool StateVictory::init()
{
    key_down = true;
    execute_selection = false;
    return true;
}

void StateVictory::input(Entropy::Graphics::Window& window)
{
    Graphics::JoystickController joystickController;
    int axisCount;
    int buttonCount;
    const float* axisData = joystickController.getAxisData(GLFW_JOYSTICK_1, &axisCount);
    const unsigned char* buttonData = joystickController.getButtonsData(GLFW_JOYSTICK_1, &buttonCount);

    if (axisCount >= 2 && buttonCount >= 10)
    {
        if ((window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down) || (buttonData[2] == GLFW_PRESS && !key_down))
        {
            ResourceManager::playAudio("sfx_menu_select");
            execute_selection = true;
        }
        else if (!window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && buttonData[2] == GLFW_RELEASE && key_down)
            key_down = false;
    }
    else
    {
        if (window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down)
        {
            ResourceManager::playAudio("sfx_menu_select");
            execute_selection = true;
        }
        else if (!window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && key_down)
            key_down = false;
    }
}

void StateVictory::render()
{
    Math::Vec2 textPos[] =
    {
        Math::Vec2(17.5, 37.5), //Y
        Math::Vec2(22.5, 37.5), //o
        Math::Vec2(27.5, 37.5), //u

        Math::Vec2(37.5, 37.5), //W
        Math::Vec2(42.5, 37.5), //i
        Math::Vec2(47.5, 37.5), //n

        Math::Vec2(24.5, 9.5), //M
        Math::Vec2(29.5, 9.5), //e
        Math::Vec2(34.5, 9.5), //n
        Math::Vec2(39.5, 9.5), //u
    };

    Math::Vec2 textChar[] =
    {
        Math::Vec2(9,  3), // Y
        Math::Vec2(15, 4), // o
        Math::Vec2(5,  5), // u

        Math::Vec2(7,  3), // W
        Math::Vec2(9,  4), // i
        Math::Vec2(14, 4), // n

        Math::Vec2(13, 2), // M
        Math::Vec2(5,  4), // e
        Math::Vec2(14, 4), // n
        Math::Vec2(5,  5), // u
    };

    for (unsigned int i = 0; i < 8; i++)
        renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    for (unsigned int i = 8; i < 12; i++)
        renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
}

Entropy::GameState* StateVictory::update(GameState* gameState)
{
    if (execute_selection)
    {
        connectedStates[0]->init();
        return connectedStates[0];
    }
    return gameState;
}
