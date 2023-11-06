#ifndef IR_EMITTER_HPP
#define IR_EMITTER_HPP

#include "hwlib.hpp"
#include <array>
#include "rtos.hpp"

class IR_emitter : public rtos::task<> {
private:
    hwlib::target::d2_36kHz& pin;
    hwlib::target::pin_in & button;
    bool pressed = false;
    std::array<int, 8> arr = {1, 1, 0, 0, 0, 0, 0, 0};

public:
    IR_emitter(hwlib::target::d2_36kHz& pin, hwlib::target::pin_in & button);
    void send(std::array<int, 8> arr);
    void main() override;
};

#endif
