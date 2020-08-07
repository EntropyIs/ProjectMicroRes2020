#pragma once

#include <Entropy/Math/Vec2.h>

#define _ShowCollider

class BoxCollider
{
protected:
	Entropy::Math::Vec2 position;
	Entropy::Math::Vec2 size;
	Entropy::Math::Vec2 offset;

#ifdef _ShowCollider
	unsigned int VAO;
#endif // _ShowCollider


public:
	BoxCollider() {
#ifdef _ShowCollider
		initRendererData();
#endif // _ShowCollider
	};
	BoxCollider(Entropy::Math::Vec2 position, Entropy::Math::Vec2 size, Entropy::Math::Vec2 offset) : position(position), size(size), offset(offset) {
#ifdef _ShowCollider
		initRendererData();
#endif // _ShowCollider
	};

	Entropy::Math::Vec2& getPosition();

	void setPosition(Entropy::Math::Vec2 position);
	void setPosition(float x, float y);

	const bool detect(const BoxCollider& other) const;

#ifdef _ShowCollider
	void initRendererData();
	void draw();
#endif // _ShowCollider

};