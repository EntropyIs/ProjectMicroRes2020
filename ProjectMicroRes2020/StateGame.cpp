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
        Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f), Math::Vec2(0.0f, 2.0f));
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
        player.setVelocity(Math::Vec2(-maxAngle, maxAngle));
    else if ((window.getKeyPressed(GLKeys::KEY_A) && window.getKeyPressed(GLKeys::KEY_S)) ||
        (window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)))
        player.setVelocity(Math::Vec2(-maxAngle, -maxAngle));
    else if ((window.getKeyPressed(GLKeys::KEY_S) && window.getKeyPressed(GLKeys::KEY_D)) ||
        (window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
        player.setVelocity(Math::Vec2(maxAngle, -maxAngle));
    else if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_D)) ||
        (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
        player.setVelocity(Math::Vec2(maxAngle, maxAngle));
    else if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT))
        player.setVelocity(Math::Vec2(-maxVel, 0));
    else if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN))
        player.setVelocity(Math::Vec2(0, -maxVel));
    else if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT))
        player.setVelocity(Math::Vec2(maxVel, 0));
    else if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP))
        player.setVelocity(Math::Vec2(0, maxVel));
    else
        player.setVelocity(Math::Vec2(0, 0));
}

void StateGame::render()
{
    player.Draw(renderer);
    level.Draw();
}

GameState* StateGame::update(GameState* gameState)
{
    if (player.velocity.Y > 0.0f && player.velocity.X < 0.0f) // Up & Left
        player.sprite_index.Y = 6;
    else if (player.velocity.Y > 0.0f && player.velocity.X > 0.0f) // Up & Right
        player.sprite_index.Y = 0;
    else if (player.velocity.Y < 0.0f && player.velocity.X < 0.0f) // Down & Left
        player.sprite_index.Y = 4;
    else if (player.velocity.Y < 0.0f && player.velocity.X > 0.0f) // Down & Right
        player.sprite_index.Y = 2;
    else if (player.velocity.Y > 0.0f) // Up
        player.sprite_index.Y = 7;
    else if (player.velocity.Y < 0.0f) // Down
        player.sprite_index.Y = 3;
    else if (player.velocity.X > 0.0f) // Right
        player.sprite_index.Y = 1;
    else if (player.velocity.X < 0.0f) // Left
        player.sprite_index.Y = 5;

    // Process Player Movement
    player.Update();
    for (unsigned int i = 0; i < level.getColliders().size(); i++)
    {
        if (player.detectCollions(level.getColliders()[i]))
        {
            player.undoUpdate(); // Step Back
            player.setVelocity(Math::Vec2(0, 0)); // TODO: cancel out colision direction components? (i.e, slide along wall)
        }
    }

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
