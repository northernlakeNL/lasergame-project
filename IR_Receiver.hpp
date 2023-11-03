#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP
#include "hwlib.hpp"
#include "rtos.hpp"

#include <optional>

class IR_receiver {
private:
    hwlib::target::pin_in& pin;
    
public:
    IR_receiver(hwlib::target::pin_in& pin):
    pin(pin) 
    {}

    bool read(){
        return pin.read();
    }
};
#endif 