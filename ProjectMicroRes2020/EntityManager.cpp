#include "EntityManager.h"

LevelManager EntityManager::levelManager;
Player EntityManager::player;
PlayerWeapon EntityManager::playerWeapon;
std::vector<HotdogWeapon> EntityManager::hotdogWeapons;

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

HotdogWeapon& EntityManager::getHotdogWeapon(unsigned int index)
{
    return hotdogWeapons[index];
}

HotdogWeapon& EntityManager::setHotdogWeapon(HotdogWeapon weapon)
{
    for (int i = 0; i < hotdogWeapons.size(); i++)
        if (!hotdogWeapons[i].isAlive())
            return hotdogWeapons[i] = weapon;
    hotdogWeapons.push_back(weapon);
    return hotdogWeapons[hotdogWeapons.size() - 1];
}

void EntityManager::updateHotdogWeapon()
{
    for (int i = 0; i < hotdogWeapons.size(); i++)
        hotdogWeapons[i].Update();
}

bool EntityManager::detectHotdogWeapon(BoxCollider& other, unsigned int& index)
{
    for (index = 0; index < hotdogWeapons.size(); index++)
        if (hotdogWeapons[index].detectCollion(other))
            return true;
    return false;
}

void EntityManager::drawHotdogWeapon(SpriteRenderer& renderer)
{
    for (unsigned int i = 0; i < hotdogWeapons.size(); i++)
        hotdogWeapons[i].Draw(renderer);
}

void EntityManager::killHotdogWeapons()
{
    for (unsigned int i = 0; i < hotdogWeapons.size(); i++)
        hotdogWeapons[i].kill();
}

void EntityManager::setLevelManager(const char* levelList)
{
    levelManager = LevelManager(levelList);
}
