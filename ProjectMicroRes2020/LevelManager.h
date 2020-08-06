#pragma once

#include "Level.h"

#include <vector>

class LevelManager
{
private:
	std::vector<Level> levels;

	unsigned int currentLevel;

public:
	LevelManager() : currentLevel(0) {};
	LevelManager(const char* levelList);

	void setLevel(std::string levelName);

	Level& getLevel();
};