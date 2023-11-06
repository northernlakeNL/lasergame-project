#include "IR_receiver.hpp"

IR_receiver::IR_receiver(hwlib::target::pin_in& pin) : pin(pin) {}

bool IR_receiver::read() {
    return pin.read();
}
