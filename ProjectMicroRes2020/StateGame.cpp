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
    init();
}

bool StateGame::init()
{
    // Configure Entities
    player = GameObject("Player", "test_sprite", Math::Vec2(0.0f, 3.0f), Math::Vec2(32.0f, 32.0f),
        Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f), Math::Vec2(0.0f, 4.0f));
    playerVelocity = Math::Vec2(0.0f, 0.0f);

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
        playerVelocity.X = -maxAngle;
        playerVelocity.Y = maxAngle;
    }
    else if ((window.getKeyPressed(GLKeys::KEY_A) && window.getKeyPressed(GLKeys::KEY_S)) ||
        (window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)))
    {
        playerVelocity.X = -maxAngle;
        playerVelocity.Y = -maxAngle;
    }
    else if ((window.getKeyPressed(GLKeys::KEY_S) && window.getKeyPressed(GLKeys::KEY_D)) ||
        (window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
    {
        playerVelocity.X = maxAngle;
        playerVelocity.Y = -maxAngle;
    }
    else if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_D)) ||
        (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
    {
        playerVelocity.X = maxAngle;
        playerVelocity.Y = maxAngle;
    }
    else if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT))
    {
        playerVelocity.X = -maxVel;
        playerVelocity.Y = 0;
    }
    else if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN))
    {
        playerVelocity.X = 0;
        playerVelocity.Y = -maxVel;
    }
    else if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT))
    {
        playerVelocity.X = maxVel;
        playerVelocity.Y = 0;
    }
    else if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP))
    {
        playerVelocity.X = 0;
        playerVelocity.Y = maxVel;
    }
    else
    {
        playerVelocity.X = 0;
        playerVelocity.Y = 0;
    }
        

    player.position += playerVelocity * ResourceManager::getTimeElapsed();
}

void StateGame::render()
{
    player.Draw(renderer);
    level.Draw();
}

GameState* StateGame::update(GameState* gameState)
{
    if (playerVelocity.Y > 0.0f && playerVelocity.X < 0.0f) // Up & Left
        player.sprite_index.Y = 6;
    else if (playerVelocity.Y > 0.0f && playerVelocity.X > 0.0f) // Up & Right
        player.sprite_index.Y = 0;
    else if (playerVelocity.Y < 0.0f && playerVelocity.X < 0.0f) // Down & Left
        player.sprite_index.Y = 4;
    else if (playerVelocity.Y < 0.0f && playerVelocity.X > 0.0f) // Down & Right
        player.sprite_index.Y = 2;
    else if (playerVelocity.Y > 0.0f) // Up
        player.sprite_index.Y = 7;
    else if (playerVelocity.Y < 0.0f) // Down
        player.sprite_index.Y = 3;
    else if (playerVelocity.X > 0.0f) // Right
        player.sprite_index.Y = 1;
    else if (playerVelocity.X < 0.0f) // Left
        player.sprite_index.Y = 5;

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
