#pragma once

#include "LevelManager.h"

class EntityManager
{
public:
	static LevelManager levelManager;

	static Level& getLevel();
	static void setLevel(std::string levelName);

	static void setLevelManager(const char* levelList);
};