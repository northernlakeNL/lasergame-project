#ifndef BEEPER_HPP
#define BEEPER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"



class Beeper : public rtos::task<> {
private:
    hwlib::pin_out &lsp;
    int prio;
    rtos::flag shootSoundFlag;
    rtos::flag reloadSoundFlag;
    void await(long long unsigned int t);
    void beep(int f, int d, int fd = 1000);
    enum State{ IDLE, SHOOT, RELOAD };
    State currentState = IDLE;

    
public:
    Beeper(hwlib::pin_out &lsp, int prio);

    void setShootSound();

    void setReloadSound();

    void peewSound();

    void reloadSound();

    void main() override;

};

#endif
