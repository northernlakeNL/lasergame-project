#include "Display.hpp"

void Display::configure(){
    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );  

    auto w1 = hwlib::part( oled, hwlib::xy( 0, 0 ),hwlib::xy( 128, 64));
    auto w2 = hwlib::part( oled, hwlib::xy( 0, 0 ),hwlib::xy( 128, 16));
    auto w3 = hwlib::part( oled, hwlib::xy( 0, 16 ),hwlib::xy( 128, 64));
    auto f1 = hwlib::font_default_8x8();
    auto f2 = hwlib::font_default_16x16();
    auto d1 = hwlib::terminal_from( w1, f1 );
    auto d2 = hwlib::terminal_from( w2, f2 );
    auto d3 = hwlib::terminal_from( w3, f1 );
    auto d4 = hwlib::terminal_from( w1, f2 );

    oled.flush();
    progression = DisplayMenuState::IDLE;
    for(;;) {
        switch(progression){
            case DisplayMenuState::IDLE:
                hwlib::wait_ms(50);
                d4 << "\f" << "LASERTAG\n";
                d3 << "\f" << "Press 'A' to \nconfigure \nsettings.";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::MENU:
                hwlib::wait_ms(50);
                d2 << "\f" << "settings";
                d3 << "\f" << "[1] player count\n[2] play time\n[3] lives\n[4] bullets\n[C] configured";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::PLAYER_COUNT:
                hwlib::wait_ms(50);
                d2 << "\f" << "settings";
                d3 << "\f" << "How many players?\n";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::PLAY_TIME:
                hwlib::wait_ms(50);
                d2 << "\f" << "settings";
                d3 << "\f" << "play time length \n[1] 05 minutes \n[2] 10 minutes \n[3] 15 minutes \n";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::LIVES:
                hwlib::wait_ms(50);
                d2 << "\f" << "settings";
                d3 << "\f" << "player lives?";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::BULLETS:
                hwlib::wait_ms(50);
                d2 << "\f" << "settings";
                d3 << "\f" << "bullet count?";
                oled.flush();
                progression = display_pool.read();
                break;
            default:
                hwlib::wait_ms(50);
                hwlib::cout<< "ERROR: Default settings Case\n";
        }
        hwlib::wait_ms(100);
    }
}


void Display::gameInfo(int play_time, int lives, int bullets, int player){
    // wait for the PC console to start
    d1  << "\f" << "lives";
    d2  << "\f" << lives; 
    d3  << "\f" << "Time";
    d4  << "\f" << play_time;
    d5  << "\f" << "Player" ;
    d6  << "\f" << player;
    d7  << "\f" << "Bullets";
    d8  << "\f" << bullets;
    oled.flush();
}

void Display::updateDisplay(DisplayMenuState new_state){
    display_pool.write( new_state );
}
