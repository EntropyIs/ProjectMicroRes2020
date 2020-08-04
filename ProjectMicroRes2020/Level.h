#pragma once

#include <Entropy/Math/Vec2.h>

#include <string>
#include <vector>

#include "SpriteRenderer.h"

struct Tile
{
	Entropy::Math::Vec2 box_size, box_offset;
	unsigned int X, Y, TX, TY, DX, DY;
	std::string Tileset;
	bool Passable;
	bool Link;
	std::string LinkedLevel;
	Tile(unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable);
	Tile(unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable, const char* linkedLevel, unsigned int dX, unsigned int dY);
};

class Level
{
private:
	std::string name;
	std::vector<Tile> tiles;
	std::vector<Tile> colliders;

public:
	Level(const char* path, std::string name);
	Level() {};

	std::vector<Tile> getColliders();
	std::string getName();

	void Draw(SpriteRenderer& renderer);
};