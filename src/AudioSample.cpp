#include "AudioSample.h"
#include <iostream>

AudioSample::AudioSample(const std::string &path, int volume, bool isEffect): isEffect(isEffect) {
    if(isEffect) {
        effect = Mix_LoadWAV(path.c_str());
    } else {
        music = Mix_LoadMUS(path.c_str());
    }   
}

// -1 here means we let SDL_mixer pick the first channel that is free
// If no channel is free it'll return an err code.
void AudioSample::Play() {
    if(isEffect) {
        if(Mix_PlayChannel(-1, effect, 0) != -1) {
            printf("Mix_PlayMusic: %s\n", Mix_GetError());
        }
    } else {
        if(Mix_PlayMusic(music, -1) == -1) {
            printf("Mix_PlayMusic: %s\n", Mix_GetError());
        }
    }

}

void AudioSample::SetVolume(int volume) {
 
}
