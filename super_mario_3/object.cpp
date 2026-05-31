#include "object.hpp"

Object::Object() : x(0), y(0), width(0), height(0), 
                   vert_speed(0), horiz_speed(HORIZ_SPEED), 
                   is_fly(false), type(' ') {}

Object::Object(float x, float y, float width, float height, char type) {
    init(x, y, width, height, type);
}

void Object::set_position(float x, float y) {
    this->x = x;
    this->y = y;
}

void Object::init(float x, float y, float width, float height, char type) {
    set_position(x, y);
    this->width = width;
    this->height = height;
    this->vert_speed = 0;
    this->horiz_speed = HORIZ_SPEED;
    this->is_fly = false;
    this->type = type;
}

void Object::apply_gravity() {
    is_fly = true;
    vert_speed += GRAVITY;
    set_position(x, y + vert_speed);
}

bool Object::is_collision(const Object& other) const {
    return ((x + width) > other.x) && 
           (x < (other.x + other.width)) &&
           ((y + height) > other.y) && 
           (y < (other.y + other.height));
}