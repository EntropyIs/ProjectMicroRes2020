#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>
#include <Entropy/Math/Vec2.h>

#include "SpriteRenderer.h"

class StateCredits : public Entropy::GameState
{
private:
	SpriteRenderer renderer;

	bool key_down;
	bool execute_selection;
public:
	StateCredits() : GameState("Credits", 1) {
		init();
	};

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};