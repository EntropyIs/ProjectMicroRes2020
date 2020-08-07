#pragma once

#include <Entropy/Math/Vec2.h>

#include <string>
#include <vector>

#include "SpriteRenderer.h"
#include "Collider.h"
#include "GameObject.h"

struct Tile
{
	std::string id;
	BoxCollider collider;
	unsigned int X, Y, TX, TY, DX, DY;
	std::string Tileset;
	bool Passable;
	bool Link;
	std::string LinkedLevel;
	Tile(std::string id, unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable);
	Tile(std::string id, unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable, const char* linkedLevel, unsigned int dX, unsigned int dY);
	std::string getID();
};

class Level
{
private:
	std::string name;
	std::vector<Tile> tiles;
	std::vector<std::string> colliders;
	std::vector<GameObject> entities;

public:
	Level(const char* path, std::string name);
	Level() {};

	std::vector<std::string> getColliders();
	std::string getName();

	BoxCollider& getCollider(std::string object);

	Tile& getTile(std::string object);
	GameObject& getEntity(std::string object);

	bool isWall(std::string object);
	bool isLink(std::string object);
	bool isEntity(std::string object);

	void Draw(SpriteRenderer& renderer);

	void Update();
};