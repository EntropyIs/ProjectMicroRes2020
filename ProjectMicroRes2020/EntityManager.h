#pragma once

#include "LevelManager.h"
#include "Player.h"
#include "PlayerWeapon.h"
#include "HotdogWeapon.h"

class EntityManager
{
public:
	static LevelManager levelManager;
	static Player player;
	static PlayerWeapon playerWeapon;
	static HotdogWeapon hotdogWeapon;

	static Level& getLevel();
	static void setLevel(std::string levelName);

	static Player& getPlayer();
	static void setPlayer(Player playerObject);

	static PlayerWeapon& getPlayerWeapon();
	static void setPlayerWeapon(PlayerWeapon weapon);

	static HotdogWeapon& getHotdogWeapon();
	static void setHotdogWeapon(HotdogWeapon weapon);

	static void setLevelManager(const char* levelList);
};