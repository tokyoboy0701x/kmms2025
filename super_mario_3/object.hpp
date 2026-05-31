#ifndef OBJECT_HPP
#define OBJECT_HPP

#define HORIZ_SPEED  0.2f
#define GRAVITY      0.05f
#define COIN_SPEED  -0.7f

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