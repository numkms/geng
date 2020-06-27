#ifndef PLATFORM_H
#define PLATFORM_H
#include "./Rectangle.h"

class Platform : public Rectangle {
    public:
        void MoveRight();
        void MoveLeft();
};
    
#endif