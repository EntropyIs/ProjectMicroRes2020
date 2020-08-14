#include "HotdogWeapon.h"

HotdogWeapon::HotdogWeapon(const char* spritename, unsigned int row, 
	Entropy::Math::Vec2 position, Entropy::Math::Vec2 velocity, Entropy::Math::Vec2 offset,
	Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) : position_offset(offset),
	AnimatedGameObject("HotdogWeapon", spritename, 7, row, 14, position + offset, boxSize, boxOffset, textureOffset)
{
	animationRenderer.playAnimationOnce();
	this->velocity = velocity;
}

void HotdogWeapon::Update()
{
	if (alive)
	{
		performMovement();
		if (position.X < -10.0f || position.X > 10.0f || position.Y < -10.0f || position.Y > 10.0f)
			alive = false;
	}
}
