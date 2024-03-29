#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "hwlib.hpp"
#include "Display.hpp"
#include "KeypadListener.hpp"
#include "ButtonListener.hpp"
#include "EnumClass.hpp"

#pragma once

class Settings: public rtos::task<> {
private:
    MenuState gameSettings;
    DisplayState displayState;
    void main() override;

    Display& display;

    rtos::flag settings_flag;
    rtos::channel<MenuState, 10> menu_pool;

    char last_key;
public:
    Settings(Display& display):
        task(2, "settings"),
        display(display),
        settings_flag(this, "settings_flag"),
        menu_pool(this, "menu_pool"),
        last_key(' ')
        {}

    void setCase(MenuState state);
    void setSettingsFlag();
    void start();
};
 
#endif //SETTINGS_HPP