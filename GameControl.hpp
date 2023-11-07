#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "beeper.hpp"
#include "ButtonListener.hpp"
#include "IR_Emitter.hpp"



class GameControl : public rtos::task<> {
private:
    Beeper& beeper;
    ButtonListener& shootbutton;
    ButtonListener& reload_button;
    IR_emitter& emitter;
    int prio;
    bool pressed = false;
public:
    GameControl(Beeper& beeper, ButtonListener & shootbutton, ButtonListener& reload_button, IR_emitter& emitter, int prio);
    void main() override;
};




#endif