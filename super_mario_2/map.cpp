#include "map.hpp"
#include "object.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

void setCur(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void Sleep(int ms) {
    usleep(ms * 1000);
}

void ClearMap() {
    for (int i = 0; i < mapWidth; i++)
        map[0][i] = ' ';
    map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf(map[j], "%s", map[0]);
}

void ShowMap() {
    for (int j = 0; j < mapHeight; j++) {
        map[j][mapWidth] = '\0';
        printf("%s\n", map[j]);
    }
}

bool IsPosInMap(int x, int y) {
    return (x >= 0) && (x < mapWidth) &&
           (y >= 0) && (y < mapHeight);
}

void PutObjectOnMap(TObject obj) {
    int ix      = (int)round(obj.x);
    int iy      = (int)round(obj.y);
    int iWidth  = (int)round(obj.width);
    int iHeight = (int)round(obj.height);
    for (int i = ix; i < ix + iWidth; i++)
        for (int j = iy; j < iy + iHeight; j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.cType;
}