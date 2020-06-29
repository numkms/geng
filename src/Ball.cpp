#include "./Rectangle.h"
#ifndef BALLTYPES
#define BALLTYPES
enum BallHeightDirection {
    top,
    bottom,
    noneHeightDirection
};

enum BallWidthDirection {
    left,
    right,
    noneWidthDirection
};

struct BallDirection {
    BallHeightDirection heightDirection;
    BallWidthDirection widthDirection;
};

class Ball : public Rectangle {
    protected: 
        BallDirection direction;
    public:
        Ball(float x, float y) {
            this->x = x;
            this->y = y;
            this->width = 10;
            this->height = 10;
            this->direction = { noneHeightDirection, noneWidthDirection };
        }
        
        void SetPosition(float x, float y) {
            this->x = x;
            this->y = y;
        };

        BallDirection GetDirection() {
            return this->direction;
        }

        void SetDirection(BallDirection direction) {
            this->direction = direction;
        };
};
#endif