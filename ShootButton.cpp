#include "ShootButton.hpp"

ShootButton::ShootButton(hwlib::pin_in& shoot_pin, int prio) :
task(prio, "ShootButtonTask"),
shoot_pin(shoot_pin)
{}

bool ShootButton::readButton() {
    // hwlib::wait_ms(100);
    return shoot_pin.read();   
}

void ShootButton::main() {
    for(;;) {
        hwlib::wait_ms(50);
    }
}