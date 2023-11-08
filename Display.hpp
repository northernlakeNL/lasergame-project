#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "EnumClass.hpp"

#pragma once

class Display: public rtos::task<>{
    private:
    DisplayMenuState progression = DisplayMenuState::IDLE;
    DisplayState display = DisplayState::SETTINGS;
    void main() override{
        for(;;) {
            switch(display){
                case DisplayState::SETTINGS:
                    hwlib::wait_ms(100);
                    configure();
                    break;
                case DisplayState::GAME:
                    hwlib::wait_ms(100);
                    break;
                case DisplayState::FINISH:
                    hwlib::wait_ms(100);
                    break;
            }
        }
    }
    rtos::flag menu_flag;
    rtos::flag game_flag;
    rtos::channel<DisplayMenuState, 10> display_pool;

    public:
    Display():
        task(3, "Display"),
        menu_flag(this, "menu_flag"),
        game_flag(this, "game_flag"),
        display_pool(this, "display_pool")
        {}
    void configure();
    void gameInfo( int play_time, int lives, int bullets, int player = 1);
    void setMenuFlag(DisplayMenuState menu);
    void clearMenuFlag();
    void updateDisplay(DisplayMenuState display);
};

#endif // DISPLAY_HPP