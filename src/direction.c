#include "direction.h"

const Position UP    = {0, -1};
const Position DOWN  = {0, 1};
const Position LEFT  = {-1, 0};
const Position RIGHT = {1, 0};

void addPosition(Position* p1, const Position* dir){
    p1->x += dir->x;
    p1->y += dir->y;
}