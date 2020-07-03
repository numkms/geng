#ifndef AUDIO_MANAGER_H 
#define AUDIO_MANAGER_H
#include "AudioSample.h"

class AudioManager
{
public:
    AudioManager(/* args */);
    ~AudioManager();
    static AudioSample* LoadSample(std::string path, int volume, bool isEffect) {
        AudioSample* sample = new AudioSample(path, volume, isEffect);
        return sample;
    }
};

#endif