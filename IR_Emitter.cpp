#include "IR_emitter.hpp"

IR_emitter::IR_emitter(hwlib::target::d2_36kHz& pin, hwlib::target::pin_in & button)
    : task(1, "IR_transmitter"), pin(pin), button(button) {}

void IR_emitter::send(std::array<int, 8> arr) {
    pin.write(1);
    hwlib::wait_ms(9);
    pin.flush();
    pin.write(0);
    hwlib::wait_us(4500);
    for (int i : arr) {
        if (i) {
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
            send(arr);
        } else if ((!button.read() && pressed)) {
            pressed = false;
        }
        hwlib::wait_ms(10);
    }
}
