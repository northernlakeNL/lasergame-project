#ifndef RELOAD_BUTTON_HPP
#define RELOAD_BUTTON_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "ButtonListener.hpp"




class ReloadButton : public rtos::task<>, public ButtonListener {
private:
    hwlib::pin_in &reload_pin;
    bool pressed;
    int prio;

public:
    ReloadButton(hwlib::pin_in& reload_pin, int prio);
    bool readButton() override;
    void main() override;
    
};

#endif