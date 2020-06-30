#ifndef FONT_MANAGER_H;
#define FONT_MANAGER_H;
#include "./Game.h"
#include <SDL2/SDL_ttf.h>

class FontManager {
    public:
        static TTF_Font* LoadFont(const char* fileName, int fontSize);
        static void Draw(SDL_Texture* texture, SDL_Rect position);
    private:
};

#endif