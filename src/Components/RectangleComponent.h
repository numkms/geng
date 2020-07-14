#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "../Component.h"
#include "TransformComponent.h"
#include <SDL2/SDL.h>
class RectangleComponent: public Component
{
private:
    TransformComponent* transform; 
    SDL_Color color;
    SDL_Rect  rectangle;
public:
    RectangleComponent(SDL_Color color): color(color) {
        
    };
    
    void Initialize() override {
        transform = owner->GetComponent<TransformComponent>();
    }

    void Update(float deltaTime) override {
        rectangle = {static_cast<int>(transform->position.x), static_cast<int>(transform->position.y), transform->width * transform->scale, transform->height * transform->scale};
    } 

    void Render() override {
        TextureManager::Draw(rectangle, color);
    }
};
#endif