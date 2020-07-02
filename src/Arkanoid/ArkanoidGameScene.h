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

class ArkanoidMenuScene;
extern SceneManager sceneManager;
class ArkanoidGameScene: public Scene 
{
private:
     Entity* room;
     Entity* platform;
     Entity* levelLabel;
     Entity* scoreLabel;

     std::vector<Entity*> blocks;
public:    
    void LoadComponents() {
        GetAssetManager().AddFont("Roboto17", "./assets/fonts/Roboto/Roboto-Black.ttf", 50);
        GetAssetManager().AddFont("Roboto14", "./assets/fonts/Roboto/Roboto-Black.ttf", 30);

        GetAssetManager().AddSample("GameTheme", "./assets/sounds/Track2.ogg", 50);
        Mix_HaltMusic();
        AudioSample * sample  = GetAssetManager().GetSample("GameTheme");
        sample->Play();
        
        Entity& room(GetManager().AddEntity("Room", TILEMAP));
        room.AddComponent<TransformComponent>(0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
        room.AddComponent<RectangleComponent>(WHITE_COLOR);

        Entity& levelLabel(GetManager().AddEntity("LevelLabel", UI));
        levelLabel.AddComponent<UILabelComponent>(
            10, 
            10, 
            "LEVEL 1",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );

        Entity& scoreLabel(GetManager().AddEntity("Score label", UI));
        scoreLabel.AddComponent<UILabelComponent>(
            10, 
            45, 
            "SCORE 0",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );



        Entity& platform(GetManager().AddEntity("Platform", PLAYER));
        platform.AddComponent<TransformComponent>(WINDOW_WIDTH / 2 - 25, WINDOW_HEIGHT - 20, 0, 0, 150, 20, 1);
        platform.AddComponent<RectangleComponent>(RED_COLOR);
        platform.AddComponent<KeyboardControlComponent>(" ", "right", " ", "left", "space", glm::vec2(50, 0));
        MouseControlComponent& platformMouseControlComponent(platform.AddComponent<MouseControlComponent>());
        platformMouseControlComponent.BindMouseXToTransform();
    }


    void ProcessSceneInput() {
        switch (Game::event.type) {
            case SDL_QUIT: {
        
                break;
            }
            case SDL_KEYDOWN: {
                if(Game::event.key.keysym.sym == SDLK_ESCAPE) {
                    sceneManager.ShowScene<ArkanoidMenuScene>();
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
        Scene::Update(deltaTime);
    }

    void GoMenu() {

    }
    void LoadLevel(int lvlNum) const {
        std::cout << "Loading level" + std::to_string(lvlNum) << std::endl;
    }
};
#endif 