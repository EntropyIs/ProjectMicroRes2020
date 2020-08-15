#include "StatePause.h"

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>
#include <Entropy/Graphics/JoystickController.h>

#include "ResourceManager.h"

using namespace Entropy;

bool StatePause::init()
{
    selection = 0;
    key_down = true;
    execute_selection = false;
    return true;
}

void StatePause::input(Graphics::Window& window)
{
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
            if (selection > 1)
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
                selection = 1;
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
            if (selection > 1)
                selection = 0;
        }
        else if ((window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_W) && !key_down))
        {
            ResourceManager::playAudio("sfx_menu_move");
            key_down = true;
            selection--;
            if (selection < 0)
                selection = 1;
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

void StatePause::render()
{
    Math::Vec2 textPos[] =
    {
        Math::Vec2(22.5, 54.5), //P
        Math::Vec2(27.5, 54.5), //a
        Math::Vec2(32.5, 54.5), //u
        Math::Vec2(37.5, 54.5), //s
        Math::Vec2(42.5, 54.5), //e


        Math::Vec2(14.5, 35.5), //C
        Math::Vec2(19.5, 35.5), //o
        Math::Vec2(24.5, 35.5), //n
        Math::Vec2(29.5, 35.5), //t
        Math::Vec2(34.5, 35.5), //i
        Math::Vec2(39.5, 35.5), //n
        Math::Vec2(44.5, 35.5), //u
        Math::Vec2(49.5, 35.5), //e

        Math::Vec2(24.5, 28.5), //Q
        Math::Vec2(29.5, 28.5), //u
        Math::Vec2(34.5, 28.5), //i
        Math::Vec2(39.5, 28.5), //t
    };

    Math::Vec2 textChar[] =
    {
        Math::Vec2(0, 3), //P
        Math::Vec2(1, 4), //a
        Math::Vec2(5, 5), //u
        Math::Vec2(3, 5), //s
        Math::Vec2(5, 4), //t

        Math::Vec2(3, 2),  //C
        Math::Vec2(15, 4), //o
        Math::Vec2(14, 4), //n
        Math::Vec2(4, 5),  //t
        Math::Vec2(9, 4),  //i
        Math::Vec2(14, 4), //n
        Math::Vec2(5, 5),  //u
        Math::Vec2(5, 4),  //e
                      
        Math::Vec2(1, 3), //Q
        Math::Vec2(5, 5), //u
        Math::Vec2(9, 4), //i
        Math::Vec2(4, 5), //t
    };

    // Draw Pause Menu
    for (unsigned int i = 0; i < 5; i++) // Pause
        renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));

    if (selection == 0)
    {
        for (unsigned int i = 5; i < 13; i++) // Continue
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
        for (unsigned int i = 13; i < 17; i++) // Quit
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    }
    else if (selection == 1)
    {
        for (unsigned int i = 5; i < 13; i++) // Continue
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
        for (unsigned int i = 13; i < 17; i++) // Quit
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
    }

    // Draw Menu Background
    renderer.Draw(Math::Vec2(12, 41), ResourceManager::getTexture("random_assets"), Math::Vec2(0, 0), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(20, 41), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 0), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(28, 41), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 0), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(36, 41), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 0), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(44, 41), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 0), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(52, 41), ResourceManager::getTexture("random_assets"), Math::Vec2(2, 0), ResourceManager::getSpriteSizeData("random_assets"));

    renderer.Draw(Math::Vec2(12, 33), ResourceManager::getTexture("random_assets"), Math::Vec2(0, 1), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(20, 33), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 1), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(28, 33), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 1), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(36, 33), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 1), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(44, 33), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 1), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(52, 33), ResourceManager::getTexture("random_assets"), Math::Vec2(2, 1), ResourceManager::getSpriteSizeData("random_assets"));

    renderer.Draw(Math::Vec2(12, 25), ResourceManager::getTexture("random_assets"), Math::Vec2(0, 2), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(20, 25), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 2), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(28, 25), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 2), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(36, 25), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 2), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(44, 25), ResourceManager::getTexture("random_assets"), Math::Vec2(1, 2), ResourceManager::getSpriteSizeData("random_assets"));
    renderer.Draw(Math::Vec2(52, 25), ResourceManager::getTexture("random_assets"), Math::Vec2(2, 2), ResourceManager::getSpriteSizeData("random_assets"));

    // Render Background Scene
    connectedStates[0]->render(); // TODO: Blur effect?
}

GameState* StatePause::update(GameState* gameState)
{
    if (execute_selection)
    {
        switch (selection)
        {
        case 0: // Dont re-init gameplay when returning from pause menu
            return connectedStates[0]; 
        case 1:
            connectedStates[1]->init();
            return connectedStates[1];
        default:
            break;
        }
    }
    return gameState;
}
