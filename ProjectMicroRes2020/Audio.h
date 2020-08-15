#pragma once

#include <AL/al.h>
#include <AL/alc.h>

class Audio
{
private:
	unsigned int audioBuffer;
	unsigned int audioSource;
	unsigned int frequency;
	int format;

	int state;

public:
	Audio(const char* path);
	Audio() {};
	~Audio();

	void play();
	void stop();

	bool load(const char* path);
};