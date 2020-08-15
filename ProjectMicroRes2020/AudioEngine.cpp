#include "AudioEngine.h"

#include <AL/al.h>
#include <AL/alc.h>

#include <exception>

AudioEngine::AudioEngine()
{
    Device = alcOpenDevice(NULL);
    if (!Device)
        throw std::exception("No sound device");
    Context = alcCreateContext(Device, NULL);
    alcMakeContextCurrent(Context);
    if (!Context)
        throw std::exception("No sound context");
}

AudioEngine::~AudioEngine()
{
    alcMakeContextCurrent(NULL);
    alcDestroyContext(Context);
    alcCloseDevice(Device);
}
