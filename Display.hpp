#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "EnumClass.hpp"
#include "i2c_hardware_due.hpp"
#include "logger2.hpp"

#pragma once
extern Logger* pLogger;

class Display: public rtos::task<>{
    private:
    DisplayMenuState progression = DisplayMenuState::IDLE;
    DisplayState display = DisplayState::SETTINGS;
    int prio;
    due::i2c_hardware i2c_bus;
    hwlib::glcd_oled oled;  //128x64

    hwlib::font_default_8x8 f1;
    hwlib::font_default_16x16 f2;

    hwlib::window_part_t w1;
    hwlib::window_part_t w2;
    hwlib::window_part_t w3;
    hwlib::window_part_t w4;
    hwlib::window_part_t w5;
    hwlib::window_part_t w6;
    hwlib::window_part_t w7;
    hwlib::window_part_t w8;

    hwlib::terminal_from d1; // top text
    hwlib::terminal_from d2; // settings text
    hwlib::terminal_from d3; // time name
    hwlib::terminal_from d4; // time
    hwlib::terminal_from d5; // lives name
    hwlib::terminal_from d6; // lives
    hwlib::terminal_from d7; // time name
    hwlib::terminal_from d8; // time
    
    void main() override{
        hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl1 );
        hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda1 );
        for(;;) {
            switch(display){
                case DisplayState::SETTINGS:
                    hwlib::wait_ms(100);
                    configure();
                    break;
                case DisplayState::PREGAME:
                    hwlib::wait_ms(100);
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
    Display(int prio):
        task(prio, "Display"),
        i2c_bus(due::i2c_hardware()),
        oled(hwlib::glcd_oled( i2c_bus, 0x3c )),
        f1(hwlib::font_default_8x8()),
        f2(hwlib::font_default_16x16()),

        w1(hwlib::part( oled, hwlib::xy( 0, 0 ), hwlib::xy( 128, 16) )),
        w2(hwlib::part( oled, hwlib::xy( 0, 16), hwlib::xy( 128, 64) )),
        w3(hwlib::part( oled, hwlib::xy( 0, 16), hwlib::xy( 64, 24) )),
        w4(hwlib::part( oled, hwlib::xy( 0, 24), hwlib::xy( 64, 40) )),
        w5(hwlib::part( oled, hwlib::xy( 64, 16), hwlib::xy( 128, 24) )),
        w6(hwlib::part( oled, hwlib::xy( 64, 24), hwlib::xy( 128, 40) )),
        w7(hwlib::part( oled, hwlib::xy( 0, 40), hwlib::xy( 64, 32) )),
        w8(hwlib::part( oled, hwlib::xy( 32, 40), hwlib::xy( 128, 64) )),

        d1(hwlib::terminal_from( w1, f2 )), // top text
        d2(hwlib::terminal_from( w2, f1 )), // settings text
        d3(hwlib::terminal_from( w3, f1 )), // time name
        d4(hwlib::terminal_from( w4, f2 )), // time
        d5(hwlib::terminal_from( w5, f1 )), // lives name
        d6(hwlib::terminal_from( w6, f2 )), // lives
        d7(hwlib::terminal_from( w7, f1 )), // time name
        d8(hwlib::terminal_from( w8, f2 )), // time
        menu_flag(this, "menu_flag"),
        game_flag(this, "game_flag"),
        display_pool(this, "display_pool")
        {}
    void configure();
    void ReceivedSettings(int play_time, int lives, int bullets);

    void gameInfo( int play_time, int lives, int bullets, int player = 1);
    void updateDisplay(DisplayMenuState display);
    void HitInfo(int play_time, int lives, int bullets, int enemy);
    void WinnerScreen(int player, int score);
    void gameOverScreen(int play_time);
};

#endif // DISPLAY_HPP