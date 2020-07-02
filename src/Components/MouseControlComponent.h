#ifndef MOUSE_CONTROL_COMPONENT_H
#define MOUSE_CONTROL_COMPONENT_H
#include <SDL2/SDL.h>
#include "../Component.h"
#include "ColliderComponent.h"
#include "../Collision.h"

typedef void (*MouseCallbackPointer)();

class MouseControlComponent: public Component
{
private:
    std::map<std::string, std::function<void()>> callbacks;
    std::vector<std::string> currentEvents = {};
    SDL_Rect mouseRect;

    void AddToCurrentEventsList(std::string eventType) {
        currentEvents.emplace_back(eventType);
    }

    bool IsEventInCurrentEventsList(std::string eventType) {
        return std::find(currentEvents.begin(), currentEvents.end(), eventType) != currentEvents.end();
    }

    bool IsEventBinded(std::string eventType) {
        return callbacks.count(eventType) != 0;
    }

    void RemoveEventFromCurrentEventsList(std::string eventType) {
        currentEvents.erase(std::find(currentEvents.begin(), currentEvents.end(), eventType));
    }

public:
    MouseControlComponent(/* args */);
    ~MouseControlComponent();

    void Initialize() {
        mouseRect = {0, 0, 1, 1};
    }
    
    void AddCallback(std::string eventType, std::function<void()> lambda) {
         callbacks[eventType] = lambda;
    }

    void Update(float deltaTime) override {
        SDL_GetMouseState(&mouseRect.x, &mouseRect.y);

        //HOVERING LOGIC 
        if(this->owner->HasComponent<ColliderComponent>()) {
             if(Collision::CheckRectangleCollision(this->owner->GetComponent<ColliderComponent>()->collider, mouseRect)) {
                 if(this->owner->HasComponent<UILabelComponent>()) {
                     this->owner->GetComponent<UILabelComponent>()->MakeHovered();
                 }


                //CLICKED LOGIC 
                switch(Game::event.type) {
                    case SDL_MOUSEBUTTONDOWN: {
                        if(IsEventBinded("CLICK") && IsEventInCurrentEventsList("CLICK") == false) {
                            callbacks["CLICK"]();
                            AddToCurrentEventsList("CLICK");
                        } 
                    }
                    case SDL_MOUSEBUTTONUP:  {
                        if(IsEventInCurrentEventsList("CLICK")) {
                            RemoveEventFromCurrentEventsList("CLICK");
                        }
                    }
                }
             } else {
                 if(this->owner->HasComponent<UILabelComponent>()) {
                     this->owner->GetComponent<UILabelComponent>()->MakeDefault();
                 }
                 
             } 
        }

    }
};

MouseControlComponent::MouseControlComponent(/* args */)
{
}

MouseControlComponent::~MouseControlComponent()
{
}

#endif