#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include "Scene.h"
#include <string>

class SceneManager
{
private:
    std::vector<Scene*> scenes;
    std::map<const std::type_info*, Scene*> sceneByType;
public:
    SceneManager() {
        
    };

    template <typename T, typename... TArgs>
    T& AddScene(TArgs... args) {
        T* newScene(new T(std::forward<TArgs>(args)...));
        newScene->name = typeid(T).name();
        scenes.emplace_back(newScene);
        sceneByType[&typeid(*newScene)] = newScene;
        return *newScene;
    }

    template <typename T>
    void ShowScene() {
        HideAllScenes();
        T* scene =  static_cast<T*>(sceneByType[&typeid(T)]);        
        scene->Initialize();
        scene->isHidden = false;
    }

    void HideAllScenes() {
        for (auto const& x : sceneByType)
        {   
             x.second->isHidden = true;
        }
    }

    void Update(float deltaTime) {
        for(auto& scene: scenes) {
            if(scene->isHidden == false) {
                scene->Update(deltaTime);    
            }
        }        
    }

    void Render() {
        for(auto& scene: scenes) {
            if(scene->isHidden == false) {
                scene->Render();
            }
        }
    }

    
};
#endif