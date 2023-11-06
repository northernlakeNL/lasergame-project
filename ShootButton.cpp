#include "ShootButton.hpp"

ShootButton::ShootButton(hwlib::pin_in& shoot_pin) :
task(2, "ShootButtonTask"),
shoot_pin(shoot_pin)
{}

bool ShootButton::readButton() {
    return shoot_pin.read();   
}

void ShootButton::main() {
    for(;;) {
        hwlib::wait_ms(1000);
        // hwlib::cout << "shootbutton";
    }
}