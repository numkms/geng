#include "EntityManager.h"
#include <iostream>
#include "Collision.h"
#include "Components/ColliderComponent.h"

void EntityManager::ClearData() {
    for(auto& entity: entities) {
        entity->Destroy();
    }
}

bool EntityManager::HasNoEntities() {
    return entities.size() == 0;
}

void EntityManager::DestroyInactiveEntities() {
    for(int i = 0; i < entities.size(); i++) {
        if(!entities[i]->IsActive()) {
            entities.erase(entities.begin() + i);
        }
    }
}

void EntityManager::Update(float deltaTime) {
    for(auto& entity: entities) {
        entity->Update(deltaTime);
    }
}

void EntityManager::Render() {
    for(int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++) {
        for(auto& entity: GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
            entity->Render();
        }
    }
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
    Entity * entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
    return entities;
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
    //TODO: Зарефакторить пожже
    std::vector<Entity *> selectedEntities;
    
    for(auto& entity: entities) {
        if(entity->layer == layer) {
            selectedEntities.emplace_back(entity);
        }
    }

    return selectedEntities;
}


unsigned int EntityManager::GetEntityCount() const {
    return entities.size();
}

void EntityManager::PrintEntityTree() {
    for(auto& entity: entities) {
        std::cout << entity->name << std::endl;
        for(auto& component: entity->ComponentsList()) {
            std::cout << "   " + component->componentName << std::endl;
        }
    }
}



CollisionType EntityManager::CheckEntityCollisions() const {

    //Плохое решение нужно переделать на отличное от n^2
    for(auto& thisEntity: entities) {
        std::cout << "Entities loop" << std::endl;
        if(thisEntity->HasComponent<ColliderComponent>()) {
            
            ColliderComponent* thisCollider = thisEntity->GetComponent<ColliderComponent>();

            for(auto& thatEntity: entities) {

                if(thisEntity->name.compare(thatEntity->name) != 0 && thatEntity->HasComponent<ColliderComponent>()) {
                    ColliderComponent* thatCollider = thatEntity->GetComponent<ColliderComponent>();
                    if(Collision::CheckRectangleCollision(thisCollider->collider, thatCollider->collider)) {
                        if(
                            thisCollider->colliderTag.compare("PLAYER") == 0 &&
                            thatCollider->colliderTag.compare("ENEMY") == 0
                        ) {
                            return PLAYER_ENEMY;
                        }

                        if(
                            thisCollider->colliderTag.compare("PLAYER") == 0 &&
                            thatCollider->colliderTag.compare("PROJECTILE") == 0
                        ) {
                            return PLAYER_PROJECTILE;
                        }

                        if(
                            thisCollider->colliderTag.compare("ENEMY") == 0 &&
                            thatCollider->colliderTag.compare("FRIENDLY_PROJECTILE") == 0
                        ) {
                            return ENEMY_PROJECTILE;
                        }

                        if(
                            thisCollider->colliderTag.compare("PLAYER") == 0 &&
                            thatCollider->colliderTag.compare("LEVEL_COMPLETE") == 0
                        ) {
                            return PLAYER_LEVEL_COMPLETE;
                        }
                    
                    }
                }
            }
        }
        return NO;   
    }
}
