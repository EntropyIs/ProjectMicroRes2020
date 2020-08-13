#pragma once

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>
#include <Entropy/Timing/Clock.h>

#include <map>
#include <string>

struct SpriteData {
	unsigned int num_rows;
	unsigned int num_cols;
	unsigned int cel_width;
	unsigned int cel_height;
	SpriteData(unsigned int num_rows, unsigned int num_cols, unsigned int cel_width, unsigned int cel_height) :num_rows(num_rows), num_cols(num_cols), cel_width(cel_width), cel_height(cel_height) {};
	SpriteData() : num_rows(1), num_cols(1), cel_width(8), cel_height(8) {};
};

class ResourceManager
{
public:
	static std::map<std::string, Entropy::Graphics::Shader> Shaders;
	static std::map<std::string, Entropy::Graphics::Texture> Textures;
	static std::map<std::string, SpriteData> SpriteSizeData;
	
	static Entropy::Timing::Clock MainClock;

	static bool loadData(const char* path);

	static Entropy::Graphics::Shader& loadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometaryShaderPath, std::string name);
	static Entropy::Graphics::Shader& getShader(std::string name);

	static Entropy::Graphics::Texture& loadTexture(const char* path, const char* type, std::string name);
	static Entropy::Graphics::Texture& getTexture(std::string name);

	static SpriteData& setSpriteSizeData(SpriteData data, std::string name);
	static SpriteData& getSpriteSizeData(std::string name);

	static bool initClock();
	static void pollClock();
	static float getTimeElapsed();
};