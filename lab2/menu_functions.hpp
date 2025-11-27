#pragma once

#include "menu.hpp"

namespace ordo {

    const menu_item* exit(const menu_item* current);

    const menu_item* go_back(const menu_item* current);
    const menu_item* function(const menu_item* current);

    const menu_item* show_for_layer1(const menu_item* current);
    const menu_item* show_for_layer2(const menu_item* current);
    const menu_item* show_for_layer3(const menu_item* current);
}
