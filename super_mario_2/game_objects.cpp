#include "game_objects.hpp"

void SetObjectPos(TObject *obj, float xPos, float yPos) {
    obj->x = xPos;
    obj->y = yPos;
}

void InitObject(TObject *obj, float xPos, float yPos,
                float oWidth, float oHeight, char inType) {
    SetObjectPos(obj, xPos, yPos);
    obj->width     = oWidth;
    obj->height    = oHeight;
    obj->vertSpeed = 0;
    obj->IsFly     = false;
    obj->cType     = inType;
}

bool IsCollision(TObject o1, TObject o2) {
    return ((o1.x + o1.width)  > o2.x) &&
            (o1.x < (o2.x + o2.width))  &&
           ((o1.y + o1.height) > o2.y) &&
            (o1.y < (o2.y + o2.height));
}