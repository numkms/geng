#ifndef ARKANOID_SCOREBOARD_H
#define ARKANOID_SCOREBOARD_H

#include "../Scene.h"
#include "Services/ScoreService.h"
#include <iterator>
#include <iostream>
#include "../Game.h"
#include "../Components/TransformComponent.h"
#include "../Components/RectangleCOmponent.h"
#include "../Components/UILabelComponent.h"

class ArkanoidScoreboardScene: public Scene
{
private:
public:
   void Initialize() {
        Scene::Initialize();

        GetAssetManager().AddFont("Roboto50", "./assets/fonts/Roboto/Roboto-Black.ttf", 50);
        GetAssetManager().AddFont("Roboto80", "./assets/fonts/Roboto/Roboto-Black.ttf", 80);

        Entity& title(GetManager().AddEntity("Scoreboard", UI));
        title.AddComponent<UILabelComponent>(
            50,
            20, 
            "Scoreboard.",
            "Roboto80", 
            REDWHITE_COLOR,
            RED_COLOR
        );
        int offset = 140;
        int i = 0;
        for (auto const& x : ScoreService::GetResults())
        {
            if(i > 4) {
                continue;
            }
            Entity& item(GetManager().AddEntity("ScoreboardItem", UI));
            item.AddComponent<UILabelComponent>(
                50,
                offset, std::to_string(i+1) + ". " + x.first + " - " + std::to_string(x.second) + " PTS.",
                "Roboto50", 
                REDWHITE_COLOR,
                 RED_COLOR
            );
            offset = offset + 70;
            i++;
        }
    }

    void Update(float deltaTime) override {
        switch (Game::event.type) {
            case SDL_KEYDOWN: {
                if(Game::event.key.keysym.sym == SDLK_ESCAPE) {
                    GoMenu();
                }
            }
            default: {
                break;
            }
        }
    }

    void GoMenu() {
        sceneManager.ShowScene<ArkanoidMenuScene>();
    }
};
#endif