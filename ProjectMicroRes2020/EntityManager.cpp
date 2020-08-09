#include "EntityManager.h"

LevelManager EntityManager::levelManager;

Level& EntityManager::getLevel()
{
    return levelManager.getLevel();
}

void EntityManager::setLevel(std::string levelName)
{
    levelManager.setLevel(levelName);
}

Player& EntityManager::getPlayer()
{
    return player;
}

void EntityManager::setPlayer(Player playerObject)
{
    player = playerObject;
}

PlayerWeapon& EntityManager::getPlayerWeapon()
{
    return playerWeapon;
}

void EntityManager::setPlayerWeapon(PlayerWeapon weapon)
{
    playerWeapon = weapon;
}

void EntityManager::setLevelManager(const char* levelList)
{
    levelManager = LevelManager(levelList);
}
