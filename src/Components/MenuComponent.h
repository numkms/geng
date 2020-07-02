#ifndef MENU_COMPONENT_H;
#define MENU_COMPONENT_H;

#include <map>
#include <string>
#include "../Component.h"
#include "TransformComponent.h"
#include "../MenuItem.h"
#include <iostream>

class MenuComponent: public Component {
    private:
        /* data */
        //Here we have map of menu items with their implementation
        std::vector<std::string> itemEntityNames;
    public:
        MenuComponent(std::vector<std::string> itemEntityNames): itemEntityNames(itemEntityNames) {}

        void Render() override {
            
        }
};  
#endif;