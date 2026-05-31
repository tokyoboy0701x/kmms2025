#include "level.hpp"
#include "object.hpp"
#include "game_objects.hpp"
#include <stdlib.h>

void CreateLevel(int lvl) {
    InitObject(&mario, 39, 10, 3, 3, '@');

    if (lvl == 1) {
        brickLength = 6;
        brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
        InitObject(brick+0,  20, 20, 40,  5, '#');
        InitObject(brick+1,  60, 15, 10, 10, '#');
        InitObject(brick+2,  80, 20, 40,  5, '#');
        InitObject(brick+3, 120, 15, 10, 10, '#');
        InitObject(brick+4, 150, 20, 40,  5, '#');
        InitObject(brick+5, 210, 15, 10, 10, '+');
    }
    if (lvl == 2) {
        brickLength = 4;
        brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
        InitObject(brick+0,  20, 20, 40,  5, '#');
        InitObject(brick+1,  80, 20, 15,  5, '#');
        InitObject(brick+2, 120, 15, 15, 10, '#');
        InitObject(brick+3, 160, 10, 15, 15, '+');
    }
}