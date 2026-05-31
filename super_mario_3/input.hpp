#ifndef INPUT_HPP
#define INPUT_HPP

#include <termios.h>

class Input {
public:
    bool key_a;
    bool key_d;
    bool key_space;
    bool key_esc;

    Input();
    ~Input();
    
    void enable_raw_mode();
    void disable_raw_mode();
    void poll_keys();

private:
    struct termios orig_termios;
    int get_key();
};

#endif