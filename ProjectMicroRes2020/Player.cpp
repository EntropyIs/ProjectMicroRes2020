#include "Player.h"

#include "EntityManager.h"
#include "ResourceManager.h"

#include <iostream>

using namespace Entropy;

Player::Player(const char* spriteName, unsigned int row, Entropy::Math::Vec2 position,
    Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) :
    AnimatedGameObject("player", spriteName, 2, row, 6, position, boxSize, boxOffset, textureOffset)
{
    health = 6;
    timer = 0.0f;
    vulnerable = true;
    hurting = false;
    attacking = false;
    lastDirection = Direction::DOWN;
    hurtAnim = 0;
}

Direction Player::getLastDirection()
{
    return lastDirection;
}

void Player::setAttacking()
{
    attacking = true;
}

void Player::stop()
{
    setVelocity(Math::Vec2(0, 0));
}

void Player::Update()
{
    if (!hurting)
    {
        if (attacking)
        {
            switch (lastDirection)
            {
            case UPRIGHT:
                animationRenderer.setRowNumber(20);
                animationRenderer.setNumFrames(1);
                break;
            case RIGHT:
                animationRenderer.setRowNumber(21);
                animationRenderer.setNumFrames(1);
                break;
            case DOWNRIGHT:
                animationRenderer.setRowNumber(22);
                animationRenderer.setNumFrames(1);
                break;
            case DOWN:
                animationRenderer.setRowNumber(23);
                animationRenderer.setNumFrames(1);
                break;
            case DOWNLEFT:
                animationRenderer.setRowNumber(16);
                animationRenderer.setNumFrames(1);
                break;
            case LEFT:
                animationRenderer.setRowNumber(17);
                animationRenderer.setNumFrames(1);
                break;
            case UPLEFT:
                animationRenderer.setRowNumber(18);
                animationRenderer.setNumFrames(1);
                break;
            case UP:
                animationRenderer.setRowNumber(19);
                animationRenderer.setNumFrames(1);
                break;
            default:
                break;
            }
        }
        else
        {
            // Set Sprite Direction and Animate
            animationRenderer.playAnimation();
            if (getVelocity().Y > 0.0f && getVelocity().X < 0.0f) // Up & Left
            {
                animationRenderer.setRowNumber(10);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::UPLEFT;
            }
            else if (getVelocity().Y > 0.0f && getVelocity().X > 0.0f) // Up & Right
            {
                animationRenderer.setRowNumber(12);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::UPRIGHT;
            }
            else if (getVelocity().Y < 0.0f && getVelocity().X < 0.0f) // Down & Left
            {
                animationRenderer.setRowNumber(8);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::DOWNLEFT;
            }
            else if (getVelocity().Y < 0.0f && getVelocity().X > 0.0f) // Down & Right
            {
                animationRenderer.setRowNumber(14);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::DOWNRIGHT;
            }
            else if (getVelocity().Y > 0.0f) // Up
            {
                animationRenderer.setRowNumber(11);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::UP;
            }
            else if (getVelocity().Y < 0.0f) // Down
            {
                animationRenderer.setRowNumber(15);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::DOWN;
            }
            else if (getVelocity().X > 0.0f) // Right
            {
                animationRenderer.setRowNumber(13);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::RIGHT;
            }
            else if (getVelocity().X < 0.0f) // Left
            {
                animationRenderer.setRowNumber(9);
                animationRenderer.setNumFrames(2);
                lastDirection = Direction::LEFT;
            }
            else // Idle
            {
                animationRenderer.stopAnimation();
                switch (lastDirection)
                {
                case UPRIGHT:
                    animationRenderer.setRowNumber(4);
                    animationRenderer.setNumFrames(1);
                    break;
                case RIGHT:
                    animationRenderer.setRowNumber(5);
                    animationRenderer.setNumFrames(1);
                    break;
                case DOWNRIGHT:
                    animationRenderer.setRowNumber(6);
                    animationRenderer.setNumFrames(1);
                    break;
                case DOWN:
                    animationRenderer.setRowNumber(7);
                    animationRenderer.setNumFrames(1);
                    break;
                case DOWNLEFT:
                    animationRenderer.setRowNumber(0);
                    animationRenderer.setNumFrames(1);
                    break;
                case LEFT:
                    animationRenderer.setRowNumber(1);
                    animationRenderer.setNumFrames(1);
                    break;
                case UPLEFT:
                    animationRenderer.setRowNumber(2);
                    animationRenderer.setNumFrames(1);
                    break;
                case UP:
                    animationRenderer.setRowNumber(3);
                    animationRenderer.setNumFrames(1);
                    break;
                default:
                    break;
                }
            }
        }
    }
    animationRenderer.Update();

    // Move Character
    performMovement();

    // Get Collisions
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
#ifdef _DEBUG
                    std::cout << this->id << ", hit by: " << object << std::endl;
#endif // _DEBUG
                    ResourceManager::playAudio("sfx_player_hurt");
                    undoMovement(); // Step Back
                    health--;
                    vulnerable = false;
                    hurting = true;
                    hurtAnim = 2;
                    animationRenderer.playAnimationOnce();
                    timer = 0;

                    switch (lastDirection)
                    {
                    case UPRIGHT:
                        animationRenderer.setRowNumber(28);
                        animationRenderer.setNumFrames(2);
                        break;
                    case RIGHT:
                        animationRenderer.setRowNumber(29);
                        animationRenderer.setNumFrames(2);
                        break;
                    case DOWNRIGHT:
                        animationRenderer.setRowNumber(30);
                        animationRenderer.setNumFrames(2);
                        break;
                    case DOWN:
                        animationRenderer.setRowNumber(31);
                        animationRenderer.setNumFrames(2);
                        break;
                    case DOWNLEFT:
                        animationRenderer.setRowNumber(24);
                        animationRenderer.setNumFrames(2);
                        break;
                    case LEFT:
                        animationRenderer.setRowNumber(25);
                        animationRenderer.setNumFrames(2);
                        break;
                    case UPLEFT:
                        animationRenderer.setRowNumber(26);
                        animationRenderer.setNumFrames(2);
                        break;
                    case UP:
                        animationRenderer.setRowNumber(27);
                        animationRenderer.setNumFrames(2);
                        break;
                    default:
                        break;
                    }

                    break;
                }
            }
        }
    }

    unsigned int index;
    if (EntityManager::detectHotdogWeapon(collider, index) && vulnerable)
    {
#ifdef _DEBUG
        std::cout << this->id << ", hit by: HotdogWeapon" << std::endl;
#endif // _DEBUG
        EntityManager::getHotdogWeapon(index).kill();
        ResourceManager::playAudio("sfx_player_hurt");
        undoMovement(); // Step Back
        health--;
        vulnerable = false;
        hurting = true;
        hurtAnim = 2;
        animationRenderer.playAnimationOnce();
        timer = 0;

        switch (lastDirection)
        {
        case UPRIGHT:
            animationRenderer.setRowNumber(28);
            animationRenderer.setNumFrames(2);
            break;
        case RIGHT:
            animationRenderer.setRowNumber(29);
            animationRenderer.setNumFrames(2);
            break;
        case DOWNRIGHT:
            animationRenderer.setRowNumber(30);
            animationRenderer.setNumFrames(2);
            break;
        case DOWN:
            animationRenderer.setRowNumber(31);
            animationRenderer.setNumFrames(2);
            break;
        case DOWNLEFT:
            animationRenderer.setRowNumber(24);
            animationRenderer.setNumFrames(2);
            break;
        case LEFT:
            animationRenderer.setRowNumber(25);
            animationRenderer.setNumFrames(2);
            break;
        case UPLEFT:
            animationRenderer.setRowNumber(26);
            animationRenderer.setNumFrames(2);
            break;
        case UP:
            animationRenderer.setRowNumber(27);
            animationRenderer.setNumFrames(2);
            break;
        default:
            break;
        }
    }

    // Tickdown Hurt Animation
    if (hurting)
    {
        if (animationRenderer.isComplete() && hurtAnim == 0)
        {
            hurting = false;
        }
        else if (animationRenderer.isComplete())
        {
            hurtAnim--;
            animationRenderer.playAnimationOnce();
        }
    }

    // Check if still attacking;
    if (attacking)
        if (!EntityManager::getPlayerWeapon().isAlive())
            attacking = false;
           
    // Tickdown Invunralbility
    if (!vulnerable && !hurting)
    {
        float timeElapsed = ResourceManager::getTimeElapsed();
        timer += ResourceManager::getTimeElapsed();
        if (timer > invulnerable_time)
            vulnerable = true;
    }

    if (health == 0)
        alive = false;
}

void Player::Draw(SpriteRenderer& renderer)
{
    // draw hearts
    switch (health)
    {
    case 6:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    case 5:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(1.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    case 4:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    case 3:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(1.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    case 2:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(0.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    case 1:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(1.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    case 0:
        renderer.Draw(heartPosition + heartOffset + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition + heartOffset, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        renderer.Draw(heartPosition, ResourceManager::getTexture("heart_sprite"), Entropy::Math::Vec2(2.0f, 0.0f), ResourceManager::getSpriteSizeData("heart_sprite"));
        break;
    default:
        break;
    }

    // Draw Character
    AnimatedGameObject::Draw(renderer);
}
