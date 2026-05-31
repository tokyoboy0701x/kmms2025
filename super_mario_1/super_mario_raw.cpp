#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define mapWidth 80
#define mapHeight 25

typedef struct SObject {
    float x, y;
    float width, height;
    float vertSpeed;
    bool IsFly;
    char cType;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brickLength;
int level = 1;