#ifndef IR_CONTROL_HPP
#define IR_CONTROL_HPP
#include <array>

template<typename S>
class IR_Control{

public:
    IR_Control():
    {}

    virtual void send(std::array<int , S>) = 0;
};

#endif