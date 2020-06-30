#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "AssetManager.h"
#include "Map.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
Map* map;
Game::Game() {
    this->isRunning = false;
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
    
    if(TTF_Init() != 0) {
        std::cerr << "Error init sdl ttf" << std::endl;
        return;
    }

    if(!window) {
        std::cerr << "Error creating SDL window" << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);

    if(!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return;
    }

    LoadLevel(0);

    isRunning = true;
    return;
}
void Game::LoadLevel(int levelNumber) {

}

void Game::ProcessInput() {
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
         }
         default: {
             break;
         }
     }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);


    if(manager.HasNoEntities()) {
        return;
    }

    manager.Render();

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderPresent(renderer);
}

void Game::CheckCollisions() {
    CollisionType collisionType = manager.CheckEntityCollisions();
    
    if(collisionType == PLAYER_ENEMY) {
        ProcessGameOver();
    }

    if(collisionType == PLAYER_PROJECTILE) {
        ProcessGameOver();
    }

    if(collisionType == PLAYER_LEVEL_COMPLETE) {
        ProcessNextLevel(1);
    }
}

void Game::ProcessGameOver() {
    std::cout << "Process game over" << std::endl;
    isRunning = false;
}

void Game::ProcessNextLevel(int levelNumber) {
    std::cout << "Process next level" << std::endl;
    isRunning = false;
}

void Game::Update() {
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
     
     manager.Update(deltaTime);
     CheckCollisions();
} 

void Game::Destroy() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}