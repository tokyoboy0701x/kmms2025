#ifndef GAME_HPP
#define GAME_HPP

#include "level.hpp"
#include "input.hpp"
#include "renderer.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void run();

private:
    Level level;
    Input input;
    Renderer renderer;
    bool running;
    
    void update();
    void render();
    void handle_input();
};

#endif