#include "Slime.h"

void Slime::Draw(SpriteRenderer& renderer)
{
	animationRenderer.Draw(renderer, position, 0.0f, color);
}

void Slime::Update()
{
	animationRenderer.Update();
}
