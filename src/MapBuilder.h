#ifndef MAP_BUILDER_H
#define MAP_BUILDER_H
#include "./Map.h"
#include <stdlib.h> 

class MapBuilder {
    int xs[100] = {0,50,100, 150, 200,250,300, 350,400, 450};
    int ys[100] = {100,100,100,100,100,100, 100,100,100,100};
    int width = 76;
    int height = 10;
    int topBlocksCount = 10;
    int offsetPerLine = width / 2;
    
    Color colors[10] = {
        Color(210,128,128,255),
        Color(102,205,170,255), //Ciyan
        Color(240,128,128,255), //Red
        Color(255, 165, 0,255), //Orange
        Color(255,105,180,255), //Pink
        Color(240,230,140,255), //Khaki
        Color(32,178,170,255), //Lightseagreen
        Color(255,215,0,255), //Gold
        Color(240,128,128,255),
        Color(240,128,128,255),
    };
    
    public:
        MapBuilder() {};
        Map * BuildMap() {
            Map * map = new Map();
            int index = 0;
            for (int i = 0; i < 10; i++) {
                for (int m = 0; m < this->topBlocksCount; m++) {
                    Rectangle rect = Rectangle();
                    rect.SetFrame(
                        (this->width * m) + i * this->offsetPerLine + (m * 5),
                        ((this->height) * i) + i * 10,
                        this->width,
                        this->height,
                        this->colors[rand() % 10]
                    );
                    map->AddBlock(rect, index);
                    index++;
                }
                this->topBlocksCount--;
            }
            return map;
        };
};
    
#endif