#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAP_WIDTH 80
#define MAP_HEIGHT 25
#define GRAVITY 0.05f
#define JUMP_SPEED -1.0f
#define HORIZ_SPEED 0.2f
#define COIN_SPEED -0.7f
#define SCORE_ENEMY 50
#define SCORE_COIN 100
#define DEAD_DELAY 500
#define LEVEL_DELAY 500

typedef struct {
    float x, y;
    float width, height;
    float vert_speed;
    float horiz_speed;
    bool is_fly;
    char type;
} Object;

void apply_gravity(Object *obj);
void clear_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]);
void create_level(int lvl, Object *mario, Object **brick, int *brick_count, 
                  Object **moving, int *moving_count, int *score);
void delete_moving(Object **moving, int *moving_count, int i);
void disable_raw_mode();
void enable_raw_mode();
int get_key();
Object *get_new_brick(Object **brick, int *brick_count);
Object *get_new_moving(Object **moving, int *moving_count);
void handle_portal(int *level, int max_level, Object *mario, Object **brick, 
                   int *brick_count, Object **moving, int *moving_count, int *score);
void horizon_move_map(float dx, Object *mario, Object *brick, int brick_count, 
                      Object *moving, int moving_count);
void horizon_move_object(Object *obj, Object *brick, int brick_count,
                         Object *mario, Object **moving, int *moving_count,
                         int *level, int max_level, int *score);
void init_object(Object *obj, float x, float y, float width, float height, char type);
bool is_collision(Object o1, Object o2);
bool is_pos_in_map(int x, int y);
bool mario_collision(Object *mario, Object **moving, int *moving_count, int *score);
void poll_keys(bool *key_a, bool *key_d, bool *key_space, bool *key_esc);
void put_object_on_map(char map[MAP_HEIGHT][MAP_WIDTH + 1], Object obj);
void put_score_on_map(char map[MAP_HEIGHT][MAP_WIDTH + 1], int score);
void set_cursor(int x, int y);
void set_object_pos(Object *obj, float x, float y);
void show_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]);
void sleep_ms(int ms);

void check_brick_collision(Object *obj, Object *mario, Object *brick, int brick_count,
                           Object **moving, int *moving_count, int *level, 
                           int max_level, int *score);
void vert_move_object(Object *obj, Object *mario, Object *brick, int brick_count,
                      Object **moving, int *moving_count, int *level, 
                      int max_level, int *score);

int main() {
    char map[MAP_HEIGHT][MAP_WIDTH + 1];
    Object mario;
    Object *brick = NULL;
    int brick_count;
    Object *moving = NULL;
    int moving_count;
    int level = 1;
    int score = 0;
    int max_level = 3;
    
    bool key_a = false;
    bool key_d = false;
    bool key_space = false;
    bool key_esc = false;

    enable_raw_mode();
    atexit(disable_raw_mode);

    printf("\033[2J");
    create_level(level, &mario, &brick, &brick_count, &moving, &moving_count, &score);

    do {
        key_a = false;
        key_d = false;
        poll_keys(&key_a, &key_d, &key_space, &key_esc);

        clear_map(map);

        if (!mario.is_fly && key_space) mario.vert_speed = JUMP_SPEED;
        if (key_a) horizon_move_map( 1.0f, &mario, brick, brick_count, moving, moving_count);
        if (key_d) horizon_move_map(-1.0f, &mario, brick, brick_count, moving, moving_count);

        if (mario.y > MAP_HEIGHT) {
            sleep_ms(DEAD_DELAY);
            create_level(level, &mario, &brick, &brick_count, &moving, &moving_count, &score);
            continue;
        }

        vert_move_object(&mario, &mario, brick, brick_count, &moving, &moving_count, 
                         &level, max_level, &score);
        
        if (mario_collision(&mario, &moving, &moving_count, &score)) {
            sleep_ms(DEAD_DELAY);
            create_level(level, &mario, &brick, &brick_count, &moving, &moving_count, &score);
            continue;
        }

        for (int i = 0; i < brick_count; i++)
            put_object_on_map(map, brick[i]);

        for (int i = 0; i < moving_count; i++) {
            vert_move_object(&moving[i], &mario, brick, brick_count, &moving, &moving_count,
                             &level, max_level, &score);
            horizon_move_object(&moving[i], brick, brick_count, &mario, &moving, &moving_count,
                                &level, max_level, &score);
            if (moving[i].y > MAP_HEIGHT) {
                delete_moving(&moving, &moving_count, i);
                i--;
                continue;
            }
            put_object_on_map(map, moving[i]);
        }
        put_object_on_map(map, mario);
        put_score_on_map(map, score);

        set_cursor(0, 0);
        show_map(map);
        fflush(stdout);

        sleep_ms(10);

    } while (!key_esc);

    free(brick);
    free(moving);
    printf("\033[2J\033[H");
    return 0;
}

static struct termios orig_termios;

void apply_gravity(Object *obj) {
    obj->is_fly = true;
    obj->vert_speed += GRAVITY;
    set_object_pos(obj, obj->x, obj->y + obj->vert_speed);
}

