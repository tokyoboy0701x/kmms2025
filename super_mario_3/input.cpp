#include "input.hpp"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>

Input::Input() : key_a(false), key_d(false), key_space(false), key_esc(false) {}

Input::~Input() {
    disable_raw_mode();
}

void Input::enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\033[?25l");
    fflush(stdout);
}

void Input::disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf("\033[?25h");
    fflush(stdout);
}

int Input::get_key() {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return (int)c;
    return -1;
}

void Input::poll_keys() {
    key_space = false;
    key_esc = false;

    int c;
    while ((c = get_key()) != -1) {
        if (c == 27) key_esc = true;
        if (c == ' ') key_space = true;
        if (c == 'a' || c == 'A') key_a = true;
        if (c == 'd' || c == 'D') key_d = true;
    }
}