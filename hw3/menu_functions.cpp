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
    while (user_input < 0 || user_input >= current->children_count) {
        std::cout << "Выбран неверный пункт, введите число от 0 до " << current->children_count - 1;
        std::cout << std::endl;
        std::cin >> user_input;
    }
    std::cout << std::endl;
        
    return current->children[user_input];
}

const ordo::menu_item* ordo::exit(const ordo::menu_item* current) {
    std::exit(0);
}

const ordo::menu_item* ordo::go_back(const ordo::menu_item* current) {
    return current->parent->parent;
}

const ordo::menu_item* ordo::menu_settings(const ordo::menu_item* current) {
    //todo
    std::cout << current->title << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::sortings_quicksort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ВЫПОЛНЕНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::sortings_merge_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ВЫПОЛНЕНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::sortings_heap_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ВЫПОЛНЕНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::sortings_radix_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ВЫПОЛНЕНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::sortings_counting_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ВЫПОЛНЕНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::testing_quicksort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ТЕСТИРОВАНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::testing_merge_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ТЕСТИРОВАНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::testing_heap_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ТЕСТИРОВАНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::testing_radix_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ТЕСТИРОВАНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

const ordo::menu_item* ordo::testing_counting_sort(const ordo::menu_item* current) {
    std::cout << current->title << std::endl;
    //todo
    std::cout << "*ИМИТАЦИЯ ТЕСТИРОВАНИЯ СОРТИРОВКИ*" << std::endl;
    return current->parent;
}

