#include "Display.hpp"

std::array<int, 4> Display::configure(int progression){
    Keypad keypad;
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

    std::array<int, 4> settings = {'0', '0', '0', '0'}; //{player count, play time, lives, bullets(reload is infinite)}

    while(true) {
        switch(progression){
            case 0:
                hwlib::wait_ms( 500 );
                d1  << "\f" << "Press 'A' to \nconfigure \nsettings.";
                oled.flush();
                if (keypad.keypadRead() == 'A') {
                    progression = 1;
                }
                break;
            case 1:
                hwlib::wait_ms( 500 );
                d2 << "\f" << "settings";
                d3 << "\f" << "[1] player count\n[2] play time\n[3] lives\n[4] bullets\n[C] configured";
                oled.flush();
                if (keypad.keypadRead() == '1'){
                    progression = 2;
                    break;
                }
                if (keypad.keypadRead() == '2'){
                    progression = 3;
                    break;
                }
                if (keypad.keypadRead() == '3'){
                    progression = 4;
                    break;
                }
                if (keypad.keypadRead() == '4'){
                    progression = 5;
                    break;
                }
                if (keypad.keypadRead() == 'C'){
                    progression = 6;
                    break;
                }
                if (keypad.keypadRead() == 'D'){
                    hwlib::wait_ms( 500 );
                    d1 << "\f" << "quit settings?";
                    oled.flush();
                    if (keypad.keypadRead() == '1'){
                        progression = 0;
                    }
                    else if (keypad.keypadRead() == '2'){
                        continue;
                    }
                }
            case 2:
                hwlib::wait_ms( 500 );
                d1 << "\f" << "player count?";
                oled.flush();
                settings[0] = keypad.keypadRead() - '0';
                d3 << "\f" << settings[0];
                oled.flush();
                progression = 1;
                break;
            case 3:
                hwlib::wait_ms( 500 );
                d1 << "\f" << "play time length \n[1] 05 minutes \n[2] 10 minutes \n[3] 15 minutes \n";
                oled.flush();
                if (keypad.keypadRead() == '1'){
                    hwlib::wait_ms( 500 );
                    d1 << "\f" << "selected\n05 minutes.\n[1] continue\n[2] quit";
                    oled.flush();
                    if (keypad.keypadRead() == '1'){
                        hwlib::wait_ms( 500 );
                        d1 << "\f" << "05 minutes\nconfigured.";
                        settings[1] = 5;
                        progression = 1;
                        break;
                    }
                    if (keypad.keypadRead() == '2'){
                        hwlib::wait_ms( 500 );
                        progression = 3;
                        break;
                    }
                }
                if (keypad.keypadRead() == '2'){
                    hwlib::wait_ms( 500 );
                    d1 << "\f" << "selected\n10 minutes.\n[1] continue\n[2] quit";
                    oled.flush();
                    if (keypad.keypadRead() == '1'){
                        hwlib::wait_ms( 500 );
                        d1 << "\f" << "10 minutes\nconfigured.";
                        settings[1] = 10;
                        progression = 1;
                        break;
                    }
                    if (keypad.keypadRead() == '2'){
                        hwlib::wait_ms( 500 );
                        progression = 3;
                        break;
                    }
                }
                if (keypad.keypadRead() == '3'){
                    hwlib::wait_ms( 500 );
                    d1 << "\f" << "selected\n15 minutes.\n[1] continue\n[2] quit";
                    oled.flush();
                    if (keypad.keypadRead() == '1'){
                        hwlib::wait_ms( 500 );
                        d1 << "\f" << "15 minutes\nconfigured.";
                        settings[1] = 15;
                        progression = 1;
                        break;
                    }
                    if (keypad.keypadRead() == '2'){
                        hwlib::wait_ms( 500 );
                        progression = 3;
                        break;
                    }
                }
                if (keypad.keypadRead() == 'D'){
                    hwlib::wait_ms( 500 );
                    d1 << "\f" << "quit setting time?";
                    oled.flush();
                    if (keypad.keypadRead() == '1'){
                        progression = 0;
                    }
                    else{
                        continue;
                    }
                }
            case 4:
                hwlib::wait_ms( 500 );
                d1 << "\f" << "player lives?";
                oled.flush();
                settings[2] = keypad.keypadRead() - '0';
                d3 << "\f" << settings[2];
                oled.flush();
                progression = 1;
                break;
            case 5:
                hwlib::wait_ms( 500 );
                d1 << "\f" << "bullet count?";
                oled.flush();
                settings[3] = keypad.keypadRead() - '0';
                d3 << "\f" << settings[3];
                oled.flush();
                progression = 1;
                break;
            case 6:
                hwlib::wait_ms( 500 );
                d2  << "\f" << "Set values:";
                d3  << "\f" << "players: " << settings[0] << "\ntime: " << settings[1] << "\nlives: " << settings[2] << "\nbullets: " << settings[3] << "\n[A] continue";
                oled.flush();
                if (keypad.keypadRead() == 'A'){
                    d2 << "\f" << "Done?";
                    d3 << "\f" << "[1] Yes\n" << "[2] No";
                    oled.flush();
                    if (keypad.keypadRead() == '1'){
                        return settings;
                    }
                    if (keypad.keypadRead() == '2'){
                        progression = 1;
                        break;
                    }
                }
        }
    }
}

// void Display::countdown(){
//     int configure_time = 5; //minuten
//     int countdown = 20; // seconden
// }

void Display::gameInfo(int play_time, int lives, int bullets, int player){
    Display display;
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
