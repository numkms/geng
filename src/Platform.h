#ifndef PLATFORM_H
#define PLATFORM_H
#include "./Rectangle.h"
#include "./Constants.h"
class Platform : public Rectangle {
    protected:
        float speed = 20;
    public:
        Platform() {
            this->height = 20;
            this->width = WINDOW_WIDTH / 10;
            this->x = WINDOW_WIDTH / 2 - this->width / 2;
            this->y = WINDOW_HEIGHT - 10;
        }
        void MoveRight() {
            this->x = this->x + this->speed;
        }
        
        void MoveLeft() {
            if (this->x > this->width / 2) {
               this->x = this->x - this->speed;
            }
        }
};
    
#endif