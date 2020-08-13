#include "StateGame.h"

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>
#include <Entropy/Graphics/JoystickController.h>

#include <iostream>

#include "ResourceManager.h"
#include "AnimationRenderer.h"

#include "EntityManager.h"

using namespace Entropy;
using Entropy::Graphics::GLKeys;

StateGame::StateGame() : GameState("Game", 2), animationRenderer("marker", 4, 0, 2)
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
    init();
}

bool StateGame::init()
{
    // Configure Entities
    EntityManager::setPlayer(Player("player_sheet", 7, Math::Vec2(32.0f, 32.0f), Math::Vec2(6.0f, 6.0f), Math::Vec2(4.0f, 4.0f), Math::Vec2(-1.0f, 2.0f)));
    EntityManager::setLevelManager("Assets/Levels/levels.csv");

    // Configure shaders
    ResourceManager::getShader("spriteShader").use();
    ResourceManager::getShader("spriteShader").setMat4("projection", Projection);
    ResourceManager::getShader("spriteShader").setInt("spriteSheet", 0);

    return false;
}

void StateGame::input(Graphics::Window& window)
{
    std::string tile = EntityManager::getLevel().getName() + "[" + std::to_string(i) +"," + std::to_string(j) + "]";

    SpriteData spriteData = ResourceManager::getSpriteSizeData(EntityManager::getLevel().getTile(tile).Tileset);

    if (window.getKeyPressed(GLKeys::KEY_UP) && !key_down)
    {
        key_down = true;
        if (EntityManager::getLevel().getTile(tile).TY == 0)
            EntityManager::getLevel().getTile(tile).TY = spriteData.num_cols - 1;
        else
            EntityManager::getLevel().getTile(tile).TY--;
    }
    else if (window.getKeyPressed(GLKeys::KEY_DOWN) && !key_down)
    {
        key_down = true;
        if (EntityManager::getLevel().getTile(tile).TY == spriteData.num_cols - 1)
            EntityManager::getLevel().getTile(tile).TY = 0;
        else
            EntityManager::getLevel().getTile(tile).TY++;
    }
    else if (window.getKeyPressed(GLKeys::KEY_LEFT) && !key_down)
    {
        key_down = true;
        if (EntityManager::getLevel().getTile(tile).TX == spriteData.num_rows - 1)
            EntityManager::getLevel().getTile(tile).TX = 0;
        else
            EntityManager::getLevel().getTile(tile).TX++;
    }
    else if (window.getKeyPressed(GLKeys::KEY_RIGHT) && !key_down)
    {
        key_down = true;
        if (EntityManager::getLevel().getTile(tile).TX == 0)
            EntityManager::getLevel().getTile(tile).TX = spriteData.num_rows - 1;
        else
            EntityManager::getLevel().getTile(tile).TX--;
    }

    else if (window.getKeyPressed(GLKeys::KEY_W) && !key_down)
    {
        key_down = true;
        if (j == 7)
            j = 0;
        else
            j++;
    }
    else if (window.getKeyPressed(GLKeys::KEY_S) && !key_down)
    {
        
        key_down = true;
        if (j == 0)
            j = 7;
        else
            j--;
    }
    else if (window.getKeyPressed(GLKeys::KEY_A) && !key_down)
    {
        key_down = true;
        if (i == 0)
            i = 7;
        else
            i--;
    }
    else if (window.getKeyPressed(GLKeys::KEY_D) && !key_down)
    {
        key_down = true;
        if (i == 7)
            i = 0;
        else
            i++;
    }
    else if (window.getKeyPressed(GLKeys::KEY_ENTER) && !key_down)// Save Level
    {
        EntityManager::getLevel().save("Assets/Levels");
        EntityManager::nextLevel();
        key_down = true;
    }
    else if (!window.getKeyPressed(GLKeys::KEY_UP) && !window.getKeyPressed(GLKeys::KEY_DOWN) &&
        !window.getKeyPressed(GLKeys::KEY_LEFT) && !window.getKeyPressed(GLKeys::KEY_RIGHT) &&
        !window.getKeyPressed(GLKeys::KEY_W) && !window.getKeyPressed(GLKeys::KEY_S) &&
        !window.getKeyPressed(GLKeys::KEY_A) && !window.getKeyPressed(GLKeys::KEY_D) &&
        !window.getKeyPressed(GLKeys::KEY_ENTER) && key_down)
    {
        key_down = false;
    }
}

void StateGame::render()
{
    Math::Vec2 selected(8 * i + 4, 8 * j + 4);
    animationRenderer.Draw(renderer, selected);
    EntityManager::getLevel().Draw(renderer);
}

GameState* StateGame::update(GameState* gameState)
{
    animationRenderer.Update();
    return gameState;
}
