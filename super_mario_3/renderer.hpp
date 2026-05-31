#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "object.hpp"
#include "constants.hpp"

class Renderer {
public:
    Renderer();
    
    void clear();
    void show();
    void set_cursor(int x, int y);
    void put_object(const Object& obj);
    void put_score(int score);
    static void sleep_ms(int ms);
    static bool is_pos_in_map(int x, int y);

private:
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
};

#endif