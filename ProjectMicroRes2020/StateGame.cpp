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

StateGame::StateGame() : GameState("Game", 3)
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
    pause = false;
    init();
}

bool StateGame::init()
{
    // Configure Entities
    EntityManager::setPlayer(Player("char_player", 7, Math::Vec2(32.0f, 32.0f), Math::Vec2(6.0f, 6.0f), Math::Vec2(4.0f, 4.0f), Math::Vec2(-1.0f, 2.0f)));
    EntityManager::getPlayerWeapon().kill();
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

    float x = 0.0f;
    float y = 0.0f;

    if (axisCount >= 2)
    {
        x = axisData[0];
        y = axisData[1];
    }

    bool start = false;
    bool attack = false;

    if (buttonCount >= 10)
    {
        start = buttonData[9] == GLFW_PRESS;
        attack = buttonData[2] == GLFW_PRESS;
    }

    float threshold = 0.8f; // axis deadzone threshold

    // Character Movement
    if (!EntityManager::getPlayerWeapon().isAlive()) // if not attacking
    {
        if ((window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_LEFT)) ||
            x < (0.0f - threshold) && y < (0.0f - threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxAngle, maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_LEFT) && window.getKeyPressed(GLKeys::KEY_DOWN)) ||
            x < (0.0f - threshold) && y >(0.0f + threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_DOWN) && window.getKeyPressed(GLKeys::KEY_RIGHT)) ||
            x > (0.0f + threshold) && y > (0.0f + threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxAngle, -maxAngle));
        else if ((window.getKeyPressed(GLKeys::KEY_UP) && window.getKeyPressed(GLKeys::KEY_RIGHT)) ||
            x > (0.0f + threshold) && y < (0.0f - threshold)
            )
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxAngle, maxAngle));
        else if (window.getKeyPressed(GLKeys::KEY_LEFT) || x < (0.0f - threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(-maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_DOWN) || y > (0.0f + threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, -maxVel));
        else if (window.getKeyPressed(GLKeys::KEY_RIGHT) || x > (0.0f + threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(maxVel, 0));
        else if (window.getKeyPressed(GLKeys::KEY_UP) || y < (0.0f - threshold))
            EntityManager::getPlayer().setVelocity(Math::Vec2(0, maxVel));
        else
            EntityManager::getPlayer().stop();
    }

    // Attack / Interact
    if ((window.getKeyPressed(GLKeys::KEY_Z) || (attack)) && !EntityManager::getPlayerWeapon().isAlive())
    {
        EntityManager::getPlayer().stop();

        switch (EntityManager::getPlayer().getLastDirection())
        {
        case UPLEFT:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 2, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-8.0f, 4.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case UPRIGHT:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 4, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(6.0f, 4.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case DOWNLEFT:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 0, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-6.0f, -6.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case DOWNRIGHT:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 6, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(6.0f, -6.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case LEFT:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 1, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-9.0f, -2.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case RIGHT:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 5, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(7.0f, 1.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case UP:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 3, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(1.0f, 9.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        case DOWN:
            EntityManager::setPlayerWeapon(PlayerWeapon("char_player_weapon", 7, 
                EntityManager::getPlayer().getPosition() + Math::Vec2(8.0f, 8.0f), Math::Vec2(-1.0f, -8.0f)));
            EntityManager::getPlayer().setAttacking();
            break;
        }
        ResourceManager::playAudio("sfx_player_attack");
    }

    if (window.getKeyPressed(GLKeys::KEY_ESCAPE) || start)
        pause = true;
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
    EntityManager::drawHotdogWeapon(renderer);
    EntityManager::getLevel().Draw(renderer);
}

GameState* StateGame::update(GameState* gameState)
{
    // Update Player
    EntityManager::getPlayer().Update();
    EntityManager::getPlayerWeapon().Update();

    // Update Level Data
    EntityManager::getLevel().Update();
    EntityManager::updateHotdogWeapon();

    // Check if level has hotdog king
    if (EntityManager::getLevel().isEntity("hotdog_king"))
    {
        if (!EntityManager::getLevel().getEntity("hotdog_king").isAlive())
        {
            connectedStates[0]->init();
            return connectedStates[0];
        }
    }

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
