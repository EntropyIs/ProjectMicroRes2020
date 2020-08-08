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

void EntityManager::setLevelManager(const char* levelList)
{
    levelManager = LevelManager(levelList);
}
