#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../Component.h"
#include "../Game.h"
#include "TransformComponent.h"
#include <string>
#include "../Scene.h";
class ColliderComponent: public Component
{
private:
    SDL_Texture* texture;
    bool markedAsTarget = false;
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect sourceRectangle;
    SDL_Rect destinationRectangle;
    TransformComponent* transform;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height) {
        this->colliderTag = colliderTag;
        std::cout << "TAG" << std::endl;
        this->collider = { 
            x,
            y,
            width,
            height
        };
        std::cout << "Collider" << std::endl;
    }
    
    void Initialize() override {
        std::cout << "Component Initializing" << std::endl;
        if(owner->HasComponent<TransformComponent>()) {
            std::cout << "Has transform component: OK" << std::endl;
            transform = owner->GetComponent<TransformComponent>();
            std::cout << "Getting transform component: OK" << std::endl;
            sourceRectangle = {0, 0, transform->width, transform->height};
            std::cout << "Setting source rectangle: OK" << std::endl;
            destinationRectangle = {collider.x, collider.y, collider.w, collider.h};
            std::cout << "Setting  rectangle: OK" << std::endl;
        }
    }

    void Update(float deltaTime) override {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;

        destinationRectangle.x = collider.x;
        destinationRectangle.y = collider.y;
    }

    void MarkAsTarget(std::string assetName) {
       texture = this->owner->GetManager()->GetScene()->GetAssetManager().GetTexture(assetName);
       markedAsTarget = true;
    }

    void Render() override {
        if(markedAsTarget) {
            std::cout << "Render target mark: OK" << std::endl;
            TextureManager::Draw(texture, {0, 0, transform->width, transform->height}, destinationRectangle, SDL_FLIP_NONE);
        }
    }
};
#endif 