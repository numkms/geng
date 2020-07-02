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

class ArkanoidGameScene: public Scene 
{
private:
     Entity* platform;
     Entity* levelLabel;
     Entity* scoreLabel;
     
     std::vector<Entity*> blocks;
public:    
    void LoadComponents() {
        GetAssetManager().AddFont("Roboto17", "./assets/fonts/Roboto/Roboto-Black.ttf", 50);
        GetAssetManager().AddFont("Roboto14", "./assets/fonts/Roboto/Roboto-Black.ttf", 30);
        
        Entity& mainMenu(GetManager().AddEntity("", UI));
        mainMenu.AddComponent<TransformComponent>(0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
        mainMenu.AddComponent<RectangleComponent>(WHITE_COLOR);
        mainMenu.AddComponent<UILabelComponent>(
            mainMenu.GetComponent<TransformComponent>()->position.x + 10, 
            mainMenu.GetComponent<TransformComponent>()->position.y + 20, 
            "Level 1",
            "Roboto14",
            BLUE_COLOR,
            RED_COLOR
        );

    }

    void Initialize() override {
        Scene::Initialize();
        LoadComponents()
    }

    
    void LoadLevel(int lvlNum) const {
        std::cout << "Loading level" + std::to_string(lvlNum) << std::endl;
    }
};
#endif 