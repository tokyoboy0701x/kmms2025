#pragma once
#include "object.hpp"

void setCur(int x, int y);
void Sleep(int ms);
void ClearMap();
void ShowMap();
bool IsPosInMap(int x, int y);
void PutObjectOnMap(TObject obj);