#pragma once

#include <stdbool.h>

#define mapWidth  80
#define mapHeight 25

typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool  IsFly;
    char  cType;
} TObject;

extern char    map[mapHeight][mapWidth + 1];
extern TObject mario;
extern TObject *brick;
extern int     brickLength;
extern int     level;