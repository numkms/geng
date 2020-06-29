#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "./MapBuilder.h"
#include "./Map.h"


Game::Game() {
    this->isRunning = false;
    MapBuilder mapBuilder = MapBuilder();
    this->map = mapBuilder.BuildMap();
    this->platform = new Platform();
    this->ball = new Ball(this->platform->GetX(), this->platform->GetY() - this->platform->GetHeight() - 2);
    this->arkanoid = new Arkanoid(this->map, this->platform, this->ball);
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return this->isRunning;
}

void Game::Initialize(int width, int height) {
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL." << std::endl;
          return;
    }

    window = SDL_CreateWindow(
        "Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS
    );

    if(!window) {
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    this->scoreboard = new Scoreboard(renderer);

    if(!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return;
    }

    isRunning = true;
    return;
}


void Game::ProcessInput() {
     SDL_Event event;
     SDL_PollEvent(&event);
     switch (event.type) {
         case SDL_QUIT: {
             isRunning = false;
             break;
         }

         case SDL_KEYDOWN: {
             if(event.key.keysym.sym == SDLK_ESCAPE) {
                 isRunning = false;
             } 

             if(event.key.keysym.sym == SDLK_RIGHT) {
                 this->platform->MoveRight();
             }

             if(event.key.keysym.sym == SDLK_LEFT) {
                 this->platform->MoveLeft();
             }

             if(event.key.keysym.sym == SDLK_RETURN) {
                 this->arkanoid->RunGame();
             }
         }
         
         default: {
             break;
         }
     }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    for (int i = 0; i < 90; i++) {
            Rectangle block = map->blocks[i]; 
            if(!block.hidden) {
                SDL_Rect projectile {
                (int) block.GetX(),
                (int) block.GetY(),
                (int) block.GetWidth(),
                (int) block.GetHeight()
            };

            SDL_SetRenderDrawColor(
                renderer,
                block.GetColor().r,
                block.GetColor().g,
                block.GetColor().b,
                block.GetColor().a
            );
            
            SDL_RenderFillRect(renderer, &projectile);
        } 
    }

    SDL_SetRenderDrawColor(
            renderer,
            102,
            205,
            170,
            255
    );

    SDL_Rect platformTile {
        (int) this->platform->GetX(),
        (int) this->platform->GetY(),
        (int) this->platform->GetWidth(),
        (int) this->platform->GetHeight()
    };

    SDL_RenderFillRect(renderer, &platformTile);        


    SDL_SetRenderDrawColor(
            renderer,
            255,
            255,
            255,
            255
    );
    
    SDL_Rect ballTile {
        (int) this->ball->GetX(),
        (int) this->ball->GetY(),
        (int) this->ball->GetWidth(),
        (int) this->ball->GetHeight()
    };

    SDL_RenderFillRect(renderer, &ballTile);        

    SDL_RenderPresent(renderer);
}

void Game::Update() {
    if(this->arkanoid->IsGameStarted()) {
        this->arkanoid->MoveBall();
        this->scoreboard->WriteData("Lives: ");
    }
     //Waiting
    //  while(!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME));

     int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - ticksLastFrame);

     if(timeToWait > 0 && timeToWait < FRAME_TARGET_TIME) {
         SDL_Delay(timeToWait);
     }

     //Delta time is the difference of current and last frame rendering time 
     float deltaTime =  (SDL_GetTicks() - ticksLastFrame) / 1000.0f;
     ticksLastFrame = SDL_GetTicks();
     
     deltaTime = deltaTime > 0.05f ? 0.05f : deltaTime;

    //  projectilePos = glm::vec2(
    //     projectilePos.x + projectileVelocity.x * deltaTime,
    //     projectilePos.y + projectileVelocity.y * deltaTime
    //  );
} 

void Game::Destroy() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}