#ifndef AUDIO_SAMPLE_H
#define AUDIO_SAMPLE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string>
class AudioSample {
public:
    AudioSample(const std::string &path, int volume, bool isEffect);
    void Play();
    void SetVolume(int volume);
private:
    bool isEffect;
    Mix_Music * music;
    Mix_Chunk * effect;
};
#endif
