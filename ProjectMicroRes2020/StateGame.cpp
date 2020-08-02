#include "StateGame.h"

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>

#include "ResourceManager.h"

using namespace Entropy;

StateGame::StateGame() : GameState("Game", 2)
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
}

bool StateGame::init()
{
    // Configure Entities
    spriteIndex = Math::Vec2(8.0f, 0.0f);
    spritePos = Math::Vec2(32.0f, 32.0f);

    // Configure shaders
    ResourceManager::getShader("spriteShader").use();
    ResourceManager::getShader("spriteShader").setMat4("projection", Projection);
    ResourceManager::getShader("spriteShader").setInt("spriteSheet", 0);

    return false;
}

void StateGame::input(Graphics::Window& window)
{
}

void StateGame::render()
{
    renderer.Draw(spritePos, ResourceManager::getTexture("testSprite"), spriteIndex, ResourceManager::getSpriteSizeData("testSprite"), 16, 16);
}

GameState* StateGame::update(GameState* gameState)
{
    return gameState;
}
