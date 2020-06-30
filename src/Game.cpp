#include <iostream>
#include "./Constants.h"
#include "./Game.h"
#include "../lib/glm/glm.hpp"
#include "AssetManager.h"
#include "Map.h"

#include "Components/UILabelComponent.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "./Components/KeyboardControlComponent.h"
#include "./Components/ColliderComponent.h"
#include "./Components/ProjectileEmitterComponent.h"

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

Entity& chopperEntity(manager.AddEntity("chopper", PLAYER));

void Game::LoadLevel(int levelNumber) {
    

    assetManager->AddTexture("target-mark-image", std::string("./assets/images/collision-texture.png").c_str());
    assetManager->AddTexture("tank-image", std::string("./assets/images/tank-big-right.png").c_str());
    assetManager->AddTexture("chopper-image", std::string("./assets/images/chopper-spritesheet.png").c_str());
    assetManager->AddTexture("radar-image", std::string("./assets/images/radar.png").c_str());
    assetManager->AddTexture("jungle-tiletexture", std::string("./assets/tilemaps/jungle.png").c_str());
    assetManager->AddTexture("heliport-image", std::string("./assets/images/heliport.png").c_str());
    assetManager->AddTexture("projectile-image", std::string("./assets/images/bullet-enemy.png").c_str());

    assetManager->AddFont("charriot-font", std::string("./assets/fonts/charriot.ttf").c_str(), 14);

    map = new Map("jungle-tiletexture", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);
    std::cout << "Map loaded" << std::endl;
    Entity& tankEntity(manager.AddEntity("tank", ENEMY));
    tankEntity.AddComponent<TransformComponent>( 150, 495, 0, 0, 32, 32, 1);;
        std::cout << "Tank entity: OK" << std::endl;
    tankEntity.AddComponent<SpriteComponent>("tank-image");
        std::cout << "Tank entity: OK" << std::endl;
    tankEntity.AddComponent<ColliderComponent>("ENEMY", 0, 0, 32, 32);
        std::cout << "Tank entity: OK" << std::endl;
    tankEntity.GetComponent<ColliderComponent>()->MarkAsTarget("target-mark-image");    

    std::cout << "Tank entity: OK" << std::endl;

    chopperEntity.AddComponent<TransformComponent>(240, 106, 0, 0, 32, 32, 1);
    std::cout << "Chopper entity: OK" << std::endl;
    chopperEntity.AddComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    chopperEntity.AddComponent<KeyboardControlComponent>("up", "right", "down", "left", "space");
    chopperEntity.AddComponent<ColliderComponent>("PLAYER", 240, 106, 32, 32);
    chopperEntity.GetComponent<ColliderComponent>()->MarkAsTarget("target-mark-image");
    

    std::cout << "Chopper entity: OK" << std::endl;

    Entity& radarEntity(manager.AddEntity("radar", UI));
    radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.AddComponent<SpriteComponent>("radar-image", 8, 90, false, true); 
    std::cout << "Radar entity: OK" << std::endl;


    Entity& heliportEntity(manager.AddEntity("radar", UI));
    heliportEntity.AddComponent<TransformComponent>(420, 420, 0, 0, 32, 32, 1);
    heliportEntity.AddComponent<SpriteComponent>("heliport-image"); 
    heliportEntity.AddComponent<ColliderComponent>("LEVEL_COMPLETE", 420, 420, 32, 32); 
    std::cout << "Heliport entity: OK" << std::endl;

    Entity& projectile(manager.AddEntity("projectile", PROJECTILE));
    projectile.AddComponent<TransformComponent>( 150 + 16, 495 + 16, 0, 0, 4, 4, 1);
    projectile.AddComponent<SpriteComponent>("projectile-image");
    projectile.AddComponent<ColliderComponent>("PROJECTILE", 150 + 16, 495 + 16, 4, 4);
    projectile.AddComponent<ProjectileEmitterComponent>(50, 270, 200, true);

    Entity& levelName(manager.AddEntity("LabelLevelName", UI));
    levelName.AddComponent<UILabelComponent>(10,10, "First level", "charriot-font", WHITE_COLOR);

    manager.PrintEntityTree();
    std::cout << "Printing Entity Tree: OK" << std::endl;
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

void Game::HandleCameraMovement() {
    TransformComponent* mainPlayerTransform = chopperEntity.GetComponent<TransformComponent>();
    camera.x = mainPlayerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = mainPlayerTransform->position.y - (WINDOW_HEIGHT / 2);

    camera.x = camera.x < 0 ? 0 : camera.x;
    camera.y = camera.y < 0 ? 0 : camera.y;
    camera.x = camera.x > camera.w ? camera.w : camera.x;
    camera.y = camera.y > camera.h ? camera.h : camera.y;
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

     HandleCameraMovement();
     CheckCollisions();
} 

void Game::Destroy() {
   SDL_DestroyRenderer(renderer);
   SDL_DestroyWindow(window);
   SDL_Quit();
}