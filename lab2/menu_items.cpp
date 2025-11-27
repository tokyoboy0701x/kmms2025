#include "menu_items.hpp"
#include "menu_functions.hpp"

const ordo::menu_item ordo::ANOTHER_TECHNOLOGIES_DATA_BASES = {
    "1 - Базы данных", function, &STUDY_ANOTHER_TECHNOLOGIES
};

const ordo::menu_item ordo::ANOTHER_TECHNOLOGIES_MULTIFLOW = {
    "2 - Многопоточное прогаммирование", function, &STUDY_ANOTHER_TECHNOLOGIES
};

const ordo::menu_item ordo::ANOTHER_TECHNOLOGIES_NET = {
    "3 - Сетевые технологии", function, &STUDY_ANOTHER_TECHNOLOGIES
};

const ordo::menu_item ordo::ANOTHER_TECHNOLOGIES_GO_BACK= {
    "0 - Выйти в предыдущее меню", go_back, &STUDY_ANOTHER_TECHNOLOGIES
};

namespace {
    const ordo::menu_item* technologies_children[] = {
        &ordo::ANOTHER_TECHNOLOGIES_GO_BACK,
        &ordo::ANOTHER_TECHNOLOGIES_DATA_BASES,
        &ordo::ANOTHER_TECHNOLOGIES_MULTIFLOW,
        &ordo::ANOTHER_TECHNOLOGIES_NET
        
    };
    int technologies_size = sizeof(technologies_children) / sizeof(technologies_children[0]);
}

const ordo::menu_item ordo::STUDY_PROGRAMMING_LANGUAGES = {
    "1 - Изучать языки программирования", function, &STUDY_PROGRAMMING
};

const ordo::menu_item ordo::STUDY_ALGORITHMS = {
    "2 - Алгоритмы и структуры", function, &STUDY_PROGRAMMING
};

const ordo::menu_item ordo::STUDY_ANOTHER_TECHNOLOGIES = {
    "3 - Другие технологии", show_for_layer3, &STUDY_PROGRAMMING, technologies_children, technologies_size
};

const ordo::menu_item ordo::STUDY_GO_BACK = {
    "0 - Выйти в главное меню", go_back, &STUDY_PROGRAMMING
};

namespace {
    const ordo::menu_item* programming_children[] = {
        &ordo::STUDY_GO_BACK,
        &ordo::STUDY_PROGRAMMING_LANGUAGES,
        &ordo::STUDY_ALGORITHMS,
        &ordo::STUDY_ANOTHER_TECHNOLOGIES
    };

    int programming_size = sizeof(programming_children) / sizeof(programming_children[0]);
};

const ordo::menu_item ordo::EXIT = {
    "0 - Пойти поиграть в футбол", exit, &MAIN
};

const ordo::menu_item ordo::STUDY_PROGRAMMING = {
    "1 - Изучать программирование", show_for_layer2, &MAIN, programming_children, programming_size
};

namespace {
    const ordo::menu_item* main_children[] = {
        &ordo::EXIT,
        &ordo::STUDY_PROGRAMMING
    };

    int main_size = sizeof(main_children) / sizeof(main_children[0]);
}

const ordo::menu_item ordo::MAIN = {
    nullptr, show_for_layer1, nullptr, main_children, main_size 
};
