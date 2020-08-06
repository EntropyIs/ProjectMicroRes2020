#pragma once

#include "GameObject.h"

#include "AnimationRenderer.h"

class AnimatedGameObject : public GameObject
{
protected:
	AnimationRenderer animationRenderer;

public:
	AnimatedGameObject(const char* name, const char* spriteName, unsigned int numFrames, unsigned int rowNum, unsigned int fps,
		Entropy::Math::Vec2 position = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 boxSize = Entropy::Math::Vec2(8.0f, 8.0f),
		Entropy::Math::Vec2 boxOffset = Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2 textureOffset = Entropy::Math::Vec2(0.0f, 0.0f)) :
		GameObject(name, spriteName, Entropy::Math::Vec2(0.0f, (float) rowNum), position, boxSize, boxOffset, textureOffset),
		animationRenderer(spriteName, numFrames, rowNum, fps) {};
	AnimatedGameObject() {};

	virtual void Draw(SpriteRenderer& renderer) override;

	virtual void Update() override;
};