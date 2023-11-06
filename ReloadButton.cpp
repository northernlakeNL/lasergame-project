#include "ReloadButton.hpp"

ReloadButton::ReloadButton(hwlib::pin_in& reload_pin) :
task(2, "ReloadButtonTask"),
reload_pin(reload_pin)
{}

bool ReloadButton::readButton() {
    if (reload_pin.read()) {
        hwlib::wait_ms(100);
        return true;
    }

    return false;    
}

void ReloadButton::main() {
    hwlib::cout << "rtosiskut";
    for(;;) {
        hwlib::wait_ms(1000);
        hwlib::cout << "reloadbutton";
    }
}