#include "GameClock.hpp"

int GameClock::gameTimer(){
    int countdown = 20;
    int timer = hwlib::now_us();
    if (timer == 1000000){
        timer = hwlib::now_us();
        countdown--;
        return countdown;
    }
}