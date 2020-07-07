#ifndef ARKANOID_BALL_COMPONENT_H
#define ARKANOID_BALL_COMPONENT_H
#include "../Game.h"
#include "TransformComponent.h"
const std::string DIRECTION_TOP = "TOP";
const std::string DIRECTION_BOTTOM = "BOTTOM";
const std::string DIRECTION_LEFT = "LEFT";
const std::string DIRECTION_RIGHT = "RIGHT";
const std::string DIRECTION_NO = "NO";

class ArkanoidBallComponent: public Component
{
public:
    int velocity;
private:
    TransformComponent* transform;
    TransformComponent* roomTransform;

    int originVelocity;
    
    std::string directionX = DIRECTION_NO;
    std::string directionY = DIRECTION_NO;
    
    void ChangeDirectionIfNeeded() {
        std::cout << "Height:" + std::to_string(roomTransform->height) << std::endl;
        std::cout << "Width:" + std::to_string(roomTransform->width) << std::endl;
        // printf(tranform.position.x);
        std::cout << "Y:" + std::to_string(transform->position.y) << std::endl;
        std::cout << "X:" + std::to_string(transform->position.x) << std::endl;
        if((int) transform->position.x <= 0) {
            directionX = "RIGHT";
            PlayChangeDirectionSound();
            std::cout << "TO RIGHT" << std::endl;
        }

        if((int) transform->position.y <= 0) {
            directionY = "BOTTOM";
            PlayChangeDirectionSound();
            std::cout << "BOTTOM" << std::endl;
        }

        if((int) transform->position.x >= roomTransform->width) {
            directionX = "LEFT";
            PlayChangeDirectionSound();
            std::cout << "LEFT" << std::endl;
        }

        if((int) transform->position.y >= roomTransform->height) {
            directionY = "TOP";
            PlayChangeDirectionSound();
            std::cout << "TOP" << std::endl;
        }
        
    }

  

    void PlayChangeDirectionSound() {
        AudioSample* sample(this->owner->GetManager()->GetScene()->GetAssetManager().GetSample("BoxCollisionSound"));
        sample->Play();
    }

    void SetNewPosition(float deltaTime) {
        if(directionX == "LEFT") {
            this->transform->position.x -= (velocity / 2) * deltaTime;
        }
        if(directionX == "RIGHT") {
            this->transform->position.x += (velocity / 2) * deltaTime;
        }
        if(directionY == "TOP") {
            this->transform->position.y -= velocity * deltaTime;
        }
        if(directionY == "BOTTOM") {
            this->transform->position.y += velocity * deltaTime;
            std::cout << "Y INCREASED" << std::endl;
        }
    }

    void ProcessMoving(float deltaTime) {
       ChangeDirectionIfNeeded();
       SetNewPosition(deltaTime);
    }   

public:
    ArkanoidBallComponent(int velocity, TransformComponent* roomTransform);
    
    void MirrorDirections() {
        MirrorXDirection();
        MirrorYDirection();
    }
    
    void MirrorXDirection() {
        directionX = directionX == "LEFT" ? "RIGHT" : "LEFT";
    }

    void MirrorYDirection() {
        directionY = directionY == "TOP" ? "BOTTOM" : "TOP";
    }

    void SetDirection(std::string x, std::string y) {
        directionX = x;
        directionY = y;
    }

    std::tuple<std::string, std::string> GetDirection() {
        return std::tuple<std::string, std::string>(directionX, directionY);
    }

    void Play() {
        if(directionX == DIRECTION_NO && directionY == DIRECTION_NO && velocity == originVelocity) {
            directionX = rand() % 2 == 0 ? "LEFT" : "RIGHT";
            directionY = "TOP";
        } else {
            velocity = originVelocity;
        }
    }   

    void Pause() {
        velocity = 0;
    }

    void Update(float deltaTime) override {
        ProcessMoving(deltaTime);
    }

    void Initialize() override {
        if (this->owner->HasComponent<TransformComponent>()) {
            transform = this->owner->GetComponent<TransformComponent>();
        }
    }        
};

ArkanoidBallComponent::ArkanoidBallComponent(int velocity, TransformComponent* roomTransform)
: velocity(velocity), roomTransform(roomTransform), originVelocity(velocity) {

}


#endif