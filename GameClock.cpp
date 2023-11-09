#include "GameClock.hpp"

int GameClock::preGameTimer(){
    int timer = hwlib::now_us();
    if (timer == 1000000){
        timer = hwlib::now_us();
        countdown--;
        return countdown;
    }
}

int GameClock::GameTimer(int gametimer){
    int timer = hwlib::now_us();
    if (timer == 60000000){
        timer = hwlib::now_us();
        gametimer--;
        return gametimer;
    }
}