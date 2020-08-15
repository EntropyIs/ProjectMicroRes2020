#include "StateIntro.h"

#include "ResourceManager.h"

using namespace Entropy;

StateIntro::StateIntro() : GameState("Intro", 1) {}

bool StateIntro::init()
{
    animRenderer = AnimationRenderer("entropy_logo", 12, 0, 4);
    animRenderer.playAnimationOnce();
    return true;
}

void StateIntro::input(Entropy::Graphics::Window& window) {}

void StateIntro::render()
{
    animRenderer.Draw(renderer, Math::Vec2(32, 32));
}

GameState* StateIntro::update(GameState* gameState)
{
    animRenderer.Update();
    if (animRenderer.isComplete())
        return connectedStates[0];
    return this;
}
