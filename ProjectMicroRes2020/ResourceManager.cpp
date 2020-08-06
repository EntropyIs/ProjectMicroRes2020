#include "ResourceManager.h"

#include <fstream>
#include <sstream>
#include <string>

using namespace Entropy;

std::map<std::string, Graphics::Shader> ResourceManager::Shaders;
std::map<std::string, Graphics::Texture> ResourceManager::Textures;
std::map<std::string, SpriteData> ResourceManager::SpriteSizeData;

Entropy::Timing::Clock ResourceManager::MainClock;

bool ResourceManager::loadData(const char* path)
{
	std::string dataPath = path;
	std::string directory = dataPath.substr(0, dataPath.find_last_of("/"));

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

	// Pharse File
	for (unsigned int i = 0; i < lines.size(); i++)
	{
		std::stringstream lineStream(lines[i]);
		std::vector<std::string> lineComp;
		std::string lineToken;
		while (std::getline(lineStream, lineToken, ','))
			if (!lineToken.empty())
				lineComp.push_back(lineToken);

		if (lineComp[0] == "shader")
		{
			// name, vertex_path, fragment_path, [geomerary_path]
			if (lineComp.size() == 5)
				loadShader((directory + "/" + lineComp[2]).c_str(), (directory + "/" + lineComp[3]).c_str(), (directory + "/" + lineComp[4]).c_str(), lineComp[1]);
			else
				loadShader((directory + "/" + lineComp[2]).c_str(), (directory + "/" + lineComp[3]).c_str(), NULL, lineComp[1]);
		}
		else if (lineComp[0] == "sprite") // texture with data
		{
			// name, texture_path, num_rows, num_cols, cel_width, cel_height
			loadTexture((directory + "/" + lineComp[2]).c_str(), "sprite_sheet", lineComp[1]);
			setSpriteSizeData(SpriteData(std::stoi(lineComp[3]), std::stoi(lineComp[4]), std::stoi(lineComp[5]), std::stoi(lineComp[6])), lineComp[1]);
		}
	}

	// return status of clock.
    return initClock();
}

Graphics::Shader& ResourceManager::loadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometaryShaderPath, std::string name)
{
    Shaders[name] = Graphics::Shader(vertexShaderPath, fragmentShaderPath, geometaryShaderPath);
    return Shaders[name];
}

Entropy::Graphics::Shader& ResourceManager::getShader(std::string name)
{
    return Shaders[name];
}

Entropy::Graphics::Texture& ResourceManager::loadTexture(const char* path, const char* type, std::string name)
{
    Textures[name] = Graphics::LoadTexture::LoadFromImageFile(path, type, false);
    return Textures[name];
}

Entropy::Graphics::Texture& ResourceManager::getTexture(std::string name)
{
    return Textures[name];
}

SpriteData& ResourceManager::setSpriteSizeData(SpriteData data, std::string name)
{
    SpriteSizeData[name] = data;
    return SpriteSizeData[name];
}

SpriteData& ResourceManager::getSpriteSizeData(std::string name)
{
    return SpriteSizeData[name];
}

bool ResourceManager::initClock()
{
    return MainClock.initialize();
}

void ResourceManager::pollClock()
{
    MainClock.poll();
}

float ResourceManager::getTimeElapsed()
{
    return MainClock.timeElapsed();
}
