#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>
#include <Entropy/Math/Transform3D.h>

class StateGame : public Entropy::GameState
{
private:
	Entropy::Math::Mat4 Projection;

public:
	StateGame();

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};