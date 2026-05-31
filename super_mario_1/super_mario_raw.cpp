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
    float horizSpeed;
} TObject;

char map[mapHeight][mapWidth + 1];
TObject mario;
TObject *brick = NULL;
int brickLength;
TObject *moving = NULL;
int movingLength;
int level = 1;
int score = 0;
int maxLvl = 3;

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
    obj->horizSpeed = 0.2;
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

void PutScoreOnMap() {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
        map[1][i + 5] = c[i];
}

TObject *GetNewBrick() {
    brickLength++;
    brick = (TObject*)realloc(brick, sizeof(*brick) * brickLength);
    return brick + brickLength - 1;
}

TObject *GetNewMoving() {
    movingLength++;
    moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
    return moving + movingLength - 1;
}

void DeleteMoving(int i) {
    movingLength--;
    moving[i] = moving[movingLength];
    moving = (TObject*)realloc(moving, sizeof(*moving) * movingLength);
}

void CreateLevel(int lvl);

void PlayerDead() {
    Sleep(500);
    CreateLevel(level);
}

void MarioCollision() {
    for (int i = 0; i < movingLength; i++) {
        if (!IsCollision(mario, moving[i]))
            continue;

        if (moving[i].cType == 'o') {
            if (mario.IsFly && mario.vertSpeed > 0 &&
                mario.y + mario.height < moving[i].y + moving[i].height * 0.5f) {
                score += 50;
                DeleteMoving(i);
                i--;
                continue;
            } else {
                PlayerDead();
            }
        }
        if (moving[i].cType == '$') {
            score += 100;
            DeleteMoving(i);
            i--;
            continue;
        }
    }
}

void VertMoveObject(TObject *obj) {
    obj->IsFly = true;
    obj->vertSpeed += 0.05f;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);

    for (int i = 0; i < brickLength; i++) {
        if (!IsCollision(*obj, brick[i]))
            continue;

        if (obj->vertSpeed > 0)
            obj->IsFly = false;

        if (brick[i].cType == '?' && obj->vertSpeed < 0 && obj == &mario) {
            brick[i].cType = '-';
            InitObject(GetNewMoving(), brick[i].x, brick[i].y - 3, 3, 2, '$');
            moving[movingLength - 1].vertSpeed = -0.7f;
        }

        obj->y -= obj->vertSpeed;
        obj->vertSpeed = 0;

        if (brick[i].cType == '+') {
            level++;
            if (level > maxLvl) level = 1;
            Sleep(500);
            CreateLevel(level);
        }
        break;
    }
}

void HorizonMoveObject(TObject *obj) {
    obj->x += obj->horizSpeed;
    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(*obj, brick[i])) {
            obj->x -= obj->horizSpeed;
            obj->horizSpeed = -obj->horizSpeed;
            return;
        }
    }
    if (obj->cType == 'o') {
        TObject tmp = *obj;
        VertMoveObject(&tmp);
        if (tmp.IsFly == true) {
            obj->x -= obj->horizSpeed;
            obj->horizSpeed = -obj->horizSpeed;
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
    for (int i = 0; i < movingLength; i++)
        moving[i].x += dx;
    
}

void CreateLevel(int lvl) {
    brickLength = 0;
    brick = (TObject*)realloc(brick, 0);
    movingLength = 0;
    moving = (TObject*)realloc(moving, 0);
    score = 0;
    InitObject(&mario, 39, 10, 3, 3, '@');

    if (lvl == 1) {
        InitObject(GetNewBrick(),  20, 20, 40,  5, '#');
            InitObject(GetNewBrick(),  30, 10,  5,  3, '?');
            InitObject(GetNewBrick(),  50, 10,  5,  3, '?');
        InitObject(GetNewBrick(),  60, 15, 40, 10, '#');
            InitObject(GetNewBrick(),  60,  5, 10,  3, '-');
            InitObject(GetNewBrick(),  70,  5,  5,  3, '?');
            InitObject(GetNewBrick(),  75,  5,  5,  3, '-');
            InitObject(GetNewBrick(),  80,  5,  5,  3, '?');
            InitObject(GetNewBrick(),  85,  5, 10,  3, '?');
        InitObject(GetNewBrick(), 100, 20, 20,  5, '#');
        InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40,  5, '#');
        InitObject(GetNewBrick(), 210, 15, 10, 10, '+');

        InitObject(GetNewMoving(),  25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(),  80, 10, 3, 2, 'o');
    }
    if (lvl == 2) {
		InitObject(GetNewBrick(),  20, 20, 40,  5, '#');
        InitObject(GetNewBrick(),  60, 15, 10, 10, '#');
        InitObject(GetNewBrick(),  80, 20, 40,  5, '#');
        InitObject(GetNewBrick(), 120, 15, 10, 10, '#');
        InitObject(GetNewBrick(), 150, 20, 40,  5, '#');
        InitObject(GetNewBrick(), 210, 15, 10, 10, '+');
        
        InitObject(GetNewMoving(),  25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(),  80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(),  65, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 160, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 175, 10, 3, 2, 'o');
    }
    if (lvl == 3) {
		InitObject(GetNewBrick(),  20, 20, 40,  5, '#');
        InitObject(GetNewBrick(),  80, 20, 15,  5, '#');
        InitObject(GetNewBrick(), 120, 15, 15, 10, '#');
        InitObject(GetNewBrick(), 160, 10, 15, 15, '+');

        InitObject(GetNewMoving(),  25, 10, 3, 2, 'o');
        InitObject(GetNewMoving(),  50, 10, 3, 2, 'o');
        InitObject(GetNewMoving(),  80, 10, 3, 2, 'o');
        InitObject(GetNewMoving(),  90, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 120, 10, 3, 2, 'o');
        InitObject(GetNewMoving(), 130, 10, 3, 2, 'o');
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

        if (mario.y > mapHeight) PlayerDead();

        VertMoveObject(&mario);
        MarioCollision();

        for (int i = 0; i < brickLength; i++)
            PutObjectOnMap(brick[i]);

        for (int i = 0; i < movingLength; i++) {
            VertMoveObject(moving + i);
            HorizonMoveObject(moving + i);
            if (moving[i].y > mapHeight) {
                DeleteMoving(i);
                i--;
                continue;
            }
            PutObjectOnMap(moving[i]);
        }
        PutObjectOnMap(mario);
        PutScoreOnMap();

        setCur(0, 0);
        ShowMap();
        fflush(stdout);

        Sleep(10);

    } while (!key_esc);

    free(brick);
    free(moving);
    printf("\033[2J\033[H");
    return 0;
}
