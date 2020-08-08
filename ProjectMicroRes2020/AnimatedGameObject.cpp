#include "AnimatedGameObject.h"

void AnimatedGameObject::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position + texture_offset);
}

void AnimatedGameObject::Update()
{
	animationRenderer.Update();
}
