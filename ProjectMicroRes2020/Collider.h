#pragma once

#include <Entropy/Math/Vec2.h>

class Collider //Abstract Collider Class
{
protected:
	Entropy::Math::Vec2 position;

public:
	Collider(Entropy::Math::Vec2 position) : position(position) {};
	Collider(float x, float y) : position(x, y) {};

	const Entropy::Math::Vec2& getPosition();
	void setPosition(Entropy::Math::Vec2 position);
	void setPosition(float x, float y);

	virtual const bool Detect(const Collider& other) const = 0;

protected:
	virtual const bool Detect(const BoxCollider& other) const = 0;

	friend class BoxCollider;
};

class BoxCollider : public Collider
{
protected:
	Entropy::Math::Vec2 size;
	Entropy::Math::Vec2 offset;

public:
	BoxCollider(Entropy::Math::Vec2 position, Entropy::Math::Vec2 size, Entropy::Math::Vec2 offset) : Collider(position), size(size), offset(offset) {};

	virtual const bool Detect(const Collider& other) const;

protected:
	virtual const bool Detect(const BoxCollider& other) const;
};