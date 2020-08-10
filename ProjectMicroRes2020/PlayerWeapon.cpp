#include "PlayerWeapon.h"

#include <Entropy/Math/Converters.h>
#include "EntityManager.h"

using namespace Entropy;

PlayerWeapon::PlayerWeapon(const char* spritename, unsigned int row, Entropy::Math::Vec2 position, Entropy::Math::Vec2 offset, 
	Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) : position_offset(offset),
AnimatedGameObject("PlayerWeapon", spritename, 7, row, 14, position, boxSize, boxOffset, textureOffset)
{
	animationRenderer.playAnimationOnce();
}

void PlayerWeapon::Update()
{
	if (animationRenderer.isComplete()) // Animation has finished
		alive = false;
	else
		animationRenderer.Update();

	// Get position from players position
	position = EntityManager::getPlayer().getPosition() + position_offset;
}
