#include "BoxCollider.h"

const bool BoxCollider::Detect(const Collider* other) const
{
	Math::Vec2 otherlower = other.position - other.box_offset;
	Math::Vec2 otherUpper = otherlower + other.box_size;
	Math::Vec2 lower = position - box_offset;
	Math::Vec2 upper = lower + box_size;

	return (lower.X < otherUpper.X&& upper.X > otherlower.X &&
		lower.Y < otherUpper.Y&& upper.Y > otherlower.Y);
	return false;
}
