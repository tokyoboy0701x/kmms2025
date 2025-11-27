#include <iostream>

#include "menu_functions.hpp"

namespace {
    const ordo::menu_item* show_menu(const ordo::menu_item* current) {
        for (int i = 1; i < current->children_count; i++) {
            std::cout << current->children[i]->title << std::endl;
        }

        std::cout << current->children[0]->title << std::endl;

        int user_input;
        std::cout << "Выберите пункт > " << std::endl;
        std::cin >> user_input;
            
        return current->children[user_input];
    }
}
const ordo::menu_item* ordo::exit(const ordo::menu_item* current) {
    std::exit(0);
}

const ordo::menu_item* ordo::go_back(const ordo::menu_item* current) {
    return current->parent->parent;
}

const ordo::menu_item* ordo::function(const ordo::menu_item* current) {
    std::cout << "ФУНКЦИЯ ВЫПОЛНЕНА" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::show_for_layer1(const ordo::menu_item* current) {
    std::cout << "=== ГЛАВНОЕ МЕНЮ ===" << std::endl;
    return show_menu(current);
}

const ordo::menu_item* ordo::show_for_layer2(const ordo::menu_item* current) {
    std::cout << "=== ВТОРОЙ УРОВЕНЬ МЕНЮ ===" << std::endl;
    return show_menu(current);
}

const ordo::menu_item* ordo::show_for_layer3(const ordo::menu_item* current) {
    std::cout << "=== ТРЕТИЙ УРОВЕНЬ ДРУГИЕ ТЕХНОЛОГИИ ===" << std::endl;
    return show_menu(current);
}

