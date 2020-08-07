#pragma once

#include "AnimatedGameObject.h"

class Slime : public AnimatedGameObject
{
private:
	Entropy::Math::Vec3 color;
public:
	Slime(std::string id, Entropy::Math::Vec2 position, Entropy::Math::Vec3 color = Entropy::Math::Vec3(0.0f)) :
		AnimatedGameObject(id, "slime_sheet", 3, 0, 6, position, Entropy::Math::Vec2(8.0f, 8.0f),
			Entropy::Math::Vec2(4.0f, 4.0f), Entropy::Math::Vec2(1.0f, 1.0f)), color(color) {};

	virtual void Draw(SpriteRenderer& renderer) override;
	virtual void Update() override;
};
