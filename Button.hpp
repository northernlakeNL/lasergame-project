#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "ButtonListener.hpp"


class Button : public rtos::task<>, public ButtonListener {
private:
    hwlib::pin_in &button_pin;
    const char* task_name;
    int prio;

public:
    Button(hwlib::pin_in& button_pin, const char* task_name, int prio);
    bool readButton() override;
    void main() override;
    
};

#endif