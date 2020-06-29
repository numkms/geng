#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "./Color.cpp"
#include <SDL2/SDL.h>

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
        bool hidden = false; 
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
        
        float GetMinX() {
            return this->x - this->width / 2;
        };
        
        float GetMaxX() {
            return this->x + this->width / 2;
        };
        
        float GetMinY() {
            return this->y - this->height / 2;
        };
        
        float GetMaxY() {
            return this->y + this->height / 2;
        };

        bool isCrossingOverBy(Rectangle * rectangle) {
            const SDL_Rect a = {
              (int) this->x,
              (int) this->y,
              (int) this->width,
              (int) this->height
            };

            const SDL_Rect b = {
               (int) rectangle->GetX(), 
               (int) rectangle->GetY(), 
               (int) rectangle->GetWidth(), 
               (int) rectangle->GetHeight(), 
            };
            return SDL_HasIntersection(&a,&b) == SDL_TRUE;
        }


};

    
#endif