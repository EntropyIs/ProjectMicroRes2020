#include "AnimatedGameObject.h"

void AnimatedGameObject::Draw(SpriteRenderer& renderer)
{
	if(alive) // Only render if alive
		animationRenderer.Draw(renderer, position + texture_offset);
}

void AnimatedGameObject::Update()
{
	animationRenderer.Update();
}
