#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "AssetManager.h"

EntityManager manager;
AssetManager* Game::assetManager = new AssetManager(&manager);
SDL_Renderer* Game::renderer;

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
    
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());

    Entity& tankEntity(manager.AddEntity("tank"));
    tankEntity.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("tank-image");

    Entity& chopperEntity(manager.AddEntity("chopper"));
    tankEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    tankEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    
    // Entity& entityB(manager.AddEntity("projecttileB"));
    // entityB.AddComponent<TransformComponent>(0, 0, 20, 20, 32, 32, 1);
    
    // Entity&  entityC(manager.AddEntity("projecttileC"));
    // entityC.AddComponent<TransformComponent>(0,WINDOW_HEIGHT - 32, 20, -20, 32, 32, 1);

    // Entity& entityD(manager.AddEntity("projecttileD"));
    // entityD.AddComponent<TransformComponent>(WINDOW_WIDTH - 32 , WINDOW_HEIGHT -32, -20, -20, 32, 32, 1);

    manager.PrintEntityTree();
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
} 

void Game::Destroy() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}