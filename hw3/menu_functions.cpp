#include "menu_functions.hpp"

#include <cstdlib>
#include <iostream>

const ordo::menu_item* ordo::show_menu(const ordo::menu_item* current) {
    std::cout << "===== МЕНЮ =====" << std::endl;
        for (int i = 1; i < current->children_count; i++) {
            std::cout << current->children[i]->title << std::endl;
        }

        std::cout << current->children[0]->title << std::endl;

        std::cout << "Выберите пункт: ";
        
        int user_input;
        std::cin >> user_input;
        std::cout << std::endl;
        
        return current->children[user_input];
}

const ordo::menu_item* ordo::exit(const ordo::menu_item* current) {
    std::exit(0);
}

const ordo::menu_item* ordo::menu_start_sorting(const ordo::menu_item* current) {
    //todo
    std::cout << current->title << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::menu_start_testing(const ordo::menu_item* current) {
    //todo
    std::cout << current->title << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::menu_settings(const ordo::menu_item* current) {
    //todo
    std::cout << current->title << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::menu_go_back(const ordo::menu_item* current) {
    //todo
    return current->parent->parent;
}