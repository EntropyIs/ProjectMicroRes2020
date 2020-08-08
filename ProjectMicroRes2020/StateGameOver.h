#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>

#include "SpriteRenderer.h"

class StateGameOver : public Entropy::GameState
{
private:
	SpriteRenderer renderer;

	bool key_down;
	bool execute_selection;

public:
	StateGameOver() : GameState("Game Over", 1) {
		init();
	};

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};