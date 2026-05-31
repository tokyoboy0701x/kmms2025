#ifndef LEVEL_HPP
#define LEVEL_HPP

#include "object.hpp"
#include <vector>

class Level {
public:
    Level();
    
    void create_level(int lvl);
    bool is_game_over() const;
    void player_dead();
    
    void vert_move_object(Object* obj);
    void horizon_move_object(Object* obj);
    void horizon_move_map(float dx);
    bool mario_collision();
    
    Object& get_mario() { return mario; }
    int get_score() const { return score; }
    const std::vector<Object>& get_bricks() const { return bricks; }
    std::vector<Object>& get_movings() { return movings; }

private:
    std::vector<Object> bricks;
    std::vector<Object> movings;
    Object mario;
    int level;
    int score;
    static const int max_level = 3;
    
    void apply_gravity(Object* obj);
    void check_brick_collision(Object* obj);
    void handle_portal();
    void delete_moving(int index);
};

#endif