#include "Collider.h"

Entropy::Math::Vec2& BoxCollider::getPosition()
{
	return position;
}

void BoxCollider::setPosition(Entropy::Math::Vec2 position)
{
    this->position = position;
}

void BoxCollider::setPosition(float x, float y)
{
    position = Entropy::Math::Vec2(x, y);
}

const bool BoxCollider::Detect(const BoxCollider& other) const
{
	Entropy::Math::Vec2 otherlower = other.position - other.offset;
	Entropy::Math::Vec2 otherUpper = otherlower + other.size;
	Entropy::Math::Vec2 lower = position - offset;
	Entropy::Math::Vec2 upper = lower + size;

	return (lower.X < otherUpper.X&& upper.X > otherlower.X &&
		lower.Y < otherUpper.Y&& upper.Y > otherlower.Y);
}
