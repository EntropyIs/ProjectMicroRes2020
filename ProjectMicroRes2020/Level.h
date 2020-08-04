#pragma once

#include <Entropy/Math/Vec2.h>

#include <string>
#include <vector>

#include "SpriteRenderer.h"

struct Tile
{
	Entropy::Math::Vec2 box_size, box_offset;
	unsigned int X, Y, TX, TY;
	std::string Tileset;
	bool Passable;
	Tile(unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable);
};

class Level
{
private:
	std::vector<Tile> tiles;
	std::vector<Tile> colliders;

	SpriteRenderer renderer;

public:
	Level(const char* path);

	std::vector<Tile> getColliders();

	void Draw();
};