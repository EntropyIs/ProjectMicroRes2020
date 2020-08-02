#include "Level.h"

#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace Entropy;

Level::Level(const char* path, unsigned int tileWidth, unsigned int tileHeight) :
	tileWidth(tileWidth), tileHeight(tileHeight)
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

		tiles.push_back(Tile(std::stoi(lineComp[0]), std::stoi(lineComp[1]), lineComp[2],
			std::stoi(lineComp[3]), std::stoi(lineComp[4]), std::stoi(lineComp[5]) == 1));
	}
}

void Level::Draw()
{
	Graphics::Texture texture = ResourceManager::getTexture(tiles[0].Tileset);
	for (unsigned int i = 0; i < tiles.size(); i++)
		renderer.Draw(Math::Vec2((tiles[i].X * tileWidth) + tileWidth/2.0f, (tiles[i].Y * tileHeight) + tileWidth / 2.0f),
			ResourceManager::getTexture(tiles[i].Tileset), Math::Vec2(tiles[i].TX, tiles[i].TY), 
			ResourceManager::getSpriteSizeData(tiles[i].Tileset), tileWidth, tileHeight);
}
