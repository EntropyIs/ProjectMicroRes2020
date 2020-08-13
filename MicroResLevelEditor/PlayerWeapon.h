#pragma once

#include "AnimatedGameObject.h"

class PlayerWeapon : public AnimatedGameObject
{
private:
	Entropy::Math::Vec2 position_offset;

public:
	PlayerWeapon(const char* spritename, unsigned int row = 0.0f,
		Entropy::Math::Vec2 position = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 offset = Entropy::Math::Vec2(0.0f, 0.0f),
		Entropy::Math::Vec2 boxSize = Entropy::Math::Vec2(8.0f, 8.0f), Entropy::Math::Vec2 boxOffset = Entropy::Math::Vec2(4.0f, 4.0f),
		Entropy::Math::Vec2 textureOffset = Entropy::Math::Vec2(0.0f, 0.0f));
	PlayerWeapon() {};

	virtual void Update() override;
};
