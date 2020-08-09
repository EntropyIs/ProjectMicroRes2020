#include "PlayerWeapon.h"

#include <Entropy/Math/Converters.h>

using namespace Entropy;

PlayerWeapon::PlayerWeapon(const char* spritename, float angle, unsigned int row, Entropy::Math::Vec2 position, Entropy::Math::Vec2 boxSize, Entropy::Math::Vec2 boxOffset, Entropy::Math::Vec2 textureOffset) :
	AnimatedGameObject("PlayerWeapon", spritename, 4, row, 2, position, boxSize, boxOffset, textureOffset)
{
	this->angle = Entropy::Math::Radians(angle);
}

void PlayerWeapon::Update()
{
	if (animationRenderer.isComplete()) // Animation has finished
		alive = false;
	else
		animationRenderer.Update();

	// Get position from players position

}
