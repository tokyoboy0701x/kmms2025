#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const ordo::menu_item ordo::MENU_START_SORTING = {
    "1 - Запуск сортировки", ordo::menu_start_sorting, &ordo::MAIN_MENU
};

const ordo::menu_item ordo::MENU_START_TESTING = {
    "2 - Тестирование", ordo::menu_start_testing, &ordo::MAIN_MENU
};

const ordo::menu_item ordo::MENU_SETTINGS = {
    "3 - Настройки", ordo::menu_settings, &ordo::MAIN_MENU
};

const ordo::menu_item ordo::MENU_GO_BACK = {
    "0 - Выход в главное меню", ordo::menu_go_back, &ordo::MAIN_MENU
};

namespace {
    const ordo::menu_item* const menu_children[] = {
        &ordo::MENU_GO_BACK,
        &ordo::MENU_START_SORTING,
        &ordo::MENU_START_TESTING,
        &ordo::MENU_SETTINGS
    };
    const int menu_size = sizeof(menu_children) / sizeof(menu_children[0]); 
}

const ordo::menu_item ordo::MAIN_MENU = {
    "1 - Главное меню", ordo::show_menu, &ordo::MAIN, menu_children, menu_size
};

const ordo::menu_item ordo::EXIT = {
    "0 - Выход из программы", ordo::exit, &ordo::MAIN
};

namespace {
    const ordo::menu_item* const main_children[] = {
        &ordo::EXIT,
        &ordo::MAIN_MENU
    };
    const int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const ordo::menu_item ordo::MAIN = {
    nullptr, ordo::show_menu, nullptr, main_children, main_size
};