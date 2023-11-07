#ifndef IR_CONTROL_HPP
#define IR_CONTROL_HPP
#include <array>

// template<typename N>
class IR_Control{

public:
    IR_Control();

    virtual void send(std::array<int , 8>) = 0;
};

#endif