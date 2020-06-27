#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Map.h"

class Game {
    private:
        Map * map; 
        bool isRunning;
        SDL_Renderer *renderer;
        SDL_Window *window;
    public:
        Game();
        ~Game();
        int ticksLastFrame;
        bool IsRunning() const;    
        void Initialize(int width, int height);
        void ProcessInput();
        void Update();
        void Render();
        void Destroy();
};
    
#endif