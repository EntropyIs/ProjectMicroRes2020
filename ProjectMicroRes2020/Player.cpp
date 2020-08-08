#include "Player.h"

#include "EntityManager.h"
#include "ResourceManager.h"

using namespace Entropy;

Player::Player(std::string id, const char* spriteName, Entropy::Math::Vec2 spriteIndex, Entropy::Math::Vec2 position,
    Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) :
    GameObject(id, spriteName, spriteIndex, position, boxSize, boxOffset, textureOffset) 
{
    health = 3;
}

void Player::Update()
{
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
            else if (EntityManager::getLevel().isEntity(object)) // Entity (collectable or enemy)
            {
                undoMovement(); // Step Back
                health--;
                //TODO: Invonerable Timer
                break;
            }
        }

        if (health == 0)
            alive = false;
    }
}
