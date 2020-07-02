#include "AssetManager.h"
AssetManager::AssetManager(Scene* scene): scene(scene) {

}

void AssetManager::ClearData() {
    textures.clear();
}

void AssetManager::AddTexture(std::string textureId, const char* filePath) {
    textures.emplace(textureId, TextureManager::LoadTexture(filePath));
}

SDL_Texture* AssetManager::GetTexture(std::string textureId) {
    return textures[textureId];
}

void AssetManager::AddFont(std::string fontId, const char* filePath, int fontSize) {
    fonts.emplace(fontId, FontManager::LoadFont(filePath, fontSize));
}

TTF_Font* AssetManager::GetFont(std::string fontId) {
    return fonts[fontId];
}

void AssetManager::AddSample(std::string sampledId, std::string filePath, int volume) {
    samples.emplace(sampledId, AudioManager::LoadSample(filePath, volume));
}

AudioSample* AssetManager::GetSample(std::string sampleId) {
    printf("Aue");
    AudioSample* sample =  samples[sampleId];
    printf("Aue");
    return sample;
}