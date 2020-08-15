#pragma once

class Audio
{
private:
	unsigned int audioBuffer;
	unsigned int audioSource;

	int state;

public:
	Audio(const char* path);
	Audio() {};
	~Audio();

	void play();
};