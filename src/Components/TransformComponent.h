#ifndef TRANSFORM_COMPONENT_H 
#define TRANSFORM_COMPONENT_H
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"
#include "../Game.h"
#include "SDL2/SDL.h"
class TransformComponent: public Component {
    public:
        glm::vec2 position;
        glm::vec2 velocity;
        int width;
        int height;
        int scale;

        TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s) {
            position = glm::vec2(posX, posY);
            velocity = glm::vec2(velX, velY);
            width = w;
            height = h;
            scale = s;
        } 

        void Initialize() override {

        }

        void Update(float deltaTime) override {
            float nextPositionX = position.x + velocity.x * deltaTime;
            float nextPositionY = position.y + velocity.y * deltaTime;
            if(nextPositionX >= WINDOW_WIDTH - width) {
                nextPositionX = WINDOW_WIDTH - width;
            } 

            if(nextPositionX <= 0) {
                nextPositionX = 0;
            }

            if(nextPositionY >= WINDOW_HEIGHT) {
                nextPositionY = WINDOW_HEIGHT;
            } 

            if(nextPositionY <= 0) {
                nextPositionY = 0;
            }

            position.x = nextPositionX;
            position.y = nextPositionY;
        }

        void Render() override {
        }

};
#endif