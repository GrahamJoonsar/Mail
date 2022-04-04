#ifndef DIRECTION_H
#define DIRECTION_H

typedef struct _Position {
    int x, y;
} Position;

// Possible fptr Directions
const Position UP;
const Position DOWN;
const Position LEFT;
const Position RIGHT;

extern void addPosition(Position* p1, const Position* dir);

#endif