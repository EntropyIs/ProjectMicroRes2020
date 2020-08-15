#pragma once

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/efx.h>

class AudioEngine
{
private:
	ALCdevice* Device;
	ALCcontext* Context;

public:
	AudioEngine();
	~AudioEngine();
};
