#ifndef ENTITY_H
#define ENTITY_H
#include <vector>
#include "Component.h"
#include <string>
#include "EntityManager.h"
#include <map>
#include <iostream>
#include "Constants.h"
class EntityManager;
class Component;

class Entity {
    private:
        EntityManager& manager;
        bool isActive;
        std::vector<Component * > components;
        std::map<const std::type_info*, Component*> componentTypeMap;
    public:
        std::string name;
        Entity (EntityManager& manager);
        Entity (EntityManager& manager, std::string name, LayerType layer);
        LayerType layer;
        void Update(float deltaTime);
        void Render();
        void Destroy();
        bool IsActive() const;
        std::vector<Component*> ComponentsList() const;
    template <typename T, typename... TArgs>
    T& AddComponent(TArgs... args) {
        T* newComponent(new T(std::forward<TArgs>(args)...));
        std::cout << "New component: OK" << std::endl;
        newComponent->owner = this;
        std::cout << "Setting owner: OK" << std::endl;
        newComponent->componentName = typeid(T).name();
        std::cout << "Setting component name: OK" << std::endl;
        components.emplace_back(newComponent);
        std::cout << "Emplacing component: OK" << std::endl;
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        std::cout << "Component Type Map Add: OK" << std::endl;
        newComponent->Initialize();
        std::cout << "Init component: OK" << std::endl;
        return *newComponent;
    }

    template <typename T>
    T* GetComponent() {
        return static_cast<T*>(componentTypeMap[&typeid(T)]);
    }

    template <typename T>
    bool HasComponent() {
        if(componentTypeMap.find(&typeid(T)) != componentTypeMap.end()) {
            return true;
        }
        return false;
    }
};

#endif