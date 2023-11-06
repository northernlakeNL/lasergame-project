#ifndef SHOOT_BUTTON_HPP
#define SHOOT_BUTTON_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "ButtonListener.hpp"




class ShootButton : public rtos::task<> , public ButtonListener {
private:
    hwlib::pin_in &shoot_pin;
    bool pressed;

public:
    ShootButton(hwlib::pin_in& shoot_pin);
    bool readButton() override;
    void main() override;

};

#endif