#ifndef PROJECTILE_EMITTER_COMPONENT_H
#define PROJECTILE_EMITTER_COMPONENT_H
#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "TransformComponent.h"

class ProjectileEmitterComponent: public Component {
    private:
        TransformComponent* transform;
        glm::vec2 origin;
        int speed;
        int range;
        float angleRad;
        bool isLooped;
    public:
        ProjectileEmitterComponent(int speed, float angleDeg, int range, bool shouldLoop) {
            this->speed = speed;
            this->range = range;
            this->isLooped = shouldLoop;
            this->angleRad = glm::radians(static_cast<float>(angleDeg));
        }

        void Initialize() override {
            transform = owner->GetComponent<TransformComponent>();
            origin = glm::vec2(transform->position.x, transform->position.y);
            transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
        }

        void Update(float deltaTime) override {
            if (glm::distance(transform->position, origin) > range) {
                if(isLooped) {
                    transform->position.x = origin.x;
                    transform->position.y = origin.y;
                 } else {
                     owner->Destroy();
                 }
            }
        } 
};
#endif