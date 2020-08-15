#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>
#include <Entropy/Math/Vec2.h>

#include <vector>
#include <string>

#include "SpriteRenderer.h"
#include "AnimationRenderer.h"

class StateIntro : public Entropy::GameState
{
private:
	SpriteRenderer renderer;
	AnimationRenderer animRenderer;

public:
	StateIntro();

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};