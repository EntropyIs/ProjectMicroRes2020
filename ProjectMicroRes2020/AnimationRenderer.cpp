#include "AnimationRenderer.h"

#include "ResourceManager.h"

using namespace Entropy;

AnimationRenderer::AnimationRenderer(std::string spriteSheet, unsigned int numFrames, unsigned int rowNum, unsigned int fps) : sprite_sheet(spriteSheet), num_frames(numFrames), row_num(rowNum)
{
	frame_advance_time = 1.0f / fps;
	current_time = 0.0f;
	current_frame = 0;
}

void AnimationRenderer::Draw(SpriteRenderer& renderer, Entropy::Math::Vec2 position, float rotAngle, Entropy::Math::Vec3 color)
{
	renderer.Draw(position, ResourceManager::getTexture(sprite_sheet), Math::Vec2(current_frame, row_num), ResourceManager::getSpriteSizeData(sprite_sheet), rotAngle, color);
}

void AnimationRenderer::Update()
{
	current_time += ResourceManager::getTimeElapsed();
	if (current_time >= frame_advance_time)
	{
		current_time -= frame_advance_time;
		current_frame++;
			if (current_frame >= num_frames)
				current_frame = 0;
	}
}

void AnimationRenderer::setRowNumber(unsigned int rowNumber)
{
	row_num = rowNumber;
}
