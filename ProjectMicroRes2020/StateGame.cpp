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

StateGame::StateGame() : GameState("Game", 2)
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
    pause = false;
    init();
}

bool StateGame::init()
{
    // Configure Entities
    player = Player("Player", "test_sprite", 3, Math::Vec2(32.0f, 32.0f), Math::Vec2(8.0f, 8.0f), Math::Vec2(4.0f, 4.0f), Math::Vec2(0.0f, 2.0f));
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
    Graphics::JoystickController joystickController;
    int axisCount;
    int buttonCount;
    const float* axisData = joystickController.getAxisData(GLFW_JOYSTICK_1, &axisCount);
    const unsigned char* buttonData = joystickController.getButtonsData(GLFW_JOYSTICK_1, &buttonCount);

    if (axisCount >= 2) // Joystick has 2 or more axis
    {
        float threshold = 0.8f; // axis deadzone threshold

        // Character Movement
        if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_A)) ||
            (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_LEFT)) ||
            axisData[0] < (0.0f - threshold) && axisData[1] < (0.0f - threshold)
            )
            player.setVelocity(Math::Vec2(-maxAngle, maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_A) && window.getKeyPressed(GLKeys::KEY_S)) ||
            (window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)) ||
            axisData[0] < (0.0f - threshold) && axisData[1] > (0.0f + threshold)
            )
            player.setVelocity(Math::Vec2(-maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_S) && window.getKeyPressed(GLKeys::KEY_D)) ||
            (window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)) ||
            axisData[0] > (0.0f + threshold) && axisData[1] > (0.0f + threshold)
            )
            player.setVelocity(Math::Vec2(maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_D)) ||
            (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)) ||
            axisData[0] > (0.0f + threshold) && axisData[1] < (0.0f - threshold)
            )
            player.setVelocity(Math::Vec2(maxAngle, maxAngle));
        else if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT) || axisData[0] < (0.0f - threshold))
            player.setVelocity(Math::Vec2(-maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN) || axisData[1] > (0.0f + threshold))
            player.setVelocity(Math::Vec2(0, -maxVel));
        else if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT) || axisData[0] > (0.0f + threshold))
            player.setVelocity(Math::Vec2(maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP) || axisData[1] < (0.0f - threshold))
            player.setVelocity(Math::Vec2(0, maxVel));
        else
            player.setVelocity(Math::Vec2(0, 0));
    }
    else // Keyboard Only Movement
    {
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

    // Pause
    if (buttonCount > 0) // Controler has buttons
    {
        if (window.getKeyPressed(GLKeys::KEY_ESCAPE) || buttonData[9] == GLFW_PRESS)
            pause = true;
    }
    else
    {
        if (window.getKeyPressed(GLKeys::KEY_ESCAPE))
            pause = true;
    }
}

void StateGame::render()
{
    player.Draw(renderer);
    EntityManager::getLevel().Draw(renderer);
}

GameState* StateGame::update(GameState* gameState)
{
    // Update Player
    if (player.getVelocity().Y > 0.0f && player.getVelocity().X < 0.0f) // Up & Left
        player.setSpriteIndexY(6);
    else if (player.getVelocity().Y > 0.0f && player.getVelocity().X > 0.0f) // Up & Right
        player.setSpriteIndexY(0);
    else if (player.getVelocity().Y < 0.0f && player.getVelocity().X < 0.0f) // Down & Left
        player.setSpriteIndexY(4);
    else if (player.getVelocity().Y < 0.0f && player.getVelocity().X > 0.0f) // Down & Right
        player.setSpriteIndexY(2);
    else if (player.getVelocity().Y > 0.0f) // Up
        player.setSpriteIndexY(7);
    else if (player.getVelocity().Y < 0.0f) // Down
        player.setSpriteIndexY(3);
    else if (player.getVelocity().X > 0.0f) // Right
        player.setSpriteIndexY(1);
    else if (player.getVelocity().X < 0.0f) // Left
        player.setSpriteIndexY(5);

    // Process Player Movement
    player.Update();

    // Update Level Data
    EntityManager::getLevel().Update();

    if (pause) // Pause Menu Called
    {
        pause = false;
        connectedStates[0]->init();
        return connectedStates[0];
    }
    if (!player.isAlive()) // Player has died, game over
    {
        connectedStates[1]->init();
        return connectedStates[1];
    }

    return gameState;
}
