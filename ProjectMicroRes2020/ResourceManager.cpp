#include "ResourceManager.h"

using namespace Entropy;

std::map<std::string, Graphics::Shader> ResourceManager::Shaders;
std::map<std::string, Graphics::Texture> ResourceManager::Textures;

Graphics::Shader& ResourceManager::loadShader(const char* vertexShaderPath, const char* fragmentShaderPath, const char* geometaryShaderPath, std::string name)
{
    Shaders[name] = Graphics::Shader(vertexShaderPath, fragmentShaderPath, geometaryShaderPath);
    return Shaders[name];
}

Entropy::Graphics::Shader& ResourceManager::getShader(std::string name)
{
    return Shaders[name];
}

Entropy::Graphics::Texture& ResourceManager::loadTexture(const char* path, const char* type, bool alpha, std::string name)
{
    Textures[name] = Graphics::LoadTexture::LoadFromFile(path, type);
    return Textures[name];
}

Entropy::Graphics::Texture& ResourceManager::getTexture(std::string name)
{
    return Textures[name];
}
