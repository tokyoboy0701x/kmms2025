#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "constants.hpp"

class Object {
public:
    float x, y;
    float width, height;
    float vert_speed;
    float horiz_speed;
    bool  is_fly;
    char  type;

    Object();
    Object(float x, float y, float width, float height, char type);
    
    void set_position(float x, float y);
    void init(float x, float y, float width, float height, char type);
    void apply_gravity();
    bool is_collision(const Object& other) const;
};

#endif