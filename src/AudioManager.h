#ifndef AUDIO_MANAGER_H 
#define AUDIO_MANAGER_H
#include "AudioSample.h"
class AudioManager
{
private:
public:
    AudioManager(/* args */);
    ~AudioManager();
    static AudioSample* LoadSample(std::string path, int volume) {
        AudioSample* sample = new AudioSample(path, volume);
        return sample;
    }
};

#endif