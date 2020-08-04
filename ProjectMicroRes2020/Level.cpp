#include "Level.h"

#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace Entropy;

Level::Level(const char* path, std::string name) : name(name)
{
	// Read contents of file into lines vector
	std::ifstream inFile;
	inFile.open(path, std::ios_base::in);
	if (!inFile.is_open())
	{
		std::string error = "Could not open file: ";
		error.append(path);
		throw std::exception(error.c_str());
	}

	std::vector<std::string> lines;
	while (inFile.good() && inFile.peek() != EOF)
	{
		std::string line;
		std::getline(inFile, line);
		if (!line.empty())
		{
			std::string::iterator end_pos = std::remove(line.begin(), line.end(), ' ');
			line.erase(end_pos, line.end());
			lines.push_back(line);
		}
	}
	inFile.close();

	// Pharse lines
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		std::stringstream lineStream(lines[i]);
		std::vector<std::string> lineComp;
		std::string lineToken;
		while (std::getline(lineStream, lineToken, ','))
			if (!lineToken.empty())
				lineComp.push_back(lineToken);

		if (lineComp.size() == 9) // Warp Zone
			tiles.push_back(Tile(std::stoi(lineComp[0]), std::stoi(lineComp[1]), lineComp[2],
				std::stoi(lineComp[3]), std::stoi(lineComp[4]), std::stoi(lineComp[5]) == 1, lineComp[6].c_str(), std::stoi(lineComp[7]), std::stoi(lineComp[8])));
		else
			tiles.push_back(Tile(std::stoi(lineComp[0]), std::stoi(lineComp[1]), lineComp[2],
				std::stoi(lineComp[3]), std::stoi(lineComp[4]), std::stoi(lineComp[5]) == 1));
	}

	// build colliders list
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (!tiles[i].Passable || tiles[i].Link) // TODO: Add other colidable conditions
			colliders.push_back(tiles[i]);
}

std::vector<Tile> Level::getColliders()
{
	return colliders;
}

std::string Level::getName()
{
	return name;
}

void Level::Draw(SpriteRenderer& renderer)
{
	Graphics::Texture texture = ResourceManager::getTexture(tiles[0].Tileset);
	
	for (unsigned int i = 0; i < tiles.size(); i++)
	{
		SpriteData spriteData = ResourceManager::getSpriteSizeData(tiles[i].Tileset);
		renderer.Draw(Math::Vec2(
			(tiles[i].X * spriteData.cel_width) + spriteData.cel_width / 2.0f,
			(tiles[i].Y * spriteData.cel_height) + spriteData.cel_height / 2.0f),
			ResourceManager::getTexture(tiles[i].Tileset), Math::Vec2((float)tiles[i].TX, (float)tiles[i].TY), spriteData);
	}
		
}

Tile::Tile(unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable) :
	X(x), Y(y), Tileset(tileset), TX(tX), TY(tY), Passable(passable), Link(false), LinkedLevel()
{
	SpriteData spriteData = ResourceManager::getSpriteSizeData(tileset);
	box_size = Math::Vec2((float)spriteData.cel_width, (float)spriteData.cel_width);
	box_offset = Math::Vec2((float)spriteData.cel_width/2, (float)spriteData.cel_width/2);
}

Tile::Tile(unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable, const char* linkedLevel, unsigned int dX, unsigned int dY) :
	X(x), Y(y), Tileset(tileset), TX(tX), TY(tY), Passable(passable), Link(true), LinkedLevel(linkedLevel), DX(dX), DY(dY)
{
	SpriteData spriteData = ResourceManager::getSpriteSizeData(tileset);
	box_size = Math::Vec2((float)spriteData.cel_width, (float)spriteData.cel_width);
	box_offset = Math::Vec2((float)spriteData.cel_width / 2, (float)spriteData.cel_width / 2);
}
