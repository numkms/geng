#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H
#include <map>
#include <string>
#include "TextureManager.h"
#include "FontManager.h"
#include <SDL2/SDL_ttf.h>
#include "AudioManager.h"

class EntityManager;
class AssetManager {
    private:
        Scene* scene;
        std::map<std::string, SDL_Texture*> textures;
        std::map<std::string, TTF_Font*> fonts;
        std::map<std::string, AudioSample*> samples;
    public:
        AssetManager(Scene* scene);
        ~AssetManager();
        
        void ClearData();
        void AddTexture(std::string textureId, const char* filePath);
        void AddFont(std::string fontId, const char* filePath, int fontSize);
        void AddSample(std::string sampleId, std::string filePath, int volume);
        
        SDL_Texture* GetTexture(std::string textureId);
        TTF_Font* GetFont(std::string fontId);
        AudioSample* GetSample(std::string sampleId);
};
#endif;