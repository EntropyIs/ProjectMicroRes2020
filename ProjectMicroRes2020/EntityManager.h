#pragma once

#include "LevelManager.h"
#include "Player.h"
#include "PlayerWeapon.h"

class EntityManager
{
public:
	static LevelManager levelManager;
	static Player player;
	static PlayerWeapon playerWeapon;

	static Level& getLevel();
	static void setLevel(std::string levelName);

	static Player& getPlayer();
	static void setPlayer(Player playerObject);

	static PlayerWeapon& getPlayerWeapon();
	static void setPlayerWeapon(PlayerWeapon weapon);

	static void setLevelManager(const char* levelList);
};