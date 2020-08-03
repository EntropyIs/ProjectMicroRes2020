#include "ResourceManager.h"

using namespace Entropy;

std::map<std::string, Graphics::Shader> ResourceManager::Shaders;
std::map<std::string, Graphics::Texture> ResourceManager::Textures;
std::map<std::string, SpriteData> ResourceManager::SpriteSizeData;

Entropy::Timing::Clock ResourceManager::MainClock;

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
