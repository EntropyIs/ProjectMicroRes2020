#include "StateMenu.h"

#include <Entropy/Graphics/JoystickController.h>

using namespace Entropy;

bool StateMenu::init()
{
    selection = 0;
    key_down = true;
    execute_selection = false;
    return true;
}

void StateMenu::input(Graphics::Window& window)
{
    // Close window on KEY_ESCAPE been pressed or !gameFlag
    if (window.getKeyPressed(Graphics::GLKeys::KEY_ESCAPE) || !gameFlag)
        window.setShouldClose(true);

    Graphics::JoystickController joystickController;
    int axisCount;
    int buttonCount;
    const float* axisData = joystickController.getAxisData(GLFW_JOYSTICK_1, &axisCount);
    const unsigned char* buttonData = joystickController.getButtonsData(GLFW_JOYSTICK_1, &buttonCount);

    if (axisCount >= 2 && buttonCount >= 10)
    {
        float threshold = 0.8f; // axis deadzone threshold

        if ((window.getKeyPressed(Graphics::GLKeys::KEY_DOWN) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_S) && !key_down) ||
            (axisData[1] > (0.0f + threshold) && !key_down)
            )
        {
            ResourceManager::playAudio("sfx_menu_move");
            key_down = true;
            selection++;
            if (selection > 2)
                selection = 0;
        }
        else if ((window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_W) && !key_down) ||
            (axisData[1] < (0.0f - threshold) && !key_down)
            )
        {
            ResourceManager::playAudio("sfx_menu_move");
            key_down = true;
            selection--;
            if (selection < 0)
                selection = 2;
        }
        else if ((window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down) || (buttonData[2] == GLFW_PRESS && !key_down))
        {
            ResourceManager::playAudio("sfx_menu_select");
            execute_selection = true;
        }
        else if (!window.getKeyPressed(Graphics::GLKeys::KEY_DOWN) && !window.getKeyPressed(Graphics::GLKeys::KEY_S) &&
            !window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !window.getKeyPressed(Graphics::GLKeys::KEY_W) &&
            !window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && buttonData[2] == GLFW_RELEASE &&
            (axisData[1] > (0.0f - threshold) && axisData[1] < (0.0f + threshold))
            && key_down)
            key_down = false;
    }
    else
    {
        if ((window.getKeyPressed(Graphics::GLKeys::KEY_DOWN) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_S) && !key_down))
        {
            ResourceManager::playAudio("sfx_menu_move");
            key_down = true;
            selection++;
            if (selection > 2)
                selection = 0;
        }
        else if ((window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_W) && !key_down))
        {
            ResourceManager::playAudio("sfx_menu_move");
            key_down = true;
            selection--;
            if (selection < 0)
                selection = 2;
        }
        else if (window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down)
        {
            ResourceManager::playAudio("sfx_menu_select");
            execute_selection = true;
        }
        else if (!window.getKeyPressed(Graphics::GLKeys::KEY_DOWN) && !window.getKeyPressed(Graphics::GLKeys::KEY_S) &&
            !window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !window.getKeyPressed(Graphics::GLKeys::KEY_W) &&
            !window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && key_down)
            key_down = false;
    }
}

void StateMenu::render()
{
    // Render Title
    // TODO: Render Title

    // Render Menu Text
    Entropy::Math::Vec2 textPos[] =
    {
        Math::Vec2(7.5, 33.5), //P
        Math::Vec2(12.5, 33.5), //l
        Math::Vec2(17.5, 33.5), //a
        Math::Vec2(22.5, 33.5), //y

        Math::Vec2(7.5, 25.5), //C
        Math::Vec2(12.5, 25.5), //r
        Math::Vec2(17.5, 25.5), //e
        Math::Vec2(22.5, 25.5), //d
        Math::Vec2(27.5, 25.5), //i
        Math::Vec2(32.5, 25.5), //t
        Math::Vec2(37.5, 25.5), //s

        Math::Vec2(7.5, 17.5), //Q
        Math::Vec2(12.5, 17.5), //u
        Math::Vec2(17.5, 17.5), //i
        Math::Vec2(22.5, 17.5), //t
    };

    Entropy::Math::Vec2 textChar[] =
    {
        Math::Vec2(0, 3), //P
        Math::Vec2(12, 4), //l
        Math::Vec2(1, 4), //a
        Math::Vec2(9, 5), //y

        Math::Vec2(3, 2), //C
        Math::Vec2(2, 5), //r
        Math::Vec2(5, 4), //e
        Math::Vec2(4, 4), //d
        Math::Vec2(9, 4), //i
        Math::Vec2(4, 5), //t
        Math::Vec2(3, 5), //s

        Math::Vec2(1, 3), //Q
        Math::Vec2(5, 5), //u
        Math::Vec2(9, 4), //i
        Math::Vec2(4, 5), //t
    };

    if (selection == 0)
    {
        for (unsigned int i = 0; i < 4; i++) 
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
        for (unsigned int i = 4; i < 15; i++) 
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    }
    if (selection == 1)
    {
        for (unsigned int i = 0; i < 4; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
        for (unsigned int i = 4; i < 11; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
        for (unsigned int i = 11; i < 15; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    }
    if (selection == 2)
    {
        for (unsigned int i = 0; i < 11; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
        for (unsigned int i = 11; i < 15; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
    }

    // Render Menu Background
    // TODO: Render Menu Background
}

Entropy::GameState* StateMenu::update(GameState* gameState)
{
    if (execute_selection)
    {
        switch (selection)
        {
        case 0:
            connectedStates[0]->init();
            return connectedStates[0];
        case 1:
            connectedStates[1]->init();
            return connectedStates[1];
        case 2:
            gameFlag = false;
        default:
            break;
        }
    }
    return gameState;
}
