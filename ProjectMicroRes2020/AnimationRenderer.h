#pragma once

#include "SpriteRenderer.h"

#include <string>

class AnimationRenderer
{
private:
	float current_time;
	float frame_advance_time;

	unsigned int num_frames;
	unsigned int row_num;
	unsigned int current_frame;

	bool playing;

	std::string sprite_sheet;

public:
	AnimationRenderer(std::string spriteSheet, unsigned int numFrames, unsigned int rowNum, unsigned int fps);
	AnimationRenderer() : current_frame(0), current_time(0.0f), frame_advance_time(0.0f), num_frames(0), row_num(0), sprite_sheet() {};

	void Draw(SpriteRenderer& renderer, Entropy::Math::Vec2 position, float rotAngle = 0, Entropy::Math::Vec3 color = Entropy::Math::Vec3(1.0f));
	void Update();

	unsigned int getFrame();

	void playAnimation();
	void stopAnimation();

	void setRowNumber(unsigned int rowNumber);
};