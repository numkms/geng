#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "./Game.h"
class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static void Draw(SDL_Texture * texture, SDL_Rect sourceRectangle, SDL_Rect destinationRectangle, SDL_RendererFlip flip);
        static void Draw(SDL_Rect rectangle, SDL_Color color);
};
#endif;