#include "Slime.h"

#include <Entropy/Math/Transform2D.h>

Slime::Slime(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color) :
	AnimatedGameObject(id, "slime_sheet", 3, 0, 6, position, Entropy::Math::Vec2(8.0f, 8.0f),
		Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2(1.0f, 1.0f)), color(color)
{
	angle = 0.0f;
	speed = 0.0f;

	set = false;
}

void Slime::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position, 0.0f, color);
}

void Slime::Update()
{
	animationRenderer.Update();

	// Set Movement Pattern
	if (animationRenderer.getFrame() == 1 && !set) // frame 1, begin moveing
	{
		angle += 0.5f;
		speed = 25.0f;
		set = true;
	}
	else if (animationRenderer.getFrame() == 2 && set) // frame 2, stop moving
	{
		speed = 0.0f;
		set = false;
	}
	Entropy::Math::Vec3 slime_velocity = Entropy::Math::Rotate(angle) * Entropy::Math::Vec3(speed, 0.0f, 0.0f);
	velocity.X = slime_velocity.X;
	velocity.Y = slime_velocity.Y;

	// Move Slime
	GameObject::Update();

	// Handle Off Screen

	// Handle Collsions
}
