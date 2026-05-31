#include "renderer.hpp"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

Renderer::Renderer() {
    clear();
}

void Renderer::clear() {
    for (int i = 0; i < MAP_WIDTH; i++)
        map[0][i] = ' ';
    map[0][MAP_WIDTH] = '\0';
    for (int j = 1; j < MAP_HEIGHT; j++)
        sprintf(map[j], "%s", map[0]);
}

void Renderer::show() {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        map[j][MAP_WIDTH] = '\0';
        printf("%s\n", map[j]);
    }
}

void Renderer::set_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

bool Renderer::is_pos_in_map(int x, int y) {
    return (x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT);
}

void Renderer::put_object(const Object& obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int i_width = (int)round(obj.width);
    int i_height = (int)round(obj.height);
    
    for (int i = ix; i < ix + i_width; i++)
        for (int j = iy; j < iy + i_height; j++)
            if (is_pos_in_map(i, j))
                map[j][i] = obj.type;
}

void Renderer::put_score(int score) {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
        map[1][i + 5] = c[i];
}

void Renderer::sleep_ms(int ms) {
    usleep(ms * 1000);
}