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
#include "../Components/ProjectileEmitterComponent.h"
#include "../Utilities/Timer.h"
#include "Services/ScoreService.h"

class ArkanoidMenuScene;
extern SceneManager sceneManager;

class ArkanoidGameScene: public Scene 
{
private:
     Timer timer = Timer();

     Entity* room;
     Entity* platform;
     Entity* levelLabel;
     Entity* scoreLabel;
     Entity* timerLabel;
     Entity* ball;
     Entity* bonus;

     bool isRuning = false;
     bool debounce = true;
     bool isBonusApplied = false;

     unsigned int timeForLevel = 60;
     unsigned int lives = 3;
     unsigned int score = 0;  
     unsigned int scorePointsForBlockHit = 150;
    
     
     SDL_Rect deadZone = {0, WINDOW_HEIGHT, WINDOW_WIDTH, 1};

     unsigned int  currentTime = 0;
    
     std::string timerLabelValue = "60 sec";
     std::string livesLabelValue = "<3 3";

     ArkanoidBallComponent* arkanoidBallComponent;
     
     ColliderComponent* arkanoidBallCollider;
     ColliderComponent* platformCollider;
     ColliderComponent* bonusCollider;
     
     TransformComponent* platformTransportComponent;
     

     UILabelComponent* timerUiLabelComponent;
     UILabelComponent* levelUiLabelComponent;
     UILabelComponent* scoreUiLabelComponent;
     UILabelComponent* livesUiLabelComponent;
    
     const std::string LONG_PLATFORM_BONUS_NAME = "Long";
     const std::string SHORT_PLATFORM_BONUS_NAME = "Short";
     const std::string FAST_BALL_BONUS_NAME = "Speed";

     std::map< std::string, std::function<void()> > bonuses;
     bool isBonusLogicRunning = false;
     
     std::vector<std::string> bonuseNames = {
         LONG_PLATFORM_BONUS_NAME,
         SHORT_PLATFORM_BONUS_NAME,
         FAST_BALL_BONUS_NAME
     };

     void InitBonuses() {  
         this->bonuses[LONG_PLATFORM_BONUS_NAME] = ([&]() {
            std::cout << "Setting scale" << std::endl; 
            this->platformTransportComponent->scale = 3;
            std::cout << "Scale setted" << std::endl; 
            this->bonus->Destroy();
            timer.setTimeout([&]() {    
                std::cout << "Return first scale" << std::endl; 
                this->platformTransportComponent->scale = 2;
                std::cout << "Scale returned" << std::endl; 
                std::cout << "Destroy entity" << std::endl; 
                this->isBonusApplied = false;
                this->isBonusLogicRunning = false;
                std::cout << "Entity destroyed" << std::endl; 
            }, 5000);
        });

        this->bonuses[SHORT_PLATFORM_BONUS_NAME] = ([&]() {
            std::cout << "Setting scale" << std::endl; 
            this->platformTransportComponent->scale = 1;
            std::cout << "Scale setted" << std::endl; 
            this->bonus->Destroy();
            timer.setTimeout([&]() {    
                std::cout << "Return first scale" << std::endl; 
                this->platformTransportComponent->scale = 2;
                std::cout << "Scale returned" << std::endl; 
                std::cout << "Destroy entity" << std::endl; 
                this->isBonusApplied = false;
                this->isBonusLogicRunning = false;
                std::cout << "Entity destroyed" << std::endl; 
            }, 5000);
        });

        this->bonuses[FAST_BALL_BONUS_NAME] = ([&]() {
            std::cout << "Setting scale" << std::endl; 
            this->arkanoidBallComponent->velocity = this->arkanoidBallComponent->velocity * 2; 
            std::cout << "Scale setted" << std::endl; 
            this->bonus->Destroy();
            timer.setTimeout([&]() {    
                this->arkanoidBallComponent->velocity = this->arkanoidBallComponent->velocity / 2; 
                std::cout << "Return first scale" << std::endl; 
                std::cout << "Scale returned" << std::endl; 
                std::cout << "Destroy entity" << std::endl; 
                this->isBonusApplied = false;
                this->isBonusLogicRunning = false;
                std::cout << "Entity destroyed" << std::endl; 
            }, 5000);
        });
     } 
     
     int GetBallCenterX() {
        int ballWidth = arkanoidBallCollider->collider.w;
        return arkanoidBallCollider->collider.x + ballWidth / 2;
     }

     int GetBallCenterY() {
         int ballHeight = arkanoidBallCollider->collider.h;
        return arkanoidBallCollider->collider.y + ballHeight / 2;
     }

     int GetPlatformCenterX() {
        int platformWidth = platformCollider->collider.w;
        return platformCollider->collider.x + platformWidth / 2;
     }

     int GetBlockCenterX(Entity * block) {
        return block->GetComponent<ColliderComponent>()->collider.x + block->GetComponent<ColliderComponent>()->collider.w / 2;
     }

     int GetBlockCenterY(Entity * block) {
        return block->GetComponent<ColliderComponent>()->collider.y + block->GetComponent<ColliderComponent>()->collider.h / 2;
     }

