#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "AssetManager.h"
#include "Map.h"
#include "Arkanoid/ArkanoidMenuScene.h"
#include "Arkanoid/ArkanoidGameScene.h"
#include "Arkanoid/ArkanoidScoreboardScene.h"
#include "SceneManager.h"
#include <SDL2/SDL_mixer.h>
SceneManager sceneManager;

SDL_Renderer* Game::renderer;
SDL_Event Game::event;
SDL_Rect Game::camera = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

Mix_Music *gMusic = NULL;
//The sound effects that will be used
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;
bool Game::isRunning;

Map* map;
Game::Game() {
    Game::isRunning = false;
}

Game::~Game() {

}

bool Game::IsRunning() const {
    return Game::isRunning;
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

    if(SETTING_IS_SOUND_ENABLED && Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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
    sceneManager.AddScene<ArkanoidMenuScene>();
    sceneManager.AddScene<ArkanoidGameScene>();
    sceneManager.AddScene<ArkanoidScoreboardScene>();
    sceneManager.ShowScene<ArkanoidMenuScene>();
    Game::isRunning = true;
    return;

}

void Game::ProcessInput() {
     SDL_PollEvent(&event);
     switch (event.type) {
         case SDL_QUIT: {
             Game::isRunning = false;
             break;
         }

         default: {
             break;
         }
     }
}

void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    sceneManager.Render();

    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    SDL_RenderPresent(renderer);
}

void Game::ProcessGameOver() {
    std::cout << "Process game over" << std::endl;
    Game::isRunning = false;
}

void Game::ProcessNextLevel(int levelNumber) {
    std::cout << "Process next level" << std::endl;
    Game::isRunning = false;
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
     
     sceneManager.Update(deltaTime);
} 

void Game::Destroy() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   Mix_Quit();
   SDL_Quit();
}