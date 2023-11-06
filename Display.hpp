#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "EnumClass.hpp"

#pragma once

class Display: public rtos::task<>{
    private:
    MenuState progression = MenuState::IDLE;
    DisplayState display = DisplayState::IDLE;
    void main() override{
        for(;;) {
            switch(display){
                case DisplayState::IDLE:
                    hwlib::wait_ms(100);
                    configure(progression);
                    break;
                case DisplayState::SETTINGS:
                    hwlib::wait_ms(100);
                    configure(progression);
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

    public:
    Display():
        task(3, "Display"),
        menu_flag(this, "menu_flag"),
        game_flag(this, "game_flag")
        {}
    void configure(MenuState progression);
    void gameInfo( int play_time, int lives, int bullets, int player = 1);
    void setMenuFlag(MenuState menu);
    void clearMenuFlag();
    void setDisplayState(DisplayState display);
};

#endif // DISPLAY_HPP