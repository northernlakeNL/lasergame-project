#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "hwlib.hpp"
#include "Keypad.hpp"
#include "Display.hpp"
#include "rtos.hpp"
#include <string>

#pragma once

class Display: public rtos::task<>{
    private:
    void main() override{for (;;){}}
    public:
    Display():
        task(2, "Display")
        {}
    std::array<int, 4> configure(int progression);
    // void countdown();
    void gameInfo( int play_time, int lives, int bullets, int player = 1);
};


#endif // DISPLAY_HPP`


