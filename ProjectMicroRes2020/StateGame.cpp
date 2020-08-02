#include "StateGame.h"

#include <Entropy/Graphics/Mesh.h>
#include <Entropy/Graphics/Model/Image.h>

using namespace Entropy;

StateGame::StateGame() : GameState("Game", 2), spriteShader("Assets/Shaders/vBaseShader.glsl", "Assets/Shaders/fBaseShader.glsl")
{
    Projection = Math::Ortho(0.0f, 64.0f, 64.0f, 0.0f, -1.0f, 1.0f);
}

bool StateGame::init()
{
    // Load Assets
    spriteSheets.push_back(Graphics::LoadTexture::LoadFromImageFile("Assets/TestSprite.jpg", "sprite_sheet"));
    spriteSheetData.push_back(Math::Vec2(10.0f, 16.0f));

    // Configure Entities
    spriteIndex = Math::Vec2(0.0f, 0.0f);
    spritePos = Math::Vec2(32.0f, 32.0f);

    // Configure shaders
    spriteShader.use();
    spriteShader.setMat4("projection", Projection);
    spriteShader.setInt("spriteSheet", 0);

    return false;
}

void StateGame::input(Graphics::Window& window)
{
}

void StateGame::render()
{
    renderer.Draw(spriteShader, spritePos, spriteSheets[0], spriteIndex, spriteSheetData[0], 16, 16);
}

GameState* StateGame::update(GameState* gameState)
{
    spriteIndex.X += 1;
    if (spriteIndex.X > 9)
        spriteIndex.X = 0;
    return gameState;
}
