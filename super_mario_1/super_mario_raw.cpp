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

static struct termios orig_termios;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\033[?25l");
    fflush(stdout);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf("\033[?25h");
    fflush(stdout);
}

int getKey() {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return (int)c;
    return -1;
}

static bool key_a = false;
static bool key_d = false;
static bool key_space = false;
static bool key_esc = false;

void pollKeys() {
    key_space = false;
    key_esc = false;

    int c;
    while ((c = getKey()) != -1) {
        if (c == 27)  key_esc = true;
        if (c == ' ') key_space = true;
        if (c == 'a' || c == 'A') key_a = true;
        if (c == 'd' || c == 'D') key_d = true;
    }
}

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

void SetObjectPos(TObject *obj, float xPos, float yPos) {
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos, float oWidth, float oHeight, char inType) {
    SetObjectPos(obj, xPos, yPos);
    obj->width  = oWidth;
    obj->height = oHeight;
    obj->vertSpeed = 0;
    obj->IsFly = false;
    obj->cType  = inType;
}

bool IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width)  > o2.x) && (o1.x < (o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

bool IsPosInMap(int x, int y) {
    return (x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight);
}

void PutObjectOnMap(TObject obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int iWidth  = (int)round(obj.width);
    int iHeight = (int)round(obj.height);
    for (int i = ix; i < ix + iWidth; i++)
        for (int j = iy; j < iy + iHeight; j++)
            if (IsPosInMap(i, j))
                map[j][i] = obj.cType;
}

void VertMoveObject(TObject *obj) {
    obj->IsFly = false;
    obj->vertSpeed += 0.05f;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);
    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(*obj, brick[i])) {
            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly = false;
            if (brick[i].cType == '+') {
                level++;
                if (level > 2) level = 1;
                CreateLevel(level);
                Sleep(1000);
            }
            break;
        }
    }
}

void HorizonMoveMap(float dx) {
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++)
        if (IsCollision(mario, brick[i])) {
            mario.x += dx;
            return;
        }
    mario.x += dx;
    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;
}

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
