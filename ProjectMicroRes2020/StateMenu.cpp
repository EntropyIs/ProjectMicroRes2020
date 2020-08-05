#include "StateMenu.h"

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
    // Close window on KEY_ESCAPE been pressed
    if (window.getKeyPressed(Graphics::GLKeys::KEY_ESCAPE))
        window.setShouldClose(true);
    else if ((window.getKeyPressed(Graphics::GLKeys::KEY_DOWN) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_S) && !key_down))
    {
        key_down = true;
        selection++;
        if (selection > 3)
            selection = 0;
    }
    else if ((window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !key_down) || (window.getKeyPressed(Graphics::GLKeys::KEY_W) && !key_down))
    {
        key_down = true;
        selection--;
        if (selection < 0)
            selection = 3;
    }
    else if (window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && !key_down)
        execute_selection = true;
    else if (!window.getKeyPressed(Graphics::GLKeys::KEY_DOWN) && !window.getKeyPressed(Graphics::GLKeys::KEY_S) && !window.getKeyPressed(Graphics::GLKeys::KEY_UP) && !window.getKeyPressed(Graphics::GLKeys::KEY_W) && !window.getKeyPressed(Graphics::GLKeys::KEY_ENTER) && key_down)
        key_down = false;
}

void StateMenu::render()
{
    // Render Title
    // TODO: Render Title

    // Render Menu Text
    Entropy::Math::Vec2 textPos[] =
    {
        Math::Vec2(7.5, 35.5), //P
        Math::Vec2(12.5, 35.5), //l
        Math::Vec2(17.5, 35.5), //a
        Math::Vec2(22.5, 35.5), //y

        Math::Vec2(7.5, 28.5), //H
        Math::Vec2(12.5, 28.5), //i
        Math::Vec2(17.5, 28.5), //g
        Math::Vec2(22.5, 28.5), //h
        Math::Vec2(32.5, 28.5), //S
        Math::Vec2(37.5, 28.5), //c
        Math::Vec2(42.5, 28.5), //o
        Math::Vec2(47.5, 28.5), //r
        Math::Vec2(52.5, 28.5), //e
        Math::Vec2(57.5, 28.5), //s

        Math::Vec2(7.5, 21.5), //C
        Math::Vec2(12.5, 21.5), //r
        Math::Vec2(17.5, 21.5), //e
        Math::Vec2(22.5, 21.5), //d
        Math::Vec2(27.5, 21.5), //i
        Math::Vec2(32.5, 21.5), //t
        Math::Vec2(37.5, 21.5), //s

        Math::Vec2(7.5, 14.5), //Q
        Math::Vec2(12.5, 14.5), //u
        Math::Vec2(17.5, 14.5), //i
        Math::Vec2(22.5, 14.5), //t
    };

    Entropy::Math::Vec2 textChar[] =
    {
        Math::Vec2(0, 3), //P
        Math::Vec2(12, 4), //l
        Math::Vec2(1, 4), //a
        Math::Vec2(9, 5), //y

        Math::Vec2(8, 2), //H
        Math::Vec2(9, 4), //i
        Math::Vec2(7, 4), //g
        Math::Vec2(8, 4), //h
        Math::Vec2(3, 3), //S
        Math::Vec2(3, 4), //c
        Math::Vec2(15, 4), //o
        Math::Vec2(2, 5), //r
        Math::Vec2(5, 4), //e
        Math::Vec2(3, 5), //s

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
        for (unsigned int i = 4; i < 25; i++) 
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    }
    if (selection == 1)
    {
        for (unsigned int i = 0; i < 4; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
        for (unsigned int i = 4; i < 14; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
        for (unsigned int i = 14; i < 25; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    }
    if (selection == 2)
    {
        for (unsigned int i = 0; i < 14; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
        for (unsigned int i = 14; i < 21; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_black"), textChar[i], ResourceManager::getSpriteSizeData("charset_black"));
        for (unsigned int i = 21; i < 25; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
    }
    if (selection == 3)
    {
        for (unsigned int i = 0; i < 21; i++)
            renderer.Draw(textPos[i], ResourceManager::getTexture("charset_grey"), textChar[i], ResourceManager::getSpriteSizeData("charset_grey"));
        for (unsigned int i = 21; i < 25; i++)
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
            connectedStates[2]->init();
            return connectedStates[2];
        case 3:
            gameFlag = false;
        default:
            break;
        }
    }
    return gameState;
}
