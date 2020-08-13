#pragma once

#include <Entropy/Math/Vec2.h>

class BoxCollider
{
protected:
	Entropy::Math::Vec2 position;
	Entropy::Math::Vec2 size;
	Entropy::Math::Vec2 offset;

public:
	BoxCollider() {};
	BoxCollider(Entropy::Math::Vec2 position, Entropy::Math::Vec2 size, Entropy::Math::Vec2 offset) : position(position), size(size), offset(offset) {};

	Entropy::Math::Vec2& getPosition();

	void setPosition(Entropy::Math::Vec2 position);
	void setPosition(float x, float y);

	const bool detect(const BoxCollider& other) const;
};