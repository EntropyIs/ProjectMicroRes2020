#include "StateGame.h"

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>

#include "ResourceManager.h"

using namespace Entropy;
using Entropy::Graphics::GLKeys;

StateGame::StateGame() : GameState("Game", 2)
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
    pause = false;
}

bool StateGame::init()
{
    // Configure Entities
    spriteIndex = Math::Vec2(8.0f, 0.0f);
    spritePos = Math::Vec2(32.0f, 32.0f);
    spriteVeclocity = Math::Vec2(0.0f, 0.0f);

    // Configure shaders
    ResourceManager::getShader("spriteShader").use();
    ResourceManager::getShader("spriteShader").setMat4("projection", Projection);
    ResourceManager::getShader("spriteShader").setInt("spriteSheet", 0);

    pause = false;

    return false;
}

void StateGame::input(Graphics::Window& window)
{
    // Pause
    if (window.getKeyPressed(GLKeys::KEY_ESCAPE))
        pause = true;

    // Character Movement
    if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP))
    {
        spriteVeclocity.X = 0;
        spriteVeclocity.Y = maxVel;
    }
    else if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN))
    {
        spriteVeclocity.X = 0;
        spriteVeclocity.Y = -maxVel;
    }
    else if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT))
    {
        spriteVeclocity.X = -maxVel;
        spriteVeclocity.Y = 0;
    }
    else if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT))
    {
        spriteVeclocity.X = maxVel;
        spriteVeclocity.Y = 0;
    }
    else
    {
        spriteVeclocity.X = 0;
        spriteVeclocity.Y = 0;
    }
        

    spritePos += spriteVeclocity * ResourceManager::getTimeElapsed();
}

void StateGame::render()
{
    renderer.Draw(spritePos, ResourceManager::getTexture("testSprite"), spriteIndex, ResourceManager::getSpriteSizeData("testSprite"), 16, 16);
}

GameState* StateGame::update(GameState* gameState)
{
    if (spriteVeclocity.Y > 0.0f) // Up
        spriteIndex.X = 2;
    else if (spriteVeclocity.Y < 0.0f) // Down
        spriteIndex.X = 6;
    else if (spriteVeclocity.X > 0.0f) // Right
        spriteIndex.X = 0;
    else if (spriteVeclocity.X < 0.0f) // Left
        spriteIndex.X = 4;
    else
        spriteIndex.X = 8;

    if (pause) // Pause Menu Called
    {
        pause = true;
        return connectedStates[0];
    }

    //TODO: GameOver
    //if(reason)
        //return connectedStates[1];

    return gameState;
}
