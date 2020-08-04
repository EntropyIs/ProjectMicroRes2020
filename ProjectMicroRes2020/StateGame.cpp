#include "StateGame.h"

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>

#include "ResourceManager.h"

using namespace Entropy;
using Entropy::Graphics::GLKeys;

StateGame::StateGame() : GameState("Game", 2), level("Assets/level_0.csv")
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
    pause = false;
}

bool StateGame::init()
{
    // Configure Entities
    spriteIndex = Math::Vec2(0.0f, 3.0f);
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
    
    if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_A)) || 
        (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_LEFT)))
    {
        spriteVeclocity.X = -maxAngle;
        spriteVeclocity.Y = maxAngle;
    }
    else if ((window.getKeyPressed(GLKeys::KEY_A) && window.getKeyPressed(GLKeys::KEY_S)) ||
        (window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)))
    {
        spriteVeclocity.X = -maxAngle;
        spriteVeclocity.Y = -maxAngle;
    }
    else if ((window.getKeyPressed(GLKeys::KEY_S) && window.getKeyPressed(GLKeys::KEY_D)) ||
        (window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
    {
        spriteVeclocity.X = maxAngle;
        spriteVeclocity.Y = -maxAngle;
    }
    else if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_D)) ||
        (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
    {
        spriteVeclocity.X = maxAngle;
        spriteVeclocity.Y = maxAngle;
    }
    else if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT))
    {
        spriteVeclocity.X = -maxVel;
        spriteVeclocity.Y = 0;
    }
    else if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN))
    {
        spriteVeclocity.X = 0;
        spriteVeclocity.Y = -maxVel;
    }
    else if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT))
    {
        spriteVeclocity.X = maxVel;
        spriteVeclocity.Y = 0;
    }
    else if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP))
    {
        spriteVeclocity.X = 0;
        spriteVeclocity.Y = maxVel;
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
    renderer.Draw(spritePos, ResourceManager::getTexture("test_sprite"), spriteIndex, ResourceManager::getSpriteSizeData("test_sprite"));
    level.Draw();
}

GameState* StateGame::update(GameState* gameState)
{
    if (spriteVeclocity.Y > 0.0f && spriteVeclocity.X < 0.0f) // Up & Left
        spriteIndex.Y = 6;
    else if (spriteVeclocity.Y > 0.0f && spriteVeclocity.X > 0.0f) // Up & Right
        spriteIndex.Y = 0;
    else if (spriteVeclocity.Y < 0.0f && spriteVeclocity.X < 0.0f) // Down & Left
        spriteIndex.Y = 4;
    else if (spriteVeclocity.Y < 0.0f && spriteVeclocity.X > 0.0f) // Down & Right
        spriteIndex.Y = 2;
    else if (spriteVeclocity.Y > 0.0f) // Up
        spriteIndex.Y = 7;
    else if (spriteVeclocity.Y < 0.0f) // Down
        spriteIndex.Y = 3;
    else if (spriteVeclocity.X > 0.0f) // Right
        spriteIndex.Y = 1;
    else if (spriteVeclocity.X < 0.0f) // Left
        spriteIndex.Y = 5;

    if (pause) // Pause Menu Called
    {
        pause = false;
        connectedStates[0]->init();
        return connectedStates[0];
    }

    //TODO: GameOver
    //if(reason)
        //return connectedStates[1];

    return gameState;
}
