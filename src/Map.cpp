#include "./Rectangle.h"
#include "./Map.h"

void Map::AddBlock(Rectangle block, int index) {
    this->blocks[index] = block;
}

