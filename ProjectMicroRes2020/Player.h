#pragma once

#include "AnimatedGameObject.h"

class Player : public AnimatedGameObject
{
private:
	bool vulnerable;
	float timer;

	float invulnerable_time = 30.0f;

public:
	Player(std::string id, const char* spriteName, unsigned int row = 0.0f,
		Entropy::Math::Vec2 position = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 boxSize = Entropy::Math::Vec2(8.0f, 8.0f),
		Entropy::Math::Vec2 boxOffset = Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2 textureOffset = Entropy::Math::Vec2(0.0f, 0.0f));
	Player() {};

	virtual void Update() override;
};