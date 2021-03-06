#ifndef KEYBOARD_CONTROL_COMPONENT
#define KEYBOARD_CONTROL_COMPONENT

#include "../Game.h"
#include "../EntityManager.h"
#include "./TransformComponent.h"
#include "./SpriteComponent.h"
#include <string>
class KeyboardControlComponent: public Component {
    public:
        std::string upKey;
        std::string downKey;
        std::string leftKey;
        std::string rightKey;
        std::string actionKey;
        glm::vec2 velocity;

        TransformComponent *transform;
        SpriteComponent *sprite;

        KeyboardControlComponent() {

        }

        KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey, std::string actionKey, glm::vec2 velocity) {
            this->upKey = GetSDLKeyStringCode(upKey);
            this->rightKey = GetSDLKeyStringCode(rightKey);
            this->downKey = GetSDLKeyStringCode(downKey);
            this->leftKey = GetSDLKeyStringCode(leftKey);
            this->actionKey = GetSDLKeyStringCode(actionKey);
            this->velocity = velocity;
        }

        std::string GetSDLKeyStringCode(std::string key) const {
            if (key.compare("up") == 0) return "1073741906";
            if (key.compare("down") == 0) return "1073741905";
            if (key.compare("left") == 0) return "1073741904";
            if (key.compare("right") == 0) return "1073741903";
            if (key.compare("space") == 0) return "32"; 
            return std::to_string(static_cast<int>(key[0]));
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            
            if(owner->HasComponent<SpriteComponent>()) { 
                sprite = owner->GetComponent<SpriteComponent>();
            }
        }
    

        void Update(float deltaTime) override {
            if(Game::event.type == SDL_KEYDOWN) {
                std::string keyCode = std::to_string(Game::event.key.keysym.sym);
                
                if(keyCode.compare(upKey) == 0) {
                    transform->velocity.y = -100;
                    transform->velocity.x = 0;
                    if(owner->HasComponent<SpriteComponent>()) {
                        sprite->Play("UpAnimation");
                    } else {
                        transform->velocity.y = velocity.y;
                    }
                }

                if(keyCode.compare(downKey) == 0) {
                    transform->velocity.y = 100;
                    transform->velocity.x = 0;
                    if(owner->HasComponent<SpriteComponent>()) {
                        sprite->Play("DownAnimation");
                    } else {
                        transform->velocity.y = velocity.y * -1;
                    }
                }

                if(keyCode.compare(leftKey) == 0) {
                    transform->velocity.y = 0;
                    transform->velocity.x = -100;
                    if(owner->HasComponent<SpriteComponent>()) {
                        sprite->Play("DownAnimation");
                    } else {
                        transform->velocity.x = velocity.x * -1;
                    }
                }

                if(keyCode.compare(rightKey) == 0) {
                    transform->velocity.y = 0;
                    transform->velocity.x = 100;
                    if(owner->HasComponent<SpriteComponent>()) {
                        sprite->Play("DownAnimation");
                    } else {
                        transform->velocity.x = velocity.x;
                    }
                }

                if(keyCode.compare(actionKey) == 0) {
                }
            }

            if (Game::event.type == SDL_KEYUP) {
                std::string keyCode = std::to_string(Game::event.key.keysym.sym);
                if (keyCode.compare(upKey) == 0) {
                    transform->velocity.y = 0; 
                }
                if (keyCode.compare(rightKey) == 0) {
                    transform->velocity.x = 0;
                }
                if (keyCode.compare(downKey) == 0) {
                    transform->velocity.y = 0;
                }
                if (keyCode.compare(leftKey) == 0) {
                    transform->velocity.x = 0;
                }
            }  
        }
};
#endif