     void CheckCollisions(float deltaTime) {        
         
         std::string currentDirectionX, currentDirectionY;
         std::tie(currentDirectionX, currentDirectionY) = arkanoidBallComponent->GetDirection();
         std::cout << currentDirectionY + currentDirectionX << std::endl;
         
         if(Collision::CheckRectangleCollision(arkanoidBallCollider->collider, deadZone) && currentDirectionY == "BOTTOM") {
             this->lives --;
             this->livesUiLabelComponent->SetText("<3 " + std::to_string(this->lives)); 
             arkanoidBallComponent->SetDirection(currentDirectionX, "TOP");
             if(lives == 0) {
                 GameOver();
             }
         }
        
         if(Collision::CheckRectangleCollision(arkanoidBallCollider->collider, platformCollider->collider) && currentDirectionY == "BOTTOM") {
            
            if(GetBallCenterX() > GetPlatformCenterX()) {
                arkanoidBallComponent->SetDirection("RIGHT", "TOP");
            } else {
                arkanoidBallComponent->SetDirection("LEFT", "TOP");
            }

            AudioSample* sample = GetAssetManager().GetSample("BlockCollisionSound");
        
            sample->Play();        
            return;
         }

        if(
            isBonusApplied &&
            Collision::CheckRectangleCollision(bonusCollider->collider, platformCollider->collider) &&
            isBonusLogicRunning == false
        ) {

            std::cout << "Run " + bonus->name << std::endl;
            this->bonuses[bonus->name]();
            AudioSample * sample  = GetAssetManager().GetSample("BonusActivatedSound");
            sample->Play();
            isBonusLogicRunning = true;
        }

        if(
            isBonusApplied &&
            Collision::CheckRectangleCollision(bonusCollider->collider, deadZone)
        ) {
             isBonusApplied = false;
             AudioSample * sample  = GetAssetManager().GetSample("BonusDeathZoneSound");
             sample->Play();
         }
         
        for(auto& entity: manager->GetEntities()) {
            if (
                entity->name != "Platform" &&
                entity->name != "Ball" && 
                std::find(bonuseNames.begin(), bonuseNames.end(), entity->name) == bonuseNames.end() && 
                entity->HasComponent<ColliderComponent>() &&
                Collision::CheckRectangleCollision(arkanoidBallCollider->collider, entity->GetComponent<ColliderComponent>()->collider)
            ) {
                AudioSample* sample = GetAssetManager().GetSample("PlatformCollisionSound");
                sample->Play();    
                
                std::string directionX = "LEFT";
                std::string directionY = "TOP";
                
                this->score+= this->scorePointsForBlockHit;
                this->scoreUiLabelComponent->SetText("SCORE " + std::to_string(this->score));

                if(GetBlockCenterY(entity) > GetBallCenterY()) {
                    directionY = "TOP";
                } else {
                    directionY = "BOTTOM";
                }

                if(GetBlockCenterX(entity) > GetBallCenterX()) {
                    directionX = directionY == "TOP" ? "RIGHT" : "LEFT";
                } else {
                    directionX = directionY == "TOP" ? "LEFT" : "RIGHT";
                }

                arkanoidBallComponent->SetDirection(directionX, directionY);

                entity->Destroy();      

                if(isBonusApplied == false && random() % 4 == 3) {
                    std::string randomBonusName = bonuseNames[random() % (bonuseNames.size() + 1)];
                    AudioSample * sample  = GetAssetManager().GetSample("BonusSpawnSound");
                    sample->Play();
                    bonus = &GetManager().AddEntity(randomBonusName, ENEMY);
                    bonus->AddComponent<TransformComponent>(
                        entity->GetComponent<ColliderComponent>()->collider.x,
                        entity->GetComponent<ColliderComponent>()->collider.y,
                        0,
                        0,
                        entity->GetComponent<ColliderComponent>()->collider.w,
                        entity->GetComponent<ColliderComponent>()->collider.h,
                        1
                    );
                    bonusCollider = &bonus->AddComponent<ColliderComponent>(
                        randomBonusName, 
                        entity->GetComponent<ColliderComponent>()->collider.x,
                        entity->GetComponent<ColliderComponent>()->collider.y,
                        entity->GetComponent<ColliderComponent>()->collider.w,
                        entity->GetComponent<ColliderComponent>()->collider.h
                    );
                    bonus->AddComponent<UILabelComponent>(entity->GetComponent<ColliderComponent>()->collider.x,
                    entity->GetComponent<ColliderComponent>()->collider.y, randomBonusName, "Roboto12", RED_COLOR, BLUE_COLOR);
                    bonus->AddComponent<ProjectileEmitterComponent>(300, 90, WINDOW_HEIGHT, false);

                    isBonusApplied = true;    
                }
            }
        }
     }

public:    
    
