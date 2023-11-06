#include "Display.hpp"

void Display::configure(MenuState progression){
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

    for(;;) {
        switch(progression){
            case MenuState::IDLE:
                hwlib::wait_ms(50);
                wait(menu_flag);
                hwlib::cout << "Display IDLE case\n";
                d4 << "\f" << "LASERTAG\n";
                d3 << "\f" << "Press 'A' to \nconfigure \nsettings.";
                oled.flush();
                break;
            case MenuState::MENU:
                hwlib::wait_ms(50);
                wait(menu_flag);
                hwlib::cout << "run MenuState case display task\n";
                d2 << "\f" << "settings";
                d3 << "\f" << "[1] player count\n[2] play time\n[3] lives\n[4] bullets\n[C] configured";
                oled.flush();
                break;
            case MenuState::PLAYER_COUNT:
                hwlib::wait_ms(50);
                hwlib::cout << "Player count\n";
                wait(menu_flag);
                d1 << "\f" << "player count?";
                oled.flush();
                break;
            case MenuState::PLAY_TIME:
                hwlib::wait_ms(50);
                wait(menu_flag);
                d1 << "\f" << "play time length \n[1] 05 minutes \n[2] 10 minutes \n[3] 15 minutes \n";
                oled.flush();
                break;
            case MenuState::LIVES:
                hwlib::wait_ms(50);
                wait(menu_flag);
                d1 << "\f" << "player lives?";
                oled.flush();
                break;
            case MenuState::BULLETS:
                hwlib::wait_ms(50);
                wait(menu_flag);
                d1 << "\f" << "bullet count?";
                oled.flush();
                break;
            default:
                hwlib::wait_ms(50);
                hwlib::cout<< "ERROR: Default settings Case\n";
        }
        hwlib::cout << "display wait\n";
        hwlib::wait_ms(100);
    }
}

void Display::gameInfo(int play_time, int lives, int bullets, int player){
    // wait for the PC console to start
    hwlib::wait_ms( 500 );   

    auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
    auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );

    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl, sda );

    // use the buffered version
    auto oled = hwlib::glcd_oled( i2c_bus, 0x3c );  

    // this won't work because it doesn't call flush()     
    // hwlib::graphics_random_circles( oled );
    auto f1 = hwlib::font_default_8x8();
    auto f2 = hwlib::font_default_16x16();

    auto w1 = hwlib::part( oled, hwlib::xy( 0, 0 ), hwlib::xy( 64, 16) );
    auto w2 = hwlib::part( oled, hwlib::xy( 0, 16 ), hwlib::xy( 64, 32) );
    auto w3 = hwlib::part( oled, hwlib::xy( 64, 0 ),hwlib::xy( 128, 16));
    auto w4 = hwlib::part( oled, hwlib::xy( 64, 16 ),hwlib::xy( 128, 32));
    auto w5 = hwlib::part( oled, hwlib::xy( 0, 32 ),hwlib::xy( 64, 48));
    auto w6 = hwlib::part( oled, hwlib::xy( 0, 48 ),hwlib::xy( 64, 63));
    auto w7 = hwlib::part( oled, hwlib::xy( 64, 32 ),hwlib::xy( 128, 48));
    auto w8 = hwlib::part( oled, hwlib::xy( 64, 48 ),hwlib::xy( 128, 63));
        
    auto d1 = hwlib::terminal_from( w1, f1 );
    auto d2 = hwlib::terminal_from( w2, f2 );
    auto d3 = hwlib::terminal_from( w3, f1 );
    auto d4 = hwlib::terminal_from( w4, f2 );
    auto d5 = hwlib::terminal_from( w5, f1 );
    auto d6 = hwlib::terminal_from( w6, f2 );
    auto d7 = hwlib::terminal_from( w7, f1 );
    auto d8 = hwlib::terminal_from( w8, f2 );

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

void Display::setMenuFlag(MenuState menu){
    hwlib::cout << "MenuState flag set\n";
    progression = menu;
    menu_flag.set();
}

void Display::setDisplayState(DisplayState new_state){
    display = new_state;
}

void Display::clearMenuFlag(){
    menu_flag.clear();
}