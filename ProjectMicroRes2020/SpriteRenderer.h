#pragma once

#include <Entropy/Graphics/Material.h>
#include <Entropy/Graphics/Shader.h>
#include <Entropy/Math/Vec2.h>
#include <Entropy/Math/Vec3.h>

class SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Draw(Entropy::Math::Vec2 position, Entropy::Graphics::Texture& spriteSheet,
		Entropy::Math::Vec2 spriteIndex = Entropy::Math::Vec2(0.0f), Entropy::Math::Vec2 spriteSheetSize = Entropy::Math::Vec2(1.0f, 1.0f),
		unsigned int spriteWidth = 8, unsigned int spriteHeight = 8,
		float rotAngle = 0, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f)
	);

private:
	unsigned int VAO;

	void initRenderData();
};