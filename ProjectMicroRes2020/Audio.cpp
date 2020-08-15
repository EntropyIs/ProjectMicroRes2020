#include "Audio.h"

#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <AL/efx.h>
#include <AL/efx-creative.h>
#include <AL/efx-presets.h>

#include <exception>
#include <string>
#include <stdio.h>

Audio::Audio(const char* path)
{
	// Generate Audio Buffers
	alGenBuffers(1, &audioBuffer);
	alGenSources(1, &audioSource);

	// Load Audio File
	if (!load(path))
		throw std::exception("Failed to load audio source.");

	float sourcePos[] = { 0.0f, 0.0f, 0.0f };
	float sourceVel[] = { 0.0f, 0.0f, 0.0f };
	float listenerPos[] = { 0.0f, 0.0f, 0.0f };
	float listenerVel[] = { 0.0f, 0.0f, 0.0f };
	float listenerOri[] = { 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f };

	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	alSourcei (audioSource, AL_BUFFER,   audioBuffer);
	alSourcei (audioSource, AL_PITCH,    (ALint) 1.0f);
	alSourcei (audioSource, AL_GAIN,	 (ALint) 1.0f);
	alSourcefv(audioSource, AL_POSITION, sourcePos);
	alSourcefv(audioSource, AL_VELOCITY, sourceVel);
	alSourcei (audioSource, AL_LOOPING,  false);

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
	alGetSourcei(audioSource, AL_BUFFER, &state);
}

void Audio::stop()
{
	if (state == AL_PLAYING)
		alSourceStop(audioSource);
	alGetSourcei(audioSource, AL_BUFFER, &state);
}

bool Audio::load(const char* path)
{
	FILE* inFile = NULL;
	fopen_s(&inFile, path, "rb");

	// First 40bytes are header
	char type[4];
	long size, dataSize, chunkSize, sampleRate, averageBytesPerSec;
	short formatType, channels, bytesPerSample, bitsPerSample;

	fread(type, sizeof(char), 4, inFile);
	if(!strcmp(type, "RIFF")) // Not riff format
		return false;

	fread(&size, sizeof(long), 1, inFile);

	fread(type, sizeof(char), 4, inFile);
	if (!strcmp(type, "WAVE")) // Not wave format
		return false;

	fread(type, sizeof(char), 4, inFile);
	if (!strcmp(type, "fmt ")) // Not not fmt
		return false;

	fread(&chunkSize, sizeof(long), 1, inFile);
	fread(&formatType, sizeof(short), 1, inFile);
	fread(&channels, sizeof(short), 1, inFile);
	fread(&sampleRate, sizeof(long), 1, inFile);
	fread(&averageBytesPerSec, sizeof(long), 1, inFile);
	fread(&bytesPerSample, sizeof(short), 1, inFile);
	fread(&bitsPerSample, sizeof(short), 1, inFile);

	fread(type, sizeof(char), 4, inFile);
	if (!strcmp(type, "DATA")) // Not not DATA
		return false;

	fread(&dataSize, sizeof(long), 1, inFile);

	void* buf = malloc((size_t)dataSize);
	fread(buf, sizeof(unsigned long), dataSize, inFile);

	if (bitsPerSample == 8)
	{
		if (channels == 1)
			format = AL_FORMAT_MONO8;
		else if (channels == 2)
			format = AL_FORMAT_STEREO8;
	}
	else if (bitsPerSample == 16)
	{
		if (channels == 1)
			format = AL_FORMAT_MONO16;
		else if (channels == 2)
			format = AL_FORMAT_STEREO16;
	}

	alBufferData(audioBuffer, format, buf, dataSize, sampleRate);

	fclose(inFile);

	return true;
}
