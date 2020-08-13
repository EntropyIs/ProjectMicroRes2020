#include "EntityManager.h"

LevelManager EntityManager::levelManager;
Player EntityManager::player;
PlayerWeapon EntityManager::playerWeapon;

Level& EntityManager::getLevel()
{
    return levelManager.getLevel();
}

void EntityManager::setLevel(std::string levelName)
{
    levelManager.setLevel(levelName);
}

void EntityManager::nextLevel()
{
    levelManager.nextLevel();
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
