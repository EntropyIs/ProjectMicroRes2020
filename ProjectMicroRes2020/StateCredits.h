#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>

class StateCredits : public Entropy::GameState
{
public:
	StateCredits() : GameState("Credits", 1) {};

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};