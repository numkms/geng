#ifndef SCOREBOARD_H
#define SCOREBOARD_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Scoreboard {
    private:
        SDL_Renderer * renderer;
    public: 
        Scoreboard(SDL_Renderer * renderer) {
            this->renderer = renderer;
            // TTF_Init();
        }

        void WriteData(const char * text) {
            TTF_Font* Sans = TTF_OpenFont("../assets/fonts/Roboto/Roboto-Medium.ttf", 24); //this opens a font style and sets a size

            SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

            SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "dsadasd", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

           SDL_Texture* Message = SDL_CreateTextureFromSurface(this->renderer, surfaceMessage); //now you can convert it into a texture

            SDL_Rect Message_rect; //create a rect
            Message_rect.x = 500;  //controls the rect's x coordinate 
            Message_rect.y = 550; // controls the rect's y coordinte
            Message_rect.w = 100; // controls the width of the rect
            Message_rect.h = 100; // controls the height of the rec

            SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture

            //Don't forget to free your surface and texture
            SDL_FreeSurface(surfaceMessage);
            SDL_DestroyTexture(Message);
        }
};

#endif