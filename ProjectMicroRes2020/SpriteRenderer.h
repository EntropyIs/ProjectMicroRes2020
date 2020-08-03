#pragma once

#include <Entropy/Graphics/Material.h>
#include <Entropy/Graphics/Shader.h>
#include <Entropy/Math/Vec2.h>
#include <Entropy/Math/Vec3.h>

#include "ResourceManager.h"

class SpriteRenderer
{
public:
	SpriteRenderer();
	~SpriteRenderer();

	void Draw(Entropy::Math::Vec2 position, Entropy::Graphics::Texture& spriteSheet,
		Entropy::Math::Vec2 spriteIndex, SpriteData& spriteData,
		float rotAngle = 0, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f)
	);

private:
	unsigned int VAO;

	void initRenderData();
};