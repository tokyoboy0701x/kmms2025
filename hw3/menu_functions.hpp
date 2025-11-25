#pragma once

#include "menu.hpp"

namespace ordo {
    const menu_item* show_menu(const menu_item* current);

    const menu_item* exit(const menu_item* current);

    const menu_item* go_back(const menu_item* current);

    const menu_item* menu_settings(const menu_item* current);

    const menu_item* sortings_quicksort(const menu_item* current);
    const menu_item* sortings_merge_sort(const menu_item* current);
    const menu_item* sortings_heap_sort(const menu_item* current);
    const menu_item* sortings_radix_sort(const menu_item* current);
    const menu_item* sortings_counting_sort(const menu_item* current);

    const menu_item* testing_quicksort(const menu_item* current);
    const menu_item* testing_merge_sort(const menu_item* current);
    const menu_item* testing_heap_sort(const menu_item* current);
    const menu_item* testing_radix_sort(const menu_item* current);
    const menu_item* testing_counting_sort(const menu_item* current);
}