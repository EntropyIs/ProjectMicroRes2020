#include "Audio.h"

#include "../Middleware/OpenAl/samples/framework/Framework.h"
#include <AL/al.h>

#include <exception>

Audio::Audio(const char* path)
{
	// Generate Audio Buffers
	alGenBuffers(1, &audioBuffer);

	// Load Audio File
	if (!ALFWLoadWaveToBuffer((char*)ALFWaddMediaPath(path), audioBuffer))
		throw std::exception("Failed to load audio source");
	alGenSources(1, &audioSource);
	alSourcei(audioSource, AL_BUFFER, audioBuffer);
	alGetSourcei(audioSource, AL_BUFFER, &state);
}

Audio::~Audio()
{
	alSourceStop(audioSource);
	alDeleteSources(1, &audioSource);
	alDeleteBuffers(1, &audioBuffer);
}

void Audio::play()
{
	if(state != AL_PLAYING)
		alSourcePlay(audioSource);
}
