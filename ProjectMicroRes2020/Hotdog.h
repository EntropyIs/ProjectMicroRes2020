#pragma once

#include "AnimatedGameObject.h"
#include "Direction.h"

class Hotdog : public AnimatedGameObject
{
private:
	Entropy::Math::Vec3 color;
	Direction lastDirection;

	float angle;
	float speed;

	bool set;

	bool hurting;
	bool dieing;

	unsigned int hurtAnim;

	float moveTimer;
	float attackTimer;

public:
	Hotdog(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f));

	virtual void Draw(SpriteRenderer& renderer) override;

	virtual void Update() override;
};