#ifndef MAP_H
#define MAP_H
#include "./Rectangle.h"

class Map {
    public:
        Rectangle blocks[90];
        void AddBlock(Rectangle block, int index);
};

#endif