#pragma once

#include "AnimatedGameObject.h"

class Mustard : public AnimatedGameObject
{
private:
	Entropy::Math::Vec3 color;

	float angle;
	float speed;

	bool hurting;
	bool dieing;

	unsigned int hurtAnim;

public:
	Mustard(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f));

	virtual void Draw(SpriteRenderer& renderer) override;

	virtual void Update() override;
};
