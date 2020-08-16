#pragma once

#include "LevelManager.h"
#include "Player.h"
#include "PlayerWeapon.h"
#include "HotdogWeapon.h"

#include <vector>

class EntityManager
{
public:
	static LevelManager levelManager;
	static Player player;
	static PlayerWeapon playerWeapon;
	static std::vector<HotdogWeapon> hotdogWeapons;

	static Level& getLevel();
	static void setLevel(std::string levelName);

	static Player& getPlayer();
	static void setPlayer(Player playerObject);

	static PlayerWeapon& getPlayerWeapon();
	static void setPlayerWeapon(PlayerWeapon weapon);

	static HotdogWeapon& getHotdogWeapon(unsigned int index);
	static HotdogWeapon& setHotdogWeapon(HotdogWeapon weapon);
	static void updateHotdogWeapon();
	static bool detectHotdogWeapon(BoxCollider& other, unsigned int& index);
	static void drawHotdogWeapon(SpriteRenderer& renderer);

	static void setLevelManager(const char* levelList);
};