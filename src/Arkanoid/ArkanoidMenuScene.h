#ifndef ARKANOID_MENU_SCENE_H
#define ARKANOID_MENU_SCENE_H

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
#include "../AudioManager.h"
#include "../SceneManager.h"

#include "ArkanoidGameScene.h"

extern SceneManager sceneManager;
class ArkanoidMenuScene: public Scene 
{
private:
public:    
    void NewGame() {
        sceneManager.ShowScene<ArkanoidGameScene>();
    }

    void LoadMainMenu() {
        GetAssetManager().AddFont("Roboto17", "./assets/fonts/Roboto/Roboto-Black.ttf", 50);
        GetAssetManager().AddFont("Roboto14", "./assets/fonts/Roboto/Roboto-Black.ttf", 30);
        GetAssetManager().AddSample("MainMenuTheme", "./assets/sounds/Track1.ogg", 50);
        
        Mix_HaltMusic();
        
        AudioSample * sample  = GetAssetManager().GetSample("MainMenuTheme");
        sample->Play();
        
        int menuWrapperTopPadding = 20;
        int menuWrpapperLeftPadding = 10;
        int titleBottomMargin = 70;
        int menuElementBottomMargin = 50;

        //Create an menu for 
        Entity& mainMenu(GetManager().AddEntity("MainMenu", UI));
        mainMenu.AddComponent<TransformComponent>(0, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 1);
        mainMenu.AddComponent<RectangleComponent>(REDWHITE_COLOR);
        mainMenu.AddComponent<UILabelComponent>(
            mainMenu.GetComponent<TransformComponent>()->position.x + menuWrapperTopPadding, 
            mainMenu.GetComponent<TransformComponent>()->position.y + menuWrpapperLeftPadding, 
            "ARKANOID WAPRO",
            "Roboto17",
            WHITE_COLOR,
            LIGHTSEAGREEN_COLOR
        );

        

        Entity& mainMenuPlayItem(manager->AddEntity("MainMenuPlayItem", UI));
        mainMenuPlayItem.AddComponent<UILabelComponent>(
            mainMenu.GetComponent<TransformComponent>()->position.x + 20, 
            mainMenu.GetComponent<TransformComponent>()->position.y + titleBottomMargin + menuElementBottomMargin, 
            "Play", 
            "Roboto14",
            WHITE_COLOR,
            LIGHTSEAGREEN_COLOR
        );
        

        mainMenuPlayItem.AddComponent<TransformComponent>(
            mainMenu.GetComponent<TransformComponent>()->position.x + 20,
            mainMenu.GetComponent<TransformComponent>()->position.y + titleBottomMargin + menuElementBottomMargin,
            0,
            0,
            200,
            30,
            1
        );

        mainMenuPlayItem.AddComponent<ColliderComponent>(
            "MENU_ITEM", 
            mainMenuPlayItem.GetComponent<TransformComponent>()->position.x,
            mainMenuPlayItem.GetComponent<TransformComponent>()->position.y,
            mainMenuPlayItem.GetComponent<TransformComponent>()->width,
            mainMenuPlayItem.GetComponent<TransformComponent>()->height
        );

        MouseControlComponent& mainMenuPlayItemMouseControlComponent(mainMenuPlayItem.AddComponent<MouseControlComponent>());
        mainMenuPlayItemMouseControlComponent.AddCallback("CLICK", [&]{
            this->NewGame();
        });
        
        

        Entity& mainMenuScoreboardItem(GetManager().AddEntity("MainMenuScoreboardItem", UI));
        mainMenuScoreboardItem.AddComponent<UILabelComponent>(
            mainMenu.GetComponent<TransformComponent>()->position.x + 20, 
            mainMenu.GetComponent<TransformComponent>()->position.y + titleBottomMargin + (menuElementBottomMargin * 2), 
            "Scoreboard",
            "Roboto14",
            WHITE_COLOR,
            LIGHTSEAGREEN_COLOR
        );

        Entity& mainMenuExitItem(GetManager().AddEntity("MainMenuExitItem", UI));
        mainMenuScoreboardItem.AddComponent<UILabelComponent>(
            mainMenu.GetComponent<TransformComponent>()->position.x + 20, 
            mainMenu.GetComponent<TransformComponent>()->position.y + titleBottomMargin + (menuElementBottomMargin * 3), 
            "Exit",
            "Roboto14",
            WHITE_COLOR,
            LIGHTSEAGREEN_COLOR
        );


        // std::vector<Entity > menuElements;

        // menuElements.emplace_back(mainMenuPlayItem);
        // menuElements.emplace_back(mainMenuScoreboardItem);
        // menuElements.emplace_back(mainMenuPlayItem);

        // mainMenu.AddComponent<MenuComponent>(menuElements);


    }

    void Initialize() override {
        Scene::Initialize();
        LoadMainMenu();
    }

    
    void LoadLevel(int lvlNum) const {
        std::cout << "Loading level" + std::to_string(lvlNum) << std::endl;
    }
};
#endif 