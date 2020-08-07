#include "Level.h"

#include "ResourceManager.h"
#include "Slime.h"

#include <fstream>
#include <sstream>

#include <exception>

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

		if (lineComp[0] == "tile") // Pharse Tile
		{
			if (lineComp.size() == 10) // Warp Zone
				tiles.push_back(Tile(name + "[" + lineComp[1] + "," + lineComp[2] + "]",std::stoi(lineComp[1]), std::stoi(lineComp[2]), lineComp[3],
					std::stoi(lineComp[4]), std::stoi(lineComp[5]), std::stoi(lineComp[6]) == 1, 
					lineComp[7].c_str(), std::stoi(lineComp[8]), std::stoi(lineComp[9])));
			else if (lineComp.size() == 7) // Standard Tile
				tiles.push_back(Tile(name + "[" + lineComp[1] + "," + lineComp[2] + "]", std::stoi(lineComp[1]), std::stoi(lineComp[2]), lineComp[3],
					std::stoi(lineComp[4]), std::stoi(lineComp[5]), std::stoi(lineComp[6]) == 1));
		}
		else if (lineComp[0] == "entity") // Pharse Enemys
		{
			if (lineComp[1] == "enemy")
			{
				if (lineComp[2] == "slime") // Pharse slime enemy
				{
					if(lineComp.size() == 5) // default slime with position
						entities.push_back(new Slime(name + "_slime[" + lineComp[3] + "," + lineComp[4] + "]", 
							Math::Vec2(std::stof(lineComp[3]), std::stof(lineComp[4]))));
					else if (lineComp.size() == 8) // slime with position & recoloring
						entities.push_back(new Slime(name + "_slime[" + lineComp[3] + "," + lineComp[4] + "]", 
							Math::Vec2(std::stof(lineComp[3]), std::stof(lineComp[4])), 
							Math::Vec3(std::stof(lineComp[5]), std::stof(lineComp[6]), std::stof(lineComp[7]))));
				}
			}
		}
	}

	// build colliders list
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (!tiles[i].Passable || tiles[i].Link) // TODO: Add other colidable conditions
			colliders.push_back(tiles[i].getID());

	for (unsigned int i = 0; i < entities.size(); i++)
		colliders.push_back(entities[i]->getID());
}

std::vector<std::string> Level::getColliders()
{
	return colliders;
}

BoxCollider& Level::getCollider(std::string object)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (tiles[i].getID() == object)
			return tiles[i].collider;

	for (unsigned int i = 0; i < entities.size(); i++)
		if (entities[i]->getID() == object)
			return entities[i]->getCollider();

	std::string errString = "Object not found," + object;
	throw std::exception(errString.c_str());
}

Tile& Level::getTile(std::string object)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (tiles[i].getID() == object)
			return tiles[i];
	std::string errString = "Object not Tile," + object;
	throw std::exception(errString.c_str());
}

GameObject& Level::getEntity(std::string object)
{
	for (unsigned int i = 0; i < entities.size(); i++)
		if (entities[i]->getID() == object)
			return *entities[i];
	std::string errString = "Object not Entity," + object;
	throw std::exception(errString.c_str());
}

bool Level::isWall(std::string object)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (tiles[i].getID() == object)
			if(!tiles[i].Passable)
			return true;
	return false;
}

bool Level::isLink(std::string object)
{
	for (unsigned int i = 0; i < tiles.size(); i++)
		if (tiles[i].getID() == object)
			if (tiles[i].Link)
				return true;
	return false;
}

bool Level::isEntity(std::string object)
{
	for (unsigned int i = 0; i < entities.size(); i++)
		if (entities[i]->getID() == object)
			return true;
	return false;
}

std::string Level::getName()
{
	return name;
}

void Level::Draw(SpriteRenderer& renderer)
{
#ifdef _ShowCollider
	for (unsigned int i = 0; i < tiles.size(); i++) // Draw Each Collider Hitbox
	{
		tiles[i].collider.draw();
	}
#endif // _ShowCollider

	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities[i]->Draw(renderer);
	}

	Graphics::Texture texture = ResourceManager::getTexture(tiles[0].Tileset);
	
	for (unsigned int i = 0; i < tiles.size(); i++) // Render background tiles
	{
		SpriteData spriteData = ResourceManager::getSpriteSizeData(tiles[i].Tileset);
		renderer.Draw(Math::Vec2(
			(tiles[i].X * spriteData.cel_width) + spriteData.cel_width / 2.0f,
			(tiles[i].Y * spriteData.cel_height) + spriteData.cel_height / 2.0f),
			ResourceManager::getTexture(tiles[i].Tileset), Math::Vec2((float)tiles[i].TX, (float)tiles[i].TY), spriteData);
	}
}

void Level::Update()
{
	for (unsigned int i = 0; i < entities.size(); i++)
	{
		entities[i]->Update();
	}
}

Tile::Tile(std::string id, unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable) :
	id(id), X(x), Y(y), Tileset(tileset), TX(tX), TY(tY), Passable(passable), Link(false), LinkedLevel(), DX(0), DY(0)
{
	SpriteData spriteData = ResourceManager::getSpriteSizeData(tileset);
	collider = BoxCollider(
		Math::Vec2(
			(float)(x * spriteData.cel_width) + spriteData.cel_width / 2.0f,
			(float)(y * spriteData.cel_width) + spriteData.cel_width / 2.0f),
		Math::Vec2((float)spriteData.cel_width, (float)spriteData.cel_width),
		Math::Vec2((float)spriteData.cel_width / 2, (float)spriteData.cel_width / 2));
}

Tile::Tile(std::string id, unsigned int x, unsigned int y, std::string tileset, unsigned int tX, unsigned int tY, bool passable, const char* linkedLevel, unsigned int dX, unsigned int dY) :
	id(id), X(x), Y(y), Tileset(tileset), TX(tX), TY(tY), Passable(passable), Link(true), LinkedLevel(linkedLevel), DX(dX), DY(dY)
{
	SpriteData spriteData = ResourceManager::getSpriteSizeData(tileset);
	collider = BoxCollider(
		Math::Vec2(
			(float)(x * spriteData.cel_width) + spriteData.cel_width / 2.0f,
			(float)(y * spriteData.cel_width) + spriteData.cel_width / 2.0f),
		Math::Vec2((float)spriteData.cel_width, (float)spriteData.cel_width),
		Math::Vec2((float)(spriteData.cel_width / 2.0f), (float)(spriteData.cel_width / 2.0f)));
}

std::string Tile::getID()
{
	return id;
}
