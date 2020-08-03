#pragma once

#include <string>
#include <vector>

#include "SpriteRenderer.h"

struct Tile
{
	unsigned int X, Y, TX, TY;
	std::string Tileset;
	bool Passable;
	Tile(unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable) :
		X(x), Y(y), Tileset(tileset), TX(tX), TY(tY), Passable(passable) {};
};

class Level
{
private:
	std::vector<Tile> tiles;

	SpriteRenderer renderer;

public:
	Level(const char* path);

	void Draw();
};