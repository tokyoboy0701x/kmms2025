#include "level.hpp"
#include "constants.hpp"
#include "renderer.hpp"

Level::Level() : level(1), score(0) {
    mario = Object(39, 10, 3, 3, CHAR_MARIO);
}

void Level::delete_moving(int index) {
    movings.erase(movings.begin() + index);
}

void Level::handle_portal() {
    level++;
    if (level > max_level) level = 1;
    Renderer::sleep_ms(LEVEL_DELAY);
    create_level(level);
}

void Level::player_dead() {
    Renderer::sleep_ms(DEAD_DELAY);
    create_level(level);
}

void Level::apply_gravity(Object* obj) {
    obj->apply_gravity();
}

void Level::check_brick_collision(Object* obj) {
    for (int i = 0; i < bricks.size(); i++) {
        if (!obj->is_collision(bricks[i]))
            continue;

        if (obj->vert_speed > 0)
            obj->is_fly = false;

        if (bricks[i].type == CHAR_QUESTION && obj->vert_speed < 0 && obj == &mario) {
            bricks[i].type = CHAR_QUESTION_USED;
            Object coin;
            coin.init(bricks[i].x, bricks[i].y - 3, 3, 2, CHAR_COIN);
            coin.vert_speed = COIN_SPEED;
            movings.push_back(coin);
        }

        obj->y -= obj->vert_speed;
        obj->vert_speed = 0;

        if (bricks[i].type == CHAR_PORTAL)
            handle_portal();

        break;
    }
}

void Level::vert_move_object(Object* obj) {
    apply_gravity(obj);
    check_brick_collision(obj);
}

bool Level::mario_collision() {
    for (int i = 0; i < movings.size(); i++) {
        if (!mario.is_collision(movings[i]))
            continue;

        if (movings[i].type == CHAR_ENEMY) {
            if (mario.is_fly && mario.vert_speed > 0 &&
                mario.y + mario.height < movings[i].y + movings[i].height * 0.5f) {
                score += SCORE_ENEMY;
                delete_moving(i);
                i--;
                continue;
            } else {
                return true;
            }
        }
        if (movings[i].type == CHAR_COIN) {
            score += SCORE_COIN;
            delete_moving(i);
            i--;
            continue;
        }
    }
    return false;
}

void Level::horizon_move_object(Object* obj) {
    obj->x += obj->horiz_speed;
    for (int i = 0; i < bricks.size(); i++) {
        if (obj->is_collision(bricks[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    }
    if (obj->type == CHAR_ENEMY) {
        Object tmp = *obj;
        vert_move_object(&tmp);
        if (tmp.is_fly == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void Level::horizon_move_map(float dx) {
    mario.x -= dx;
    for (int i = 0; i < bricks.size(); i++)
        if (mario.is_collision(bricks[i])) {
            mario.x += dx;
            return;
        }
    mario.x += dx;
    for (int i = 0; i < bricks.size(); i++)
        bricks[i].x += dx;
    for (int i = 0; i < movings.size(); i++)
        movings[i].x += dx;
}

void Level::create_level(int lvl) {
    bricks.clear();
    movings.clear();
    score = 0;
    mario.init(39, 10, 3, 3, CHAR_MARIO);
    level = lvl;

    switch (lvl) {
        case 1:
            bricks.push_back(Object(20, 20, 40,  5, CHAR_BRICK));
            bricks.push_back(Object(30, 10,  5,  3, CHAR_QUESTION));
            bricks.push_back(Object(50, 10,  5,  3, CHAR_QUESTION));
            bricks.push_back(Object(60, 15, 40, 10, CHAR_BRICK));
            bricks.push_back(Object(60,  5, 10,  3, CHAR_QUESTION_USED));
            bricks.push_back(Object(70,  5,  5,  3, CHAR_QUESTION));
            bricks.push_back(Object(75,  5,  5,  3, CHAR_QUESTION_USED));
            bricks.push_back(Object(80,  5,  5,  3, CHAR_QUESTION));
            bricks.push_back(Object(85,  5, 10,  3, CHAR_QUESTION));
            bricks.push_back(Object(100, 20, 20,  5, CHAR_BRICK));
            bricks.push_back(Object(120, 15, 10, 10, CHAR_BRICK));
            bricks.push_back(Object(150, 20, 40,  5, CHAR_BRICK));
            bricks.push_back(Object(210, 15, 10, 10, CHAR_PORTAL));

            movings.push_back(Object(25, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(80, 10, 3, 2, CHAR_ENEMY));
            break;
            
        case 2:
            bricks.push_back(Object(20, 20, 40,  5, CHAR_BRICK));
            bricks.push_back(Object(60, 15, 10, 10, CHAR_BRICK));
            bricks.push_back(Object(80, 20, 40,  5, CHAR_BRICK));
            bricks.push_back(Object(120, 15, 10, 10, CHAR_BRICK));
            bricks.push_back(Object(150, 20, 40,  5, CHAR_BRICK));
            bricks.push_back(Object(210, 15, 10, 10, CHAR_PORTAL));

            movings.push_back(Object(25, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(80, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(65, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(120, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(160, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(175, 10, 3, 2, CHAR_ENEMY));
            break;
            
        case 3:
            bricks.push_back(Object(20, 20, 40,  5, CHAR_BRICK));
            bricks.push_back(Object(80, 20, 15,  5, CHAR_BRICK));
            bricks.push_back(Object(120, 15, 15, 10, CHAR_BRICK));
            bricks.push_back(Object(160, 10, 15, 15, CHAR_PORTAL));

            movings.push_back(Object(25, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(50, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(80, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(90, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(120, 10, 3, 2, CHAR_ENEMY));
            movings.push_back(Object(130, 10, 3, 2, CHAR_ENEMY));
            break;
            
        default:
            break;
    }
}

bool Level::is_game_over() const {
    return mario.y > MAP_HEIGHT;
}