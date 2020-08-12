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
    EntityManager::setPlayer(Player("player_sheet", 7, Math::Vec2(32.0f, 32.0f), Math::Vec2(6.0f, 6.0f), Math::Vec2(4.0f, 4.0f), Math::Vec2(-1.0f, 2.0f)));
    EntityManager::setLevelManager("Assets/Levels/levels.csv");

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
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxAngle, maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_A) && window.getKeyPressed(GLKeys::KEY_S)) ||
            (window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)) ||
            axisData[0] < (0.0f - threshold) && axisData[1] > (0.0f + threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_S) && window.getKeyPressed(GLKeys::KEY_D)) ||
            (window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)) ||
            axisData[0] > (0.0f + threshold) && axisData[1] > (0.0f + threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_W) && window.getKeyPressed(GLKeys::KEY_D)) ||
            (window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)) ||
            axisData[0] > (0.0f + threshold) && axisData[1] < (0.0f - threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxAngle, maxAngle));
        else if (window.getKeyPressed(GLKeys::KEY_A) || window.getKeyPressed(GLKeys::KEY_LEFT) || axisData[0] < (0.0f - threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_S) || window.getKeyPressed(GLKeys::KEY_DOWN) || axisData[1] > (0.0f + threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, -maxVel));
        else if (window.getKeyPressed(GLKeys::KEY_D) || window.getKeyPressed(GLKeys::KEY_RIGHT) || axisData[0] > (0.0f + threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_W) || window.getKeyPressed(GLKeys::KEY_UP) || axisData[1] < (0.0f - threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, maxVel));
        else
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, 0));

        // Attack / Interact
        if ((window.getKeyPressed(GLKeys::KEY_Z) || (buttonData[2] == GLFW_PRESS)) && !EntityManager::getPlayerWeapon().isAlive())
            switch (EntityManager::getPlayer().getLastDirection())
            {
            case UPLEFT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 6, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-6.0f, 6.0f)));
                break;
            case UPRIGHT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 0, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(6.0f, 6.0f)));
                break;
            case DOWNLEFT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 4, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-6.0f, -6.0f)));
                break;
            case DOWNRIGHT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 2, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(6.0f, -6.0f)));
                break;
            case LEFT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 5, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-7.0f, 0.0f)));
                break;
            case RIGHT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 1, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(7.0f, 0.0f)));
                break;
            case UP:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 7, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(0.0f, 7.0f)));
                break;
            case DOWN:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 3, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(0.0f, -7.0f)));
                break;
            }
    }
    else // Keyboard Only Movement
    {
        // Character Movement
        if ((window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_LEFT)))
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxAngle, maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)))
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)))
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxAngle, maxAngle));
        else if (window.getKeyPressed(GLKeys::KEY_LEFT))
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_DOWN))
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, -maxVel));
        else if (window.getKeyPressed(GLKeys::KEY_RIGHT))
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_UP))
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, maxVel));
        else
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, 0));

        // Attack / Interact
        if (window.getKeyPressed(GLKeys::KEY_Z))
            switch (EntityManager::getPlayer().getLastDirection() && !EntityManager::getPlayerWeapon().isAlive())
            {
            case UPLEFT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 6, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-6.0f, 6.0f)));
                break;
            case UPRIGHT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 0, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(6.0f, 6.0f)));
                break;
            case DOWNLEFT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 4, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-6.0f, -6.0f)));
                break;
            case DOWNRIGHT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 2, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(6.0f, -6.0f)));
                break;
            case LEFT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 5, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-7.0f, 0.0f)));
                break;
            case RIGHT:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 1, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(7.0f, 0.0f)));
                break;
            case UP:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 7, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(0.0f, 7.0f)));
                break;
            case DOWN:
                EntityManager::setPlayerWeapon(PlayerWeapon("test_sword", 3, EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(0.0f, -7.0f)));
                break;
            }
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
    if (EntityManager::getPlayer().getLastDirection() == DOWN ||
        EntityManager::getPlayer().getLastDirection() == DOWNLEFT ||
        EntityManager::getPlayer().getLastDirection() == DOWNRIGHT)
    {
        EntityManager::getPlayerWeapon().Draw(renderer);
        EntityManager::getPlayer().Draw(renderer);
    }
    else
    {
        EntityManager::getPlayer().Draw(renderer);
        EntityManager::getPlayerWeapon().Draw(renderer);
    }
    EntityManager::getLevel().Draw(renderer);
}

GameState* StateGame::update(GameState* gameState)
{
    // Update Player
    EntityManager::getPlayer().Update();
    EntityManager::getPlayerWeapon().Update();

    // Update Level Data
    EntityManager::getLevel().Update();

    if (pause) // Pause Menu Called
    {
        pause = false;
        connectedStates[0]->init();
        return connectedStates[0];
    }
    if (!EntityManager::getPlayer().isAlive()) // Player has died, game over
    {
        connectedStates[1]->init();
        return connectedStates[1];
    }

    return gameState;
}
