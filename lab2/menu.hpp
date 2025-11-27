#pragma once

namespace ordo{
    struct menu_item {
        const char* const title;
        const menu_item* (*func)(const menu_item* current);

        const menu_item* parent;
        const menu_item* *children;

        const int children_count;
    };
}