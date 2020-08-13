#include "Player.h"

#include "EntityManager.h"
#include "ResourceManager.h"

using namespace Entropy;

Player::Player(const char* spriteName, unsigned int row, Entropy::Math::Vec2 position,
    Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) :
    AnimatedGameObject("player", spriteName, 2, row, 6, position, boxSize, boxOffset, textureOffset)
{
    health = 6;
    timer = 0.0f;
    vulnerable = true;
    hurting = false;
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
                break;
            case RIGHT:
                animationRenderer.setRowNumber(21);
                break;
            case DOWNRIGHT:
                animationRenderer.setRowNumber(22);
                break;
            case DOWN:
                animationRenderer.setRowNumber(23);
                break;
            case DOWNLEFT:
                animationRenderer.setRowNumber(16);
                break;
            case LEFT:
                animationRenderer.setRowNumber(17);
                break;
            case UPLEFT:
                animationRenderer.setRowNumber(18);
                break;
            case UP:
                animationRenderer.setRowNumber(19);
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
                lastDirection = Direction::UPLEFT;
            }
            else if (getVelocity().Y > 0.0f && getVelocity().X > 0.0f) // Up & Right
            {
                animationRenderer.setRowNumber(12);
                lastDirection = Direction::UPRIGHT;
            }
            else if (getVelocity().Y < 0.0f && getVelocity().X < 0.0f) // Down & Left
            {
                animationRenderer.setRowNumber(8);
                lastDirection = Direction::DOWNLEFT;
            }
            else if (getVelocity().Y < 0.0f && getVelocity().X > 0.0f) // Down & Right
            {
                animationRenderer.setRowNumber(14);
                lastDirection = Direction::DOWNRIGHT;
            }
            else if (getVelocity().Y > 0.0f) // Up
            {
                animationRenderer.setRowNumber(11);
                lastDirection = Direction::UP;
            }
            else if (getVelocity().Y < 0.0f) // Down
            {
                animationRenderer.setRowNumber(15);
                lastDirection = Direction::DOWN;
            }
            else if (getVelocity().X > 0.0f) // Right
            {
                animationRenderer.setRowNumber(13);
                lastDirection = Direction::RIGHT;
            }
            else if (getVelocity().X < 0.0f) // Left
            {
                animationRenderer.setRowNumber(9);
                lastDirection = Direction::LEFT;
            }
            else // Idle
            {
                animationRenderer.stopAnimation();
                switch (lastDirection)
                {
                case UPRIGHT:
                    animationRenderer.setRowNumber(4);
                    break;
                case RIGHT:
                    animationRenderer.setRowNumber(5);
                    break;
                case DOWNRIGHT:
                    animationRenderer.setRowNumber(6);
                    break;
                case DOWN:
                    animationRenderer.setRowNumber(7);
                    break;
                case DOWNLEFT:
                    animationRenderer.setRowNumber(0);
                    break;
                case LEFT:
                    animationRenderer.setRowNumber(1);
                    break;
                case UPLEFT:
                    animationRenderer.setRowNumber(2);
                    break;
                case UP:
                    animationRenderer.setRowNumber(3);
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
                    hurting = true;
                    hurtAnim = 2;
                    animationRenderer.playAnimationOnce();
                    timer = 0;

                    switch (lastDirection)
                    {
                    case UPRIGHT:
                        animationRenderer.setRowNumber(28);
                        break;
                    case RIGHT:
                        animationRenderer.setRowNumber(29);
                        break;
                    case DOWNRIGHT:
                        animationRenderer.setRowNumber(30);
                        break;
                    case DOWN:
                        animationRenderer.setRowNumber(31);
                        break;
                    case DOWNLEFT:
                        animationRenderer.setRowNumber(24);
                        break;
                    case LEFT:
                        animationRenderer.setRowNumber(25);
                        break;
                    case UPLEFT:
                        animationRenderer.setRowNumber(26);
                        break;
                    case UP:
                        animationRenderer.setRowNumber(27);
                        break;
                    default:
                        break;
                    }

                    break;
                }
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
