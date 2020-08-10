#include "Player.h"

#include "EntityManager.h"
#include "ResourceManager.h"

using namespace Entropy;

Player::Player(const char* spriteName, unsigned int row, Entropy::Math::Vec2 position,
    Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) :
    AnimatedGameObject("Player", spriteName, 4, row, 12, position, boxSize, boxOffset, textureOffset)
{
    health = 3;
    timer = 0.0f;
    vulnerable = true;
}

Direction Player::getLastDirection()
{
    return lastDirection;
}

void Player::Update()
{
    // Set Sprite Direction and Animate
    animationRenderer.playAnimation();
    if (getVelocity().Y > 0.0f && getVelocity().X < 0.0f) // Up & Left
    {
        animationRenderer.setRowNumber(6);
        lastDirection = Direction::UPLEFT;
    }
    else if (getVelocity().Y > 0.0f && getVelocity().X > 0.0f) // Up & Right
    {
        animationRenderer.setRowNumber(0);
        lastDirection = Direction::UPRIGHT;
    }
    else if (getVelocity().Y < 0.0f && getVelocity().X < 0.0f) // Down & Left
    {
        animationRenderer.setRowNumber(4);
        lastDirection = Direction::DOWNLEFT;
    }
    else if (getVelocity().Y < 0.0f && getVelocity().X > 0.0f) // Down & Right
    {
        animationRenderer.setRowNumber(2);
        lastDirection = Direction::DOWNRIGHT;
    }
    else if (getVelocity().Y > 0.0f) // Up
    {
        animationRenderer.setRowNumber(7);
        lastDirection = Direction::UP;
    }
    else if (getVelocity().Y < 0.0f) // Down
    {
        animationRenderer.setRowNumber(3);
        lastDirection = Direction::DOWN;
    }
    else if (getVelocity().X > 0.0f) // Right
    {
        animationRenderer.setRowNumber(1);
        lastDirection = Direction::RIGHT;
    }
    else if (getVelocity().X < 0.0f) // Left
    {
        animationRenderer.setRowNumber(5);
        lastDirection = Direction::LEFT;
    }
    else
        animationRenderer.stopAnimation();
    animationRenderer.Update();

    // Move Character
    performMovement();

    for (unsigned int i = 0; i < EntityManager::getLevel().getColliders().size(); i++)
    {
        std::string object = EntityManager::getLevel().getColliders()[i];
        if (detectCollion(EntityManager::getLevel().getCollider(object)))
        {
            if (EntityManager::getLevel().isWall(object)) // Wall
            {
                undoMovement();// Step Back
                setVelocity(Math::Vec2(0, 0)); // TODO: cancel out colision direction components? (i.e, slide along wall)
                break;
            }
            else if (EntityManager::getLevel().isLink(object)) // Warp-point
            {
                Tile tile = EntityManager::getLevel().getTile(object);
                SpriteData spriteData = ResourceManager::getSpriteSizeData(tile.Tileset);
                setPosition(Math::Vec2(
                    (tile.DX * spriteData.cel_width) + (spriteData.cel_width / 2.0f),
                    (tile.DY * spriteData.cel_height) + (spriteData.cel_height / 2.0f)));
                EntityManager::setLevel(tile.LinkedLevel);
                break; // Found collision so stop checking others
            }
            else if (EntityManager::getLevel().isEntity(object) && vulnerable) // Entity (collectable or enemy)
            {
                if (EntityManager::getLevel().getEntity(object).isAlive())
                {
                    undoMovement(); // Step Back
                    health--;
                    vulnerable = false;
                    timer = 0;
                    break;
                }
            }
        }

        if (!vulnerable)
        {
            float timeElapsed = ResourceManager::getTimeElapsed();
            timer += ResourceManager::getTimeElapsed();
            if (timer > invulnerable_time)
                vulnerable = true;
        }

        if (health == 0)
            alive = false;
    }
}
