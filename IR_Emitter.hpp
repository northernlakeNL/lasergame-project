#ifndef IR_EMITTER_HPP
#define IR_EMITTER_HPP

#include "hwlib.hpp"
#include <array>
#include "rtos.hpp"

class IR_emitter : public rtos::task<> {
private:
    rtos::flag buttonFlag;
    hwlib::target::d2_36kHz& pin;
    hwlib::target::pin_in & button;
    int prio;
    bool pressed = false;
    bool bit = 0;
    // unsigned int data = 0b110110101101010110111101;

public:
    IR_emitter(hwlib::target::d2_36kHz& pin, hwlib::target::pin_in & button, int prio);
    void send(uint32_t bytes);
    void main() override;
    void setButtonFlag();
};

#endif
