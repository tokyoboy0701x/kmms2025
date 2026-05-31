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

