#pragma once

#include "AnimatedGameObject.h"

class Ketchup : public AnimatedGameObject
{
private:
	Entropy::Math::Vec3 color;

	float angle;
	float speed;

	bool hurting;
	bool dieing;
	bool set;

	unsigned int hurtAnim;

public:
	Ketchup(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f));

	virtual void Draw(SpriteRenderer& renderer) override;

	virtual void Update() override;
};
