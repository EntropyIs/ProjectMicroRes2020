#pragma once

#include "AnimatedGameObject.h"

class HotdogWeapon : public AnimatedGameObject
{
private:
	Entropy::Math::Vec2 position_offset;

public:
	HotdogWeapon(const char* spritename = "char_hotdog_weapon", unsigned int row = 0.0f,
		Entropy::Math::Vec2 position = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 velocity = Entropy::Math::Vec2(30.0f, 0.0f),
		Entropy::Math::Vec2 offset = Entropy::Math::Vec2(0.0f, 0.0f), Entropy::Math::Vec2 boxSize = Entropy::Math::Vec2(8.0f, 8.0f),
		Entropy::Math::Vec2 boxOffset = Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2 textureOffset = Entropy::Math::Vec2(0.0f, 0.0f));

	virtual void Update() override;
};