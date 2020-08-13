#pragma once

#include <Entropy/GameState.h>
#include <Entropy/Graphics/Window.h>
#include <Entropy/Math/Transform3D.h>
#include <Entropy/Math/Vec2.h>
#include <Entropy/Graphics/Shader.h>

#include <vector>

#include "SpriteRenderer.h"
#include "LevelManager.h"
#include "Player.h"

#include "AnimatedGameObject.h"

class StateGame : public Entropy::GameState
{
private:
	Entropy::Math::Mat4 Projection;
	SpriteRenderer renderer;
	AnimationRenderer animationRenderer;

	bool key_down;
	bool execute_selection;

	unsigned int i = 0;
	unsigned int j = 0;

public:
	StateGame();

	// Inherited via GameState
	virtual bool init() override;
	virtual void input(Entropy::Graphics::Window& window) override;
	virtual void render() override;
	virtual GameState* update(GameState* gameState) override;
};