#include <stdio.h>
#include <stdlib.h>
#include "object.hpp"
#include "input.hpp"
#include "map.hpp"
#include "game_objects.hpp"
#include "physics.hpp"
#include "level.hpp"

char    map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick     = NULL;
int     brickLength = 0;
int     level       = 1;

int main() {
    enableRawMode();
    atexit(disableRawMode);

    printf("\033[2J");
    CreateLevel(level);

    do {
        key_a = false;
        key_d = false;
        pollKeys();

        ClearMap();

        if (!mario.IsFly && key_space) mario.vertSpeed = -1.0f;
        if (key_a) HorizonMoveMap( 1.0f);
        if (key_d) HorizonMoveMap(-1.0f);

        if (mario.y > mapHeight) CreateLevel(level);

        VertMoveObject(&mario);
        for (int i = 0; i < brickLength; i++)
            PutObjectOnMap(brick[i]);
        PutObjectOnMap(mario);

        setCur(0, 0);
        ShowMap();
        fflush(stdout);

        Sleep(10);

    } while (!key_esc);

    free(brick);
    printf("\033[2J\033[H");
    return 0;
}