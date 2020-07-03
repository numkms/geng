#ifndef ARKANOID_GAME_SCENE_H
#define ARKANOID_GAME_SCENE_H

#include "../EntityManager.h"
#include "../AssetManager.h"
#include "../Game.h"
#include "../Components/TransformComponent.h"
#include "../Components/MenuComponent.h"
#include "../MenuItem.h"
#include "../Components/RectangleComponent.h"
#include "../Components/UILabelComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/MouseControlComponent.h"
#include "../Components/KeyboardControlComponent.h"
#include "../Components/ArkanoidBallComponent.h"

class ArkanoidMenuScene;
extern SceneManager sceneManager;
class ArkanoidGameScene: public Scene 
{
private:
     Entity* room;
     Entity* platform;
     Entity* levelLabel;
     Entity* scoreLabel;
     Entity* ball;

     bool isRuning = false;
     std::vector<Entity*> blocks;
     ArkanoidBallComponent* arkanoidBallComponent;
     ColliderComponent* arkanoidBallCollider;
     void CheckCollisions() {
         for(int i=0; i < blocks.size(); i++) {
            Entity* block = blocks[i]; 
            if(Collision::CheckRectangleCollision(arkanoidBallCollider->collider, block->GetComponent<ColliderComponent>()->collider)) {
                AudioSample* sample = GetAssetManager().GetSample("BlockCollisionSound");
                sample->Play();
                blocks.erase(blocks.begin() + i);
                block->Destroy();
                
                arkanoidBallComponent->MirrorDirections();
            }
            i++;
         }
     }
public:    
    void LoadComponents() {
        GetAssetManager().AddFont("Roboto17", "./assets/fonts/Roboto/Roboto-Black.ttf", 50);
        GetAssetManager().AddFont("Roboto14", "./assets/fonts/Roboto/Roboto-Black.ttf", 16);
        GetAssetManager().AddSample("GameTheme", "./assets/sounds/Track2.ogg", 50, false);
        GetAssetManager().AddSample("BoxCollisionSound", "./assets/sounds/effects/iceball.wav", 50, true);
        GetAssetManager().AddSample("BlockCollisionSound", "./assets/sounds/effects/boom4.wav", 50, true);
        
        Mix_HaltMusic();
        AudioSample * sample  = GetAssetManager().GetSample("GameTheme");
        sample->Play();
        
        Entity& room(GetManager().AddEntity("Room", TILEMAP));
        room.AddComponent<TransformComponent>(0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
        room.AddComponent<RectangleComponent>(WHITE_COLOR);

        Entity& levelLabel(GetManager().AddEntity("LevelLabel", UI));
        levelLabel.AddComponent<UILabelComponent>(
            WINDOW_WIDTH - 20, 
            WINDOW_HEIGHT/2 - 20, 
            "LEVEL 1",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );

        Entity& scoreLabel(GetManager().AddEntity("Score label", UI));
        scoreLabel.AddComponent<UILabelComponent>(
            WINDOW_WIDTH - 20, 
            WINDOW_HEIGHT/2, 
            "SCORE 0",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );



        Entity& platform(GetManager().AddEntity("Platform", PLAYER));
        platform.AddComponent<TransformComponent>(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 20, 0, 0, 150, 20, 1);
        platform.AddComponent<RectangleComponent>(COLOR_PALLETE[rand() % 11]);
        MouseControlComponent& platformMouseControlComponent(platform.AddComponent<MouseControlComponent>());
        platformMouseControlComponent.BindMouseXToTransform();

        Entity& ball(GetManager().AddEntity("Ball", PROJECTILE));
        ball.AddComponent<TransformComponent>(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 40, 0, 0, 20, 20, 1);
        ball.AddComponent<RectangleComponent>(COLOR_PALLETE[rand() % 11]);
        
        arkanoidBallCollider = &ball.AddComponent<ColliderComponent>(
            "PROJECTILE", 
            ball.GetComponent<TransformComponent>()->position.x,
            ball.GetComponent<TransformComponent>()->position.y,
            ball.GetComponent<TransformComponent>()->width,
            ball.GetComponent<TransformComponent>()->height
        );

        arkanoidBallComponent = &ball.AddComponent<ArkanoidBallComponent>(200, room.GetComponent<TransformComponent>());

        BuildLevel();


    }

    void BuildLevel() {
        int width = 74;
        int height = 20;
        int topBlocksCount = 10;
        int offsetPerLine = width / 2;
        int lineLength = 10;
        for (int i = 0; i < 10; i++) {
            for (int m = 0; m < lineLength; m++) {
                Entity& block(GetManager().AddEntity("Block" + std::to_string(i) + std::to_string(m), ENEMY));
                block.AddComponent<TransformComponent>(
                      10 + ((width * m) + i * offsetPerLine + (m * 5)),
                      10 + ((height) * i) + i * 10,
                      0,
                      0, 
                      width,
                      height, 
                      1
                );
                block.AddComponent<ColliderComponent>("ENEMY", 
                    10 + ((width * m) + i * offsetPerLine + (m * 5)),
                    10 + ((height) * i) + i * 10,
                    width, 
                    height
                );
                block.AddComponent<RectangleComponent>(COLOR_PALLETE[rand() % 11]);
                blocks.emplace_back(&block);
            }
            lineLength--;
        }
    }

    void RunGame() {
        if(!isRuning) {
            isRuning = true;
            arkanoidBallComponent->Play();
        }
    }

    void PauseGame() {
        isRuning = false;
    }

    void GameOver() {
        isRuning = false;
        GoMenu();
    }
    
    void ProcessSceneInput() {
        switch (Game::event.type) {
            case SDL_KEYDOWN: {
                if(Game::event.key.keysym.sym == SDLK_ESCAPE) {
                    GoMenu();
                }
                if(Game::event.key.keysym.sym == SDLK_SPACE) {
                    RunGame();
                }    
            }
            default: {
                break;
            }
        }

    }

    void Initialize() override {
        Scene::Initialize();
        LoadComponents();
    }

    void Update(float deltaTime) override {
        ProcessSceneInput();
        
        if(isRuning) {
            CheckCollisions();    
        }

        Scene::Update(deltaTime);
    }

    void GoMenu() {
        sceneManager.ShowScene<ArkanoidMenuScene>();
    }
    void LoadLevel(int lvlNum) const {
        std::cout << "Loading level" + std::to_string(lvlNum) << std::endl;
    }
};
#endif 