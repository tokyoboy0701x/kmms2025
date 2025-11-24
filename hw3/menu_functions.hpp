#pragma once

#include "menu.hpp"

namespace ordo {
    const menu_item* show_menu(const menu_item* current);

    const menu_item* exit(const menu_item* current);

    const menu_item* menu_start_sorting(const menu_item* current);
    const menu_item* menu_start_testing(const menu_item* current);
    const menu_item* menu_settings(const menu_item* current);
    const menu_item* menu_go_back(const menu_item* current);
}