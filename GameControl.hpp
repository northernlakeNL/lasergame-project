#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "beeper.hpp"
#include "ButtonListener.hpp"



class GameControl : public rtos::task<> {
private:
    Beeper& beeper;
    ButtonListener& shootbutton;
    ButtonListener& reload_button;
    rtos::flag shootFlag;
    rtos::flag reloadFlag;
    int prio;
public:
    GameControl(Beeper& beeper , ButtonListener & shootbutton, ButtonListener& reload_button, int prio);
    void setShootFlag();
    void setReloadFlag();
    void main() override;
};




#endif