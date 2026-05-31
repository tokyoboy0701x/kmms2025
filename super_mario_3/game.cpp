#include "game.hpp"
#include "constants.hpp"
#include <stdio.h>

Game::Game() : running(true) {}

Game::~Game() {
    printf("\033[2J\033[H");
}

void Game::handle_input() {
    input.key_a = false;
    input.key_d = false;
    input.poll_keys();

    if (!level.get_mario().is_fly && input.key_space) 
        level.get_mario().vert_speed = JUMP_SPEED;
    if (input.key_a) level.horizon_move_map(1.0f);
    if (input.key_d) level.horizon_move_map(-1.0f);
}

void Game::update() {
    if (level.is_game_over()) {
        level.player_dead();
        return;
    }

    level.vert_move_object(&level.get_mario());
    
    if (level.mario_collision()) {
        level.player_dead();
        return;
    }

    for (int i = 0; i < level.get_movings().size(); i++) {
        level.vert_move_object(&level.get_movings()[i]);
        level.horizon_move_object(&level.get_movings()[i]);
        if (level.get_movings()[i].y > MAP_HEIGHT) {
            level.get_movings().erase(level.get_movings().begin() + i);
            i--;
        }
    }
}

void Game::render() {
    renderer.clear();

    for (const auto& brick : level.get_bricks())
        renderer.put_object(brick);

    for (const auto& moving : level.get_movings())
        renderer.put_object(moving);

    renderer.put_object(level.get_mario());
    renderer.put_score(level.get_score());

    renderer.set_cursor(0, 0);
    renderer.show();
    fflush(stdout);
}

void Game::run() {
    input.enable_raw_mode();
    printf("\033[2J");
    level.create_level(1);

    while (running && !input.key_esc) {
        handle_input();
        update();
        render();
        Renderer::sleep_ms(10);
    }
}