#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "./Map.h"
#include "./Platform.h"
#include "./Ball.cpp"
#include "./Arkanoid.h"
#include "./Scoreboard.h"

class Game {
    private:
        Map * map; 
        Platform * platform;
        Ball * ball;
        Arkanoid * arkanoid;
        Scoreboard * scoreboard;
        
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