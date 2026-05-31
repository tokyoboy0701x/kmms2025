#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define mapWidth     80
#define mapHeight    25
#define GRAVITY      0.05f
#define JUMP_SPEED  -1.0f
#define HORIZ_SPEED  0.2f
#define COIN_SPEED  -0.7f
#define SCORE_ENEMY  50
#define SCORE_COIN   100
#define DEAD_DELAY   500
#define LEVEL_DELAY  500

typedef struct {
    float x, y;
    float width, height;
    float vert_speed;
    float horiz_speed;
    bool  is_fly;
    char  type;
} Object;

typedef struct {
    char   map[mapHeight][mapWidth + 1];
    Object mario;
    Object *brick;
    int    brick_count;
    Object *moving;
    int    moving_count;
    int    level;
    int    score;
    int    max_level;
    bool   key_a;
    bool   key_d;
    bool   key_space;
    bool   key_esc;
} GameState;

static struct termios orig_termios;

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\033[?25l");
    fflush(stdout);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf("\033[?25h");
    fflush(stdout);
}

int get_key() {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return (int)c;
    return -1;
}

void poll_keys(GameState *state) {
    state->key_space = false;
    state->key_esc   = false;

    int c;
    while ((c = get_key()) != -1) {
        if (c == 27)              state->key_esc   = true;
        if (c == ' ')             state->key_space = true;
        if (c == 'a' || c == 'A') state->key_a     = true;
        if (c == 'd' || c == 'D') state->key_d     = true;
    }
}

void set_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void sleep_ms(int ms) {
    usleep(ms * 1000);
}

void clear_map(GameState *state) {
    for (int i = 0; i < mapWidth; i++)
        state->map[0][i] = ' ';
    state->map[0][mapWidth] = '\0';
    for (int j = 1; j < mapHeight; j++)
        sprintf(state->map[j], "%s", state->map[0]);
}

void show_map(GameState *state) {
    for (int j = 0; j < mapHeight; j++) {
        state->map[j][mapWidth] = '\0';
        printf("%s\n", state->map[j]);
    }
}

void set_object_pos(Object *obj, float x, float y) {
    obj->x = x;
    obj->y = y;
}

void init_object(Object *obj, float x, float y,
                 float width, float height, char type) {
    set_object_pos(obj, x, y);
    obj->width       = width;
    obj->height      = height;
    obj->vert_speed  = 0;
    obj->horiz_speed = HORIZ_SPEED;
    obj->is_fly      = false;
    obj->type        = type;
}

