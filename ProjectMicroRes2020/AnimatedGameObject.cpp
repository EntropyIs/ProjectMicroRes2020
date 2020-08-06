#include "AnimatedGameObject.h"

void AnimatedGameObject::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position);
}

void AnimatedGameObject::Update()
{
	animationRenderer.Update();
}
