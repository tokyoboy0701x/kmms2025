#include "physics.hpp"
#include "object.hpp"
#include "game_objects.hpp"
#include "map.hpp"
#include "level.hpp"

void VertMoveObject(TObject *obj) {
    obj->IsFly = false;
    obj->vertSpeed += 0.05f;
    SetObjectPos(obj, obj->x, obj->y + obj->vertSpeed);
    for (int i = 0; i < brickLength; i++) {
        if (IsCollision(*obj, brick[i])) {
            obj->y -= obj->vertSpeed;
            obj->vertSpeed = 0;
            obj->IsFly     = false;
            if (brick[i].cType == '+') {
                level++;
                if (level > 2) level = 1;
                CreateLevel(level);
                Sleep(1000);
            }
            break;
        }
    }
}

void HorizonMoveMap(float dx) {
    mario.x -= dx;
    for (int i = 0; i < brickLength; i++)
        if (IsCollision(mario, brick[i])) {
            mario.x += dx;
            return;
        }
    mario.x += dx;
    for (int i = 0; i < brickLength; i++)
        brick[i].x += dx;
}