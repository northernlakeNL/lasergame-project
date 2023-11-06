#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "ButtonListener.hpp"
#include "EnumClass.hpp"
// #include "Display.hpp"
#pragma once

// class Button: public rtos::task<>{
// private:
//     rtos::flag pewPress;
//     rtos::flag reloadPress;
//     ButtonListener& listener;

//     void main() override {
//         auto shootButton = hwlib::target::pin_in(target::pins::d5);
//         auto reloadButton = hwlib::target::pin_in(target::pins::d5);
//         for(;;){
//             listener.ButtonPressed();
//         }
//     }
// public:
//     Button(ButtonListener& listener):
//         pewPress(this, "PewPress"),
//         ReloadPress(this, "ReloadPress"),
//         listener(listener)
//         {}

//     void buttonPressed();
// };




class Button: public rtos::task<>{
    private:
        hwlib::target::pin_in d50 = hwlib::target::pin_in(hwlib::target::pins::d50); //reload
        hwlib::target::pin_in d51 = hwlib::target::pin_in(hwlib::target::pins::d51); //shoot
        void main() override{for (;;){}}
    public:
    Button():
    task(4, "buttons")
    {}
    bool reload();
    bool shoot();
};

#endif //BUTTON_HPP