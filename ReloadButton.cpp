#include "ReloadButton.hpp"

ReloadButton::ReloadButton(hwlib::pin_in& reload_pin) :
task(4, "ReloadButtonTask"),
reload_pin(reload_pin)
{}

bool ReloadButton::readButton() {
    // hwlib::wait_ms(100);
    return reload_pin.read();   
}

void ReloadButton::main() {
    for(;;) {
        
    }
}