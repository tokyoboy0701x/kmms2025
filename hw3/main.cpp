#include <iostream>

#include "menu.hpp"
#include "menu_functions.hpp"
#include "menu_items.hpp"

int main() {
    const ordo::menu_item* current = &ordo::MAIN;
    
    do {
        current = current->func(current);
    } while (true);

    return 0;
}