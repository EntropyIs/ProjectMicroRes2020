#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>
#include <Entropy/Math/Transform3D.h>
#include <Entropy/Math/Vec2.h>
#include <Entropy/Graphics/Shader.h>

#include <vector>

#include "SpriteRenderer.h"
#include "Level.h"
#include "GameObject.h"

class StateGame : public Entropy::GameState
{
private:
	Entropy::Math::Mat4 Projection;

	Entropy::Math::Vec2 spriteIndex;
	Entropy::Math::Vec2 spritePos;
	GameObject player;
	Entropy::Math::Vec2 playerVelocity;

	float accel = 60.0f;
	float maxVel = 30.0f;
	float maxAngle = 21.21f;

	SpriteRenderer renderer;

	bool pause;

	Level level;

public:
	StateGame();

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};