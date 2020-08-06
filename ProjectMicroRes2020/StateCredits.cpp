#include "StateCredits.h"

#include <Entropy/Math/Vec2.h>
#include <Entropy/Graphics/JoystickController.h>

using namespace Entropy;

bool StateCredits::init()
{
    key_down = true;
    execute_selection = false;
    return true;
}

void StateCredits::input(Graphics::Window& window)
{
    Graphics::JoystickController joystickController;
    int axisCount;
    int buttonCount;
    const float* axisData = joystickController.getAxisData(GLFW_JOYSTICK_1, &axisCount);
    const unsigned char* buttonData = joystickController.getButtonsData(GLFW_JOYSTICK_1, &buttonCount);

    if (axisCount >= 2 && buttonCount >= 10)
    {
        if ((window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down) || (buttonData[2] == GLFW_PRESS && !key_down))
            execute_selection = true;
        else if (!window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && buttonData[2] == GLFW_RELEASE && key_down)
            key_down = false;
    }
    else
    {
        if (window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down)
            execute_selection = true;
        else if (!window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && key_down)
            key_down = false;
    }
}

void StateCredits::render()
{
    Entropy::Math::Vec2 textPos[] =
    {
        Math::Vec2(17.5, 57.5), //C
        Math::Vec2(22.5, 57.5), //r
        Math::Vec2(27.5, 57.5), //e
        Math::Vec2(32.5, 57.5), //d
        Math::Vec2(37.5, 57.5), //i
        Math::Vec2(42.5, 57.5), //t
        Math::Vec2(47.5, 57.5), //s

        Math::Vec2(17.5, 45.5), //A
        Math::Vec2(22.5, 45.5), //n
        Math::Vec2(27.5, 45.5), //o
        Math::Vec2(32.5, 45.5), //n
        Math::Vec2(37.5, 45.5), //y
        Math::Vec2(42.5, 45.5), //9
        Math::Vec2(47.5, 45.5), //1

        Math::Vec2(7.5,  37.5), //J
        Math::Vec2(12.5, 37.5), //.
        Math::Vec2(17.5, 37.5), //P
        Math::Vec2(22.5, 37.5), //.
        Math::Vec2(27.5, 37.5), //G
        Math::Vec2(32.5, 37.5), //a
        Math::Vec2(37.5, 37.5), //l
        Math::Vec2(42.5, 37.5), //o
        Math::Vec2(47.5, 37.5), //v
        Math::Vec2(52.5, 37.5), //i
        Math::Vec2(57.5, 37.5), //c

        Math::Vec2(19.5, 29.5), //X
        Math::Vec2(24.5, 29.5), //a
        Math::Vec2(29.5, 29.5), //n
        Math::Vec2(34.5, 29.5), //d
        Math::Vec2(39.5, 29.5), //e
        Math::Vec2(44.5, 29.5), //r

        Math::Vec2(24.5, 9.5), //B
        Math::Vec2(29.5, 9.5), //a
        Math::Vec2(34.5, 9.5), //c
        Math::Vec2(39.5, 9.5), //k
    };

    Entropy::Math::Vec2 textChar[] =
    {
        Math::Vec2(3, 2), //C
        Math::Vec2(2, 5), //r
        Math::Vec2(5, 4), //e
        Math::Vec2(4, 4), //d
        Math::Vec2(9, 4), //i
        Math::Vec2(4, 5), //t
        Math::Vec2(3, 5), //s

        Math::Vec2(1,  2), // A
        Math::Vec2(14, 4), // n
        Math::Vec2(15, 4), // o
        Math::Vec2(14, 4), // n
        Math::Vec2(9,  5), // y
        Math::Vec2(9,  1), // 9
        Math::Vec2(1,  1), // 1

        Math::Vec2(10, 2), // J
        Math::Vec2(14, 0), // .
        Math::Vec2(0,  3), // P
        Math::Vec2(14, 0), // .
        Math::Vec2(7,  2), // G
        Math::Vec2(1,  4), // a
        Math::Vec2(12, 4), // l
        Math::Vec2(15, 4), // o
        Math::Vec2(6,  5), // v
        Math::Vec2(9,  4), // i
        Math::Vec2(3,  4), // c

        Math::Vec2(8,  3), // X
        Math::Vec2(1,  4), // a
        Math::Vec2(14, 4), // n
        Math::Vec2(4,  4), // d
        Math::Vec2(5,  4), // e
        Math::Vec2(2,  5), // r

        Math::Vec2(2,  2), // B
        Math::Vec2(1,  4), // a
        Math::Vec2(3,  4), // c
        Math::Vec2(11, 4), // k
    };

    for (unsigned int i = 0; i < 31; i++)
        renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    for (unsigned int i = 31; i < 35; i++)
        renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
}

GameState* StateCredits::update(GameState* gameState)
{
    if (execute_selection)
    {
        connectedStates[0]->init();
        return connectedStates[0];
    }
    return gameState;
}
