#pragma once

#include "AnimatedGameObject.h"
#include "Direction.h"

class HotdogKing : public AnimatedGameObject
{
private:
	Entropy::Math::Vec3 color;
	Direction lastDirection;

	bool hurting;
	bool dieing;

	unsigned int hurtAnim;

	float moveTimer;
	float attackTimer;

public:
	HotdogKing(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f));

	virtual void Draw(SpriteRenderer& renderer) override;

	virtual void Update() override;
};