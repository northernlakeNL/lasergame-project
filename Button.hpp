#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
// #include "Display.hpp"
#pragma once

class Button: public rtos::task<>{
    private:
        hwlib::target::pin_in d50 = hwlib::target::pin_in(hwlib::target::pins::d50); //reload
        hwlib::target::pin_in d51 = hwlib::target::pin_in(hwlib::target::pins::d51); //shoot
        void main() override{for (;;){}}
    public:
    Button():
    task(3, "buttons")
    {}
    bool reload();
    bool shoot();
};

#endif //BUTTON_HPP