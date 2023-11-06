#include "Button.hpp"


Button::Button(hwlib::pin_in& button_pin, auto task_name, int prio) :
task(prio, task_name),
button_pin(button_pin)
{}

bool Button::readButton() {
    return button_pin.read();   
}

void Button::main() {
    for(;;) {       
    hwlib::wait_ms(50);
    }
}