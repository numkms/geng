#ifndef MENU_ITEM_H
#define MENU_ITEM_H
#include <string>
struct MenuItem
{
    std::string title;
    std::function<void()> function;
};
#endif