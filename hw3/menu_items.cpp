#include "menu_items.hpp"

#include <cstddef>

#include "menu_functions.hpp"

const ordo::menu_item ordo::TESTING_QUICKSORT = {
    "1 - Протестировать быструю сортировку", ordo::testing_quicksort, &ordo::MENU_START_TESTING
};

const ordo::menu_item ordo::TESTING_MERGE_SORT = {
    "2 - Протестировать сортировку слиянием", ordo::testing_merge_sort, &ordo::MENU_START_TESTING
};

const ordo::menu_item ordo::TESTING_HEAP_SORT = {
    "3 - Протестировать пирамидальную сортировку", ordo::testing_heap_sort, &ordo::MENU_START_TESTING
};

const ordo::menu_item ordo::TESTING_RADIX_SORT = {
    "4 - Протестировать поразрядную сортировку", ordo::testing_radix_sort, &ordo::MENU_START_TESTING
};

const ordo::menu_item ordo::TESTING_COUNTING_SORT = {
    "5 - Протестировать сортировку подсчетом", ordo::testing_counting_sort, &ordo::MENU_START_TESTING
};

const ordo::menu_item ordo::TESTING_GO_BACK = {
    "0 - Выход в меню", ordo::go_back, &ordo::MENU_START_TESTING
};

namespace {
    const ordo::menu_item* const testing_children[] = {

        &ordo::TESTING_GO_BACK,
        &ordo::TESTING_QUICKSORT,
        &ordo::TESTING_MERGE_SORT,
        &ordo::TESTING_HEAP_SORT,
        &ordo::TESTING_RADIX_SORT,
        &ordo::TESTING_COUNTING_SORT
    };
    const int testing_size = sizeof(testing_children) / sizeof(testing_children[0]);
}

const ordo::menu_item ordo::SORTINGS_QUICKSORT = {
    "1 - Быстрая сортировка", ordo::sortings_quicksort, &ordo::MENU_START_SORTING
};

const ordo::menu_item ordo::SORTINGS_MERGE_SORT = {
    "2 - Сортировка слиянием", ordo::sortings_merge_sort, &ordo::MENU_START_SORTING
};

const ordo::menu_item ordo::SORTINGS_HEAP_SORT = {
    "3 - Пирамидальная сортировка", ordo::sortings_heap_sort, &ordo::MENU_START_SORTING
};

const ordo::menu_item ordo::SORTINGS_RADIX_SORT = {
    "4 - Поразрядная сортировка", ordo::sortings_radix_sort, &ordo::MENU_START_SORTING
};

const ordo::menu_item ordo::SORTINGS_COUNTING_SORT = {
    "5 - Сортировка подсчетом", ordo::sortings_counting_sort, &ordo::MENU_START_SORTING
};

const ordo::menu_item ordo::SORTINGS_GO_BACK = {
    "0 - Выход в меню", ordo::go_back, &ordo::MENU_START_SORTING
};

namespace {
    const ordo::menu_item* const sortings_children[] = {

        &ordo::SORTINGS_GO_BACK,
        &ordo::SORTINGS_QUICKSORT,
        &ordo::SORTINGS_MERGE_SORT,
        &ordo::SORTINGS_HEAP_SORT,
        &ordo::SORTINGS_RADIX_SORT,
        &ordo::SORTINGS_COUNTING_SORT
    };
    const int sortings_size = sizeof(sortings_children) / sizeof(sortings_children[0]);
}

const ordo::menu_item ordo::MENU_START_SORTING = {
    "1 - Запуск сортировки", ordo::show_menu, &ordo::MAIN_MENU, sortings_children, sortings_size
};

const ordo::menu_item ordo::MENU_START_TESTING = {
    "2 - Тестирование", ordo::show_menu, &ordo::MAIN_MENU, testing_children, testing_size
};

const ordo::menu_item ordo::MENU_SETTINGS = {
    "3 - Настройки", ordo::menu_settings, &ordo::MAIN_MENU
};

const ordo::menu_item ordo::MENU_GO_BACK = {
    "0 - Выход в главное меню", ordo::go_back, &ordo::MAIN_MENU
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