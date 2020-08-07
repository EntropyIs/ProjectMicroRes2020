#pragma once

#include "AnimatedGameObject.h"

class Slime : public AnimatedGameObject
{
private:
	Entropy::Math::Vec3 color;

	float angle;
	float speed;

	bool set;

public:
	Slime(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f));

	virtual void Draw(SpriteRenderer& renderer) override;

	virtual void Update() override;
};