bool is_collision(Object o1, Object o2) {
    return ((o1.x + o1.width)  > o2.x) && (o1.x < (o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

bool is_pos_in_map(int x, int y) {
    return (x >= 0) && (x < mapWidth) && (y >= 0) && (y < mapHeight);
}

void put_object_on_map(GameState *state, Object obj) {
    int ix       = (int)round(obj.x);
    int iy       = (int)round(obj.y);
    int i_width  = (int)round(obj.width);
    int i_height = (int)round(obj.height);
    for (int i = ix; i < ix + i_width; i++)
        for (int j = iy; j < iy + i_height; j++)
            if (is_pos_in_map(i, j))
                state->map[j][i] = obj.type;
}

void put_score_on_map(GameState *state) {
    char c[30];
    sprintf(c, "Score: %d", state->score);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
        state->map[1][i + 5] = c[i];
}

Object *get_new_brick(GameState *state) {
    state->brick_count++;
    state->brick = (Object*)realloc(state->brick, sizeof(*state->brick) * state->brick_count);
    return state->brick + state->brick_count - 1;
}

Object *get_new_moving(GameState *state) {
    state->moving_count++;
    state->moving = (Object*)realloc(state->moving, sizeof(*state->moving) * state->moving_count);
    return state->moving + state->moving_count - 1;
}

void delete_moving(GameState *state, int i) {
    state->moving_count--;
    state->moving[i] = state->moving[state->moving_count];
    state->moving = (Object*)realloc(state->moving, sizeof(*state->moving) * state->moving_count);
}

void create_level(GameState *state, int lvl);

void player_dead(GameState *state) {
    sleep_ms(DEAD_DELAY);
    create_level(state, state->level);
}

void handle_portal(GameState *state) {
    state->level++;
    if (state->level > state->max_level) state->level = 1;
    sleep_ms(LEVEL_DELAY);
    create_level(state, state->level);
}

void apply_gravity(Object *obj) {
    obj->is_fly = true;
    obj->vert_speed += GRAVITY;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
}

void check_brick_collision(GameState *state, Object *obj) {
    for (int i = 0; i < state->brick_count; i++) {
        if (!is_collision(*obj, state->brick[i]))
            continue;

        if (obj->vert_speed > 0)
            obj->is_fly = false;

        if (state->brick[i].type == '?' && obj->vert_speed < 0 && obj == &state->mario) {
            state->brick[i].type = '-';
            init_object(get_new_moving(state), state->brick[i].x, state->brick[i].y - 3, 3, 2, '$');
            state->moving[state->moving_count - 1].vert_speed = COIN_SPEED;
        }

        obj->y -= obj->vert_speed;
        obj->vert_speed = 0;

        if (state->brick[i].type == '+')
            handle_portal(state);

        break;
    }
}

void vert_move_object(GameState *state, Object *obj) {
    apply_gravity(obj);
    check_brick_collision(state, obj);
}

void mario_collision(GameState *state) {
    for (int i = 0; i < state->moving_count; i++) {
        if (!is_collision(state->mario, state->moving[i]))
            continue;

        if (state->moving[i].type == 'o') {
            if (state->mario.is_fly && state->mario.vert_speed > 0 &&
                state->mario.y + state->mario.height < state->moving[i].y + state->moving[i].height * 0.5f) {
                state->score += SCORE_ENEMY;
                delete_moving(state, i);
                i--;
                continue;
            } else {
                player_dead(state);
            }
        }
        if (state->moving[i].type == '$') {
            state->score += SCORE_COIN;
            delete_moving(state, i);
            i--;
            continue;
        }
    }
}

void horizon_move_object(GameState *state, Object *obj) {
    obj->x += obj->horiz_speed;
    for (int i = 0; i < state->brick_count; i++) {
        if (is_collision(*obj, state->brick[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    }
    if (obj->type == 'o') {
        Object tmp = *obj;
        vert_move_object(state, &tmp);
        if (tmp.is_fly == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void horizon_move_map(GameState *state, float dx) {
    state->mario.x -= dx;
    for (int i = 0; i < state->brick_count; i++)
        if (is_collision(state->mario, state->brick[i])) {
            state->mario.x += dx;
            return;
        }
    state->mario.x += dx;
    for (int i = 0; i < state->brick_count; i++)
        state->brick[i].x += dx;
    for (int i = 0; i < state->moving_count; i++)
        state->moving[i].x += dx;
}

void create_level(GameState *state, int lvl) {
    state->brick_count  = 0;
    state->brick  = (Object*)realloc(state->brick,  0);
    state->moving_count = 0;
    state->moving = (Object*)realloc(state->moving, 0);
    state->score  = 0;
    init_object(&state->mario, 39, 10, 3, 3, '@');

    if (lvl == 1) {
        init_object(get_new_brick(state),  20, 20, 40,  5, '#');
        init_object(get_new_brick(state),  30, 10,  5,  3, '?');
        init_object(get_new_brick(state),  50, 10,  5,  3, '?');
        init_object(get_new_brick(state),  60, 15, 40, 10, '#');
        init_object(get_new_brick(state),  60,  5, 10,  3, '-');
        init_object(get_new_brick(state),  70,  5,  5,  3, '?');
        init_object(get_new_brick(state),  75,  5,  5,  3, '-');
        init_object(get_new_brick(state),  80,  5,  5,  3, '?');
        init_object(get_new_brick(state),  85,  5, 10,  3, '?');
        init_object(get_new_brick(state), 100, 20, 20,  5, '#');
        init_object(get_new_brick(state), 120, 15, 10, 10, '#');
        init_object(get_new_brick(state), 150, 20, 40,  5, '#');
        init_object(get_new_brick(state), 210, 15, 10, 10, '+');

        init_object(get_new_moving(state),  25, 10, 3, 2, 'o');
        init_object(get_new_moving(state),  80, 10, 3, 2, 'o');
    }
    if (lvl == 2) {
        init_object(get_new_brick(state),  20, 20, 40,  5, '#');
        init_object(get_new_brick(state),  60, 15, 10, 10, '#');
        init_object(get_new_brick(state),  80, 20, 40,  5, '#');
        init_object(get_new_brick(state), 120, 15, 10, 10, '#');
        init_object(get_new_brick(state), 150, 20, 40,  5, '#');
        init_object(get_new_brick(state), 210, 15, 10, 10, '+');

        init_object(get_new_moving(state),  25, 10, 3, 2, 'o');
        init_object(get_new_moving(state),  80, 10, 3, 2, 'o');
        init_object(get_new_moving(state),  65, 10, 3, 2, 'o');
        init_object(get_new_moving(state), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(state), 160, 10, 3, 2, 'o');
        init_object(get_new_moving(state), 175, 10, 3, 2, 'o');
    }
    if (lvl == 3) {
        init_object(get_new_brick(state),  20, 20, 40,  5, '#');
        init_object(get_new_brick(state),  80, 20, 15,  5, '#');
        init_object(get_new_brick(state), 120, 15, 15, 10, '#');
        init_object(get_new_brick(state), 160, 10, 15, 15, '+');

        init_object(get_new_moving(state),  25, 10, 3, 2, 'o');
        init_object(get_new_moving(state),  50, 10, 3, 2, 'o');
        init_object(get_new_moving(state),  80, 10, 3, 2, 'o');
        init_object(get_new_moving(state),  90, 10, 3, 2, 'o');
        init_object(get_new_moving(state), 120, 10, 3, 2, 'o');
        init_object(get_new_moving(state), 130, 10, 3, 2, 'o');
    }
}

int main() {
    GameState state = {0};
    state.max_level = 3;
    state.level = 1;
    
    enable_raw_mode();
    atexit(disable_raw_mode);

    printf("\033[2J");
    create_level(&state, state.level);

    do {
        state.key_a = false;
        state.key_d = false;
        poll_keys(&state);

        clear_map(&state);

        if (!state.mario.is_fly && state.key_space) state.mario.vert_speed = JUMP_SPEED;
        if (state.key_a) horizon_move_map(&state,  1.0f);
        if (state.key_d) horizon_move_map(&state, -1.0f);

        if (state.mario.y > mapHeight) player_dead(&state);

        vert_move_object(&state, &state.mario);
        mario_collision(&state);

        for (int i = 0; i < state.brick_count; i++)
            put_object_on_map(&state, state.brick[i]);

        for (int i = 0; i < state.moving_count; i++) {
            vert_move_object(&state, state.moving + i);
            horizon_move_object(&state, state.moving + i);
            if (state.moving[i].y > mapHeight) {
                delete_moving(&state, i);
                i--;
                continue;
            }
            put_object_on_map(&state, state.moving[i]);
        }
        put_object_on_map(&state, state.mario);
        put_score_on_map(&state);

        set_cursor(0, 0);
        show_map(&state);
        fflush(stdout);

        sleep_ms(10);

    } while (!state.key_esc);

    free(state.brick);
    free(state.moving);
    printf("\033[2J\033[H");
    return 0;
}