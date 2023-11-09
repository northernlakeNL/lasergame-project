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
    
    hwlib::target::pin_oc scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    hwlib::target::pin_oc sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    hwlib::i2c_bus_bit_banged_scl_sda i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    hwlib::glcd_oled oled = hwlib::glcd_oled( i2c_bus, 0x3c );  //128x64
    hwlib::font_default_8x8 f1 = hwlib::font_default_8x8();
    hwlib::font_default_16x16 f2 = hwlib::font_default_16x16();

    hwlib::window_part_t w1 = hwlib::part( oled, hwlib::xy( 0, 0 ), hwlib::xy( 128, 16) );
    hwlib::window_part_t w2 = hwlib::part( oled, hwlib::xy( 0, 16), hwlib::xy( 128, 64) );
    hwlib::window_part_t w3 = hwlib::part( oled, hwlib::xy( 0, 16), hwlib::xy( 64, 24) );
    hwlib::window_part_t w4 = hwlib::part( oled, hwlib::xy( 0, 24), hwlib::xy( 64, 40) );
    hwlib::window_part_t w5 = hwlib::part( oled, hwlib::xy( 64, 16), hwlib::xy( 128, 24) );
    hwlib::window_part_t w6 = hwlib::part( oled, hwlib::xy( 64, 24), hwlib::xy( 128, 40) );
    hwlib::window_part_t w7 = hwlib::part( oled, hwlib::xy( 0, 40), hwlib::xy( 64, 64) );
    hwlib::window_part_t w8 = hwlib::part( oled, hwlib::xy( 64, 40), hwlib::xy( 128, 64) );

	hwlib::terminal_from d1 = hwlib::terminal_from( w1, f2 ); // top text
	hwlib::terminal_from d2 = hwlib::terminal_from( w2, f1 ); // settings text
	hwlib::terminal_from d3 = hwlib::terminal_from( w3, f1 ); // time name
	hwlib::terminal_from d4 = hwlib::terminal_from( w4, f2 ); // time
	hwlib::terminal_from d5 = hwlib::terminal_from( w5, f1 ); // lives name
	hwlib::terminal_from d6 = hwlib::terminal_from( w6, f2 ); // lives
	hwlib::terminal_from d7 = hwlib::terminal_from( w7, f1 ); // time name
	hwlib::terminal_from d8 = hwlib::terminal_from( w8, f2 ); // time

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
    void updateDisplay(DisplayMenuState display);
};

#endif // DISPLAY_HPP