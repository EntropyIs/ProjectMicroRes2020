#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>
#include <Entropy/Math/Transform3D.h>
#include <Entropy/Math/Vec2.h>
#include <Entropy/Graphics/Shader.h>

#include <vector>

#include "SpriteRenderer.h"

class StateGame : public Entropy::GameState
{
private:
	Entropy::Math::Mat4 Projection;

	Entropy::Math::Vec2 spriteIndex;
	Entropy::Math::Vec2 spritePos;
	Entropy::Math::Vec2 spriteVeclocity;

	float accel = 60.0f;
	float maxVel = 30.0f;

	SpriteRenderer renderer;

	bool pause;

public:
	StateGame();

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};