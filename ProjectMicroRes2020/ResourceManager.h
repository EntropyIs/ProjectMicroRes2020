#pragma once

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>

#include <map>
#include <string>

class ResourceManager
{
public:
	static std::map<std::string, Entropy::Graphics::Shader> Shaders;
	static std::map<std::string, Entropy::Graphics::Texture> Textures;
	static std::map<std::string, Entropy::Math::Vec2> SpriteSizeData;

	static Entropy::Graphics::Shader& loadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometaryShaderPath, std::string name);
	static Entropy::Graphics::Shader& getShader(std::string name);

	static Entropy::Graphics::Texture& loadTexture(const char* path, const char* type, bool alpha, std::string name);
	static Entropy::Graphics::Texture& getTexture(std::string name);

	static Entropy::Math::Vec2& setSpriteSizeData(Entropy::Math::Vec2 data, std::string name);
	static Entropy::Math::Vec2& getSpriteSizeData(std::string name);
};