     void LoadComponents() {
         GetAssetManager().AddFont("Roboto12", "./assets/fonts/Roboto/Roboto-Black.ttf", 14);
        GetAssetManager().AddFont("Roboto17", "./assets/fonts/Roboto/Roboto-Black.ttf", 50);
        GetAssetManager().AddFont("Roboto14", "./assets/fonts/Roboto/Roboto-Black.ttf", 16);
        GetAssetManager().AddSample("GameTheme", "./assets/sounds/Track2.ogg", 50, false);

        GetAssetManager().AddSample("BoxCollisionSound", "./assets/sounds/effects/iceball.wav", 50, true);
        GetAssetManager().AddSample("PlatformCollisionSound", "./assets/sounds/effects/slimeball.wav", 50, true);
        GetAssetManager().AddSample("BlockCollisionSound", "./assets/sounds/effects/boom4.wav", 50, true);

        GetAssetManager().AddSample("BonusSpawnSound", "./assets/sounds/effects/rlaunch.wav", 50, true);
        GetAssetManager().AddSample("BonusActivatedSound", "./assets/sounds/effects/flaunch.wav", 50, true);
        GetAssetManager().AddSample("BonusDeathZoneSound", "./assets/sounds/effects/rlaunch.wav", 50, true);
        
        
        Mix_HaltMusic();
        AudioSample * sample  = GetAssetManager().GetSample("GameTheme");
        sample->Play();
        
        Entity& room(GetManager().AddEntity("Room", TILEMAP));
        room.AddComponent<TransformComponent>(0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
        room.AddComponent<RectangleComponent>(WHITE_COLOR);

        Entity& levelLabel(GetManager().AddEntity("LevelLabel", UI));
        UILabelComponent& levelUiLabelComponent =levelLabel.AddComponent<UILabelComponent>(
            WINDOW_WIDTH - 200, 
            WINDOW_HEIGHT/2 - 20, 
            "LEVEL 1",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );

        Entity& scoreLabel(GetManager().AddEntity("Score label", UI));
        scoreUiLabelComponent = &scoreLabel.AddComponent<UILabelComponent>(
            WINDOW_WIDTH - 200, 
            WINDOW_HEIGHT/2, 
            "SCORE 0",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );

        Entity& timerLabel(GetManager().AddEntity("Time label", UI));
        timerUiLabelComponent = &timerLabel.AddComponent<UILabelComponent>(
            WINDOW_WIDTH - 200, 
            WINDOW_HEIGHT/2 - 40, 
            "TIME 00",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );

        Entity& livesLabel(GetManager().AddEntity("Time label", UI));
        livesUiLabelComponent = &livesLabel.AddComponent<UILabelComponent>(
            WINDOW_WIDTH - 200, 
            WINDOW_HEIGHT/2 - 60, 
            ("<3 " + std::to_string(lives)),
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );
        




        Entity& platform(GetManager().AddEntity("Platform", PLAYER));
        platformTransportComponent = &platform.AddComponent<TransformComponent>(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 20, 0, 0, 75, 10, 2);
        platform.AddComponent<RectangleComponent>(COLOR_PALLETE[rand() % 11]);
        platformCollider = &platform.AddComponent<ColliderComponent>("PLAYER", WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 20, 150, 20);
        MouseControlComponent& platformMouseControlComponent(platform.AddComponent<MouseControlComponent>());
        platformMouseControlComponent.BindMouseXToTransform();

        Entity& ball(GetManager().AddEntity("Ball", PROJECTILE));
        ball.AddComponent<TransformComponent>(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 40, 0, 0, 15, 15, 1);
        ball.AddComponent<RectangleComponent>(COLOR_PALLETE[rand() % 11]);
        
        arkanoidBallCollider = &ball.AddComponent<ColliderComponent>(
            "PROJECTILE", 
            WINDOW_WIDTH / 2 - 25,
            WINDOW_HEIGHT - 40,
            15,
            15
        );

        arkanoidBallComponent = &ball.AddComponent<ArkanoidBallComponent>(500, room.GetComponent<TransformComponent>());

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
            }
            lineLength--;
        }
    }

     void RunGame() {
        if(!isRuning) {
            isRuning = true;
            arkanoidBallComponent->Play();
            timer.setInterval([&]() {
                this->currentTime--;
            }, 1000); 
        }
    }

     void PauseGame() {
        isRuning = false;
    }

     void GameOver() {
        isRuning = false;
        ScoreService::AddScoreResult("Tester", this->score);
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
        timer.stop();
        currentTime = timeForLevel;
        lives = 3;
        score = 0;
        LoadComponents();
        InitBonuses();
    }

     void Update(float deltaTime) override {
        ProcessSceneInput();
        Scene::Update(deltaTime);
        if(isRuning) {
            CheckCollisions(deltaTime);    
            this->timerUiLabelComponent->SetText("TIME " + std::to_string(currentTime));
            if(this->currentTime == 0) {
                GameOver();
            } 
        }
    }

     void GoMenu() {
        sceneManager.ShowScene<ArkanoidMenuScene>();
    }
    
     void LoadLevel(int lvlNum) const {
        std::cout << "Loading level" + std::to_string(lvlNum) << std::endl;
    }
};
#endif 