#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "./Color.cpp"

class Rectangle {
    protected:
        float x;
        float y;
        float width;
        float height;
        Color color = {25,25,25,25};
    public:
        Rectangle();
        ~Rectangle();
        void SetFrame(float x, float y, float width, float height, Color color) {
            this->height = height;
            this->width = width;
            this->color = color;
            this->x = x;
            this->y = y;    
        };
        float GetWidth() { return this->width; };
        float GetHeight() { return this->height; };
        Color GetColor() { return this->color; };
        float GetX() { return this->x; };
        float GetY() { return this->y; };
};

    
#endif