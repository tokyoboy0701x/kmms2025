#pragma once

extern bool key_a;
extern bool key_d;
extern bool key_space;
extern bool key_esc;

void enableRawMode();
void disableRawMode();
void pollKeys();