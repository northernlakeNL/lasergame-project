#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "beeper.hpp"
#include "ButtonListener.hpp"
#include "IR_Emitter.hpp"
#include "messages.hpp"
#include "logger2.hpp"
#include<array>

extern Logger* pLogger;


class GameControl : public rtos::task<> {
private:
    Beeper& beeper;
    ButtonListener& shootbutton;
    ButtonListener& reload_button;
    IR_emitter& emitter;
    Messages& messageLogger;

    int prio;
    int bullets = 5;
    bool pressed = false;
    std::array<int, 6> gameInfo;
public:
    GameControl(Beeper& beeper, ButtonListener & shootbutton, ButtonListener& reload_button, IR_emitter& emitter, Messages& messageLogger, int prio);
    void bitSplitter(uint32_t binaryValue);
    void main() override;
};




#endif