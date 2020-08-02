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

    // Move Character
    if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP))
    {
        if (spriteVeclocity.Y < maxVel)
            spriteVeclocity.Y += accel * ResourceManager::getTimeElapsed();
    }
    else
    {
        if (spriteVeclocity.Y > 0)
            spriteVeclocity.Y -= accel * ResourceManager::getTimeElapsed();
    }
    if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN))
    {
        if (spriteVeclocity.Y > -maxVel)
            spriteVeclocity.Y -= accel * ResourceManager::getTimeElapsed();
    }
    else
    {
        if (spriteVeclocity.Y < 0)
            spriteVeclocity.Y += accel * ResourceManager::getTimeElapsed();
    }
    if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT))
    {
        if (spriteVeclocity.X > -maxVel)
            spriteVeclocity.X -= accel * ResourceManager::getTimeElapsed();
    }
    else
    {
        if (spriteVeclocity.X < 0)
            spriteVeclocity.X += accel * ResourceManager::getTimeElapsed();
    }
    if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT))
    {
        if (spriteVeclocity.X < maxVel)
            spriteVeclocity.X += accel * ResourceManager::getTimeElapsed();
    }
    else
    {
        if (spriteVeclocity.X > 0)
            spriteVeclocity.X -= accel * ResourceManager::getTimeElapsed();
    }

    spritePos += spriteVeclocity * ResourceManager::getTimeElapsed();
}

void StateGame::render()
{
    renderer.Draw(spritePos, ResourceManager::getTexture("testSprite"), spriteIndex, ResourceManager::getSpriteSizeData("testSprite"), 16, 16);
}

GameState* StateGame::update(GameState* gameState)
{
    spriteIndex.X += 1;
    if (spriteIndex.X > 9)
        spriteIndex.X = 0;

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
