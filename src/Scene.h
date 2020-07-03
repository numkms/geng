#ifndef SCENE_H
#define SCENE_H

// #include "EntityManager.h";
// #include "AssetManager.h";
#include <iostream>
class AssetManager;
class EntityManager;

class Scene {
    protected:
    EntityManager* manager;
    AssetManager* assetManager;
    public:
    bool isHidden = false;
    Scene() {
        std::cout << "Initilize entity manager" << std::endl;
        manager = new EntityManager(this);
        std::cout << "Initilize entity manager: OK" << std::endl;
        std::cout << "Initilize asset manager" << std::endl;
        assetManager = new AssetManager(this);
        std::cout << "Initilize asset manage: OK" << std::endl;
    };
    virtual void Initialize() {
        
    };
    virtual void Update(float deltaTime) {
        manager->Update(deltaTime);
    };

    virtual void Render() {
        manager->Render();
    };

    AssetManager& GetAssetManager() {
        return *assetManager;
    }

    EntityManager& GetManager() {
        return *manager;
    }
    
    std::string name;
};
#endif