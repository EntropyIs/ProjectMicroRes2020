#include "AnimationRenderer.h"

#include "ResourceManager.h"

using namespace Entropy;

AnimationRenderer::AnimationRenderer(std::string spriteSheet, unsigned int numFrames, unsigned int rowNum, unsigned int fps) : sprite_sheet(spriteSheet), num_frames(numFrames), row_num(rowNum)
{
	frame_advance_time = 1.0f / fps;
	current_time = 0.0f;
	current_frame = 0;
	playing = true;
	playOnce = false;
	complete = false;
}

void AnimationRenderer::Draw(SpriteRenderer& renderer, Entropy::Math::Vec2 position, float rotAngle, Entropy::Math::Vec3 color)
{
	renderer.Draw(position, ResourceManager::getTexture(sprite_sheet), Math::Vec2((float)current_frame, (float)row_num), ResourceManager::getSpriteSizeData(sprite_sheet), rotAngle, color);
}

void AnimationRenderer::Update()
{
	if (playing)
	{
		current_time += ResourceManager::getTimeElapsed();
		if (current_time >= frame_advance_time)
		{
			current_time -= frame_advance_time;
			current_frame++;
			if (current_frame >= num_frames && !playOnce)
				current_frame = 0;
			else if (current_frame >= num_frames && playOnce)
			{
				current_frame = 0;
				playing = false;
				complete = true;
			}
		}
	}
}

unsigned int AnimationRenderer::getFrame()
{
	return current_frame;
}

void AnimationRenderer::playAnimation()
{
	playing = true;
}

void AnimationRenderer::playAnimationOnce()
{
	playing = true;
	playOnce = true;
	complete = false;
}

void AnimationRenderer::stopAnimation()
{
	playing = false;
	current_frame = 0; // Assume frame 0 is idle
	current_time = 0;
}

bool AnimationRenderer::isComplete()
{
	return complete;
}

void AnimationRenderer::setRowNumber(unsigned int rowNumber)
{
	row_num = rowNumber;
}
