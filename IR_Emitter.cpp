#include "IR_emitter.hpp"

IR_emitter::IR_emitter(hwlib::target::d2_36kHz& pin, hwlib::target::pin_in & button)
    : task(1, "IR_transmitter"), pin(pin), button(button) {}


void IR_emitter::send(uint32_t bytes) {
    pin.write(1);
    hwlib::wait_ms(9);
    pin.flush();
    pin.write(0);
    hwlib::wait_us(4500);
    for (int i = 0 ; i < 24; i++ ) {
        bit = bytes & 1;
        if(bit) {
            pin.write(1);
            hwlib::wait_us(560);
            pin.write(0);
            hwlib::wait_us(1690);
            pin.write(0);
            pin.flush();
        } else {
            pin.write(1);
            hwlib::wait_us(560);
            pin.write(0);
            hwlib::wait_us(560);
            pin.write(0);
            pin.flush();
        }
        bytes >>= 1;
    }
    pin.write(1);
    hwlib::wait_us(560);
    pin.write(0);
    hwlib::wait_ms(6);
    pin.write(1);
    hwlib::wait_us(560);
    pin.write(0);
}

void IR_emitter::main() {
    for (;;) {
        if (button.read()) {
            pressed = true;
            send(data);
        } else if ((!button.read() && pressed)) {
            pressed = false;
        }
        hwlib::wait_ms(10);
    }
}