void clear_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    for (int i = 0; i < MAP_WIDTH; i++)
        map[0][i] = ' ';
    map[0][MAP_WIDTH] = '\0';
    for (int j = 1; j < MAP_HEIGHT; j++)
        sprintf(map[j], "%s", map[0]);
}

void delete_moving(Object **moving, int *moving_count, int i) {
    (*moving_count)--;
    (*moving)[i] = (*moving)[*moving_count];
    *moving = (Object*)realloc(*moving, sizeof(**moving) * (*moving_count));
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
    printf("\033[?25h");
    fflush(stdout);
}

void enable_raw_mode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
    printf("\033[?25l");
    fflush(stdout);
}

int get_key() {
    unsigned char c;
    if (read(STDIN_FILENO, &c, 1) == 1)
        return (int)c;
    return -1;
}

Object *get_new_brick(Object **brick, int *brick_count) {
    (*brick_count)++;
    *brick = (Object*)realloc(*brick, sizeof(**brick) * (*brick_count));
    return *brick + (*brick_count) - 1;
}

Object *get_new_moving(Object **moving, int *moving_count) {
    (*moving_count)++;
    *moving = (Object*)realloc(*moving, sizeof(**moving) * (*moving_count));
    return *moving + (*moving_count) - 1;
}

void horizon_move_map(float dx, Object *mario, Object *brick, int brick_count, 
                      Object *moving, int moving_count) {
    mario->x -= dx;
    for (int i = 0; i < brick_count; i++)
        if (is_collision(*mario, brick[i])) {
            mario->x += dx;
            return;
        }
    mario->x += dx;
    for (int i = 0; i < brick_count; i++)
        brick[i].x += dx;
    for (int i = 0; i < moving_count; i++)
        moving[i].x += dx;
}

void init_object(Object *obj, float x, float y,
                 float width, float height, char type) {
    set_object_pos(obj, x, y);
    obj->width = width;
    obj->height = height;
    obj->vert_speed = 0;
    obj->horiz_speed = HORIZ_SPEED;
    obj->is_fly = false;
    obj->type = type;
}

bool is_collision(Object o1, Object o2) {
    return ((o1.x + o1.width)  > o2.x) && (o1.x < (o2.x + o2.width)) &&
           ((o1.y + o1.height) > o2.y) && (o1.y < (o2.y + o2.height));
}

bool is_pos_in_map(int x, int y) {
    return (x >= 0) && (x < MAP_WIDTH) && (y >= 0) && (y < MAP_HEIGHT);
}

bool mario_collision(Object *mario, Object **moving, int *moving_count, int *score) {
    for (int i = 0; i < *moving_count; i++) {
        if (!is_collision(*mario, (*moving)[i]))
            continue;

        if ((*moving)[i].type == 'o') {
            if (mario->is_fly && mario->vert_speed > 0 &&
                mario->y + mario->height < (*moving)[i].y + (*moving)[i].height * 0.5f) {
                *score += SCORE_ENEMY;
                delete_moving(moving, moving_count, i);
                i--;
                continue;
            } else {
                return true;
            }
        }
        if ((*moving)[i].type == '$') {
            *score += SCORE_COIN;
            delete_moving(moving, moving_count, i);
            i--;
            continue;
        }
    }
    return false;
}

void poll_keys(bool *key_a, bool *key_d, bool *key_space, bool *key_esc) {
    *key_space = false;
    *key_esc = false;

    int c;
    while ((c = get_key()) != -1) {
        if (c == 27) *key_esc = true;
        if (c == ' ') *key_space = true;
        if (c == 'a' || c == 'A') *key_a = true;
        if (c == 'd' || c == 'D') *key_d = true;
    }
}

void put_object_on_map(char map[MAP_HEIGHT][MAP_WIDTH + 1], Object obj) {
    int ix = (int)round(obj.x);
    int iy = (int)round(obj.y);
    int i_width = (int)round(obj.width);
    int i_height = (int)round(obj.height);
    for (int i = ix; i < ix + i_width; i++)
        for (int j = iy; j < iy + i_height; j++)
            if (is_pos_in_map(i, j))
                map[j][i] = obj.type;
}

void put_score_on_map(char map[MAP_HEIGHT][MAP_WIDTH + 1], int score) {
    char c[30];
    sprintf(c, "Score: %d", score);
    int len = strlen(c);
    for (int i = 0; i < len; i++)
        map[1][i + 5] = c[i];
}

void set_cursor(int x, int y) {
    printf("\033[%d;%dH", y + 1, x + 1);
}

void set_object_pos(Object *obj, float x, float y) {
    obj->x = x;
    obj->y = y;
}

void show_map(char map[MAP_HEIGHT][MAP_WIDTH + 1]) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
        map[j][MAP_WIDTH] = '\0';
        printf("%s\n", map[j]);
    }
}

void sleep_ms(int ms) {
    usleep(ms * 1000);
}

void handle_portal(int *level, int max_level, Object *mario, Object **brick, 
                   int *brick_count, Object **moving, int *moving_count, int *score) {
    (*level)++;
    if (*level > max_level) *level = 1;
    sleep_ms(LEVEL_DELAY);
    create_level(*level, mario, brick, brick_count, moving, moving_count, score);
}

void check_brick_collision(Object *obj, Object *mario, Object *brick, int brick_count,
                           Object **moving, int *moving_count, int *level, 
                           int max_level, int *score) {
    for (int i = 0; i < brick_count; i++) {
        if (!is_collision(*obj, brick[i]))
            continue;

        if (obj->vert_speed > 0)
            obj->is_fly = false;

        if (brick[i].type == '?' && obj->vert_speed < 0 && obj == mario) {
            brick[i].type = '-';
            init_object(get_new_moving(moving, moving_count), brick[i].x, brick[i].y - 3, 3, 2, '$');
            (*moving)[*moving_count - 1].vert_speed = COIN_SPEED;
        }

        obj->y -= obj->vert_speed;
        obj->vert_speed = 0;

        if (brick[i].type == '+')
            handle_portal(level, max_level, mario, &brick, &brick_count, moving, moving_count, score);

        break;
    }
}

void vert_move_object(Object *obj, Object *mario, Object *brick, int brick_count,
                      Object **moving, int *moving_count, int *level, 
                      int max_level, int *score) {
    apply_gravity(obj);
    check_brick_collision(obj, mario, brick, brick_count, moving, moving_count, 
                          level, max_level, score);
}

void horizon_move_object(Object *obj, Object *brick, int brick_count,
                         Object *mario, Object **moving, int *moving_count,
                         int *level, int max_level, int *score) {
    obj->x += obj->horiz_speed;
    for (int i = 0; i < brick_count; i++) {
        if (is_collision(*obj, brick[i])) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
            return;
        }
    }
    if (obj->type == 'o') {
        Object tmp = *obj;
        vert_move_object(&tmp, mario, brick, brick_count, moving, moving_count, 
                         level, max_level, score);
        if (tmp.is_fly == true) {
            obj->x -= obj->horiz_speed;
            obj->horiz_speed = -obj->horiz_speed;
        }
    }
}

void create_level(int lvl, Object *mario, Object **brick, int *brick_count, 
                  Object **moving, int *moving_count, int *score) {
    *brick_count  = 0;
    *brick  = (Object*)realloc(*brick, 0);
    *moving_count = 0;
    *moving = (Object*)realloc(*moving, 0);
    *score  = 0;
    init_object(mario, 39, 10, 3, 3, '@');

    switch (lvl) {
        case 1:
            init_object(get_new_brick(brick, brick_count),  20, 20, 40,  5, '#');
            init_object(get_new_brick(brick, brick_count),  30, 10,  5,  3, '?');
            init_object(get_new_brick(brick, brick_count),  50, 10,  5,  3, '?');
            init_object(get_new_brick(brick, brick_count),  60, 15, 40, 10, '#');
            init_object(get_new_brick(brick, brick_count),  60,  5, 10,  3, '-');
            init_object(get_new_brick(brick, brick_count),  70,  5,  5,  3, '?');
            init_object(get_new_brick(brick, brick_count),  75,  5,  5,  3, '-');
            init_object(get_new_brick(brick, brick_count),  80,  5,  5,  3, '?');
            init_object(get_new_brick(brick, brick_count),  85,  5, 10,  3, '?');
            init_object(get_new_brick(brick, brick_count), 100, 20, 20,  5, '#');
            init_object(get_new_brick(brick, brick_count), 120, 15, 10, 10, '#');
            init_object(get_new_brick(brick, brick_count), 150, 20, 40,  5, '#');
            init_object(get_new_brick(brick, brick_count), 210, 15, 10, 10, '+');

            init_object(get_new_moving(moving, moving_count),  25, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count),  80, 10, 3, 2, 'o');
            break;
            
        case 2:
            init_object(get_new_brick(brick, brick_count),  20, 20, 40,  5, '#');
            init_object(get_new_brick(brick, brick_count),  60, 15, 10, 10, '#');
            init_object(get_new_brick(brick, brick_count),  80, 20, 40,  5, '#');
            init_object(get_new_brick(brick, brick_count), 120, 15, 10, 10, '#');
            init_object(get_new_brick(brick, brick_count), 150, 20, 40,  5, '#');
            init_object(get_new_brick(brick, brick_count), 210, 15, 10, 10, '+');

            init_object(get_new_moving(moving, moving_count),  25, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count),  80, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count),  65, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count), 120, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count), 160, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count), 175, 10, 3, 2, 'o');
            break;
            
        case 3:
            init_object(get_new_brick(brick, brick_count),  20, 20, 40,  5, '#');
            init_object(get_new_brick(brick, brick_count),  80, 20, 15,  5, '#');
            init_object(get_new_brick(brick, brick_count), 120, 15, 15, 10, '#');
            init_object(get_new_brick(brick, brick_count), 160, 10, 15, 15, '+');

            init_object(get_new_moving(moving, moving_count),  25, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count),  50, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count),  80, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count),  90, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count), 120, 10, 3, 2, 'o');
            init_object(get_new_moving(moving, moving_count), 130, 10, 3, 2, 'o');
            break;
            
        default:
            break;
    }
}