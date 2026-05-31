#include "input.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

static struct termios orig_termios;

bool key_a     = false;
bool key_d     = false;
bool key_space = false;
bool key_esc   = false;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN]  = 0;
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

static int getKey() {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return (int)c;
    return -1;
}

void pollKeys() {
    key_space = false;
    key_esc   = false;

    int c;
    while ((c = getKey()) != -1) {
        if (c == 27)            key_esc   = true;
        if (c == ' ')           key_space = true;
        if (c == 'a' || c == 'A') key_a   = true;
        if (c == 'd' || c == 'D') key_d   = true;
    }
}