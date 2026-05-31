#pragma once
#include "object.hpp"

void SetObjectPos(TObject *obj, float xPos, float yPos);
void InitObject(TObject *obj, float xPos, float yPos,
                float oWidth, float oHeight, char inType);
bool IsCollision(TObject o1, TObject o2);