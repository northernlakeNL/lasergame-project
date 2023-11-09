#include "Display.hpp"


void Display::configure(){
    progression = DisplayMenuState::IDLE;
    for(;;) {
        switch(progression){
            case DisplayMenuState::IDLE:
                hwlib::wait_us(10);
                d1 << "\f" << "LASERTAG\n";
                d2 << "\f" << "Press 'A' to \nconfigure \nsettings. \nPress 'B' to \n receive.";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::RECEIVE:
                hwlib::wait_us(10);
                d1 << "\f" << "RECEIVE";
                d2 << "\f" << "Waiting to receive\ndata."
                oled.flush();
                progression = display_pool.read();
                break; 
            case DisplayMenuState::MENU:
                hwlib::wait_us(10);
                d1 << "\f" << "settings";
                d2 << "\f" << "[1] player count\n[2] play time\n[3] lives\n[4] bullets\n[C] configured";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::PLAYER_COUNT:
                hwlib::wait_us(10);
                d2 << "\f" << "How many players?\n";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::PLAY_TIME:
                hwlib::wait_us(10);
                d2 << "\f" << "play time length \n[1] 05 minutes \n[2] 10 minutes \n[3] 15 minutes \n";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::LIVES:
                hwlib::wait_us(10);
                d2 << "\f" << "player lives?";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::BULLETS:
                hwlib::wait_us(10);
                d2 << "\f" << "bullet count?";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::DONE:
                hwlib::wait_us(10);
                d2 << "\f" << "Press 'A' to\nstart playing \n\nPress 'D' \nto cancel";
                oled.flush();
                progression = display_pool.read();
                break;
            case DisplayMenuState::ERROR:
                hwlib::wait_us(10);
                d1 << "\f" << "ERROR";
                d2 << "\f" << "Entry Not \nsufficient \n\nPress 'A' to return to \nsettings";
                oled.flush();
                progression = display_pool.read();
                break;
            default:
                hwlib::wait_us(10);
                // hwlib::cout<< "ERROR: Default settings Case\n";
        }
        hwlib::wait_us(1);
    }
}

void Display::gameInfo(int play_time, int lives, int bullets, int player){
    int minutes = play_time / 60;
    int seconds = play_time % 60;

    // pLogger->logText("ik komhier");
    d1 << "\f" << "Player " << player;
    d3 << "\f" << "Bullets";
    d4 << "\f" << bullets;
    d5 << "\f" << "lives";	
    d6 << "\f" << lives; 
    d7 << "\f" << "Time";
    d8 << "\f" << minutes << ":" << seconds;
    oled.flush();
}

void Display::updateDisplay(DisplayMenuState new_state){
    display_pool.write( new_state );
}
