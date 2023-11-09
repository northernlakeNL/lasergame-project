#ifndef BEEPER_HPP
#define BEEPER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"

#include "logger2.hpp"

class Beeper : public rtos::task<> {
private:
    hwlib::pin_out &lsp;
    int prio;
    rtos::flag shootSoundFlag;
    rtos::flag reloadSoundFlag;
    rtos::flag emptyClipFlag;
    rtos::flag hitFlag;
    void await(long long unsigned int t);
    void beep(int f, int d, int fd = 1000);
    enum State{ IDLE, SHOOT, RELOAD, EMPTY_CLIP, HIT };
    State currentState = IDLE;

    
public:
    Beeper(hwlib::pin_out &lsp, int prio);

    void setShootSound();

    void setReloadSound();

    void setEmptyClipSound();

    void setHitFlag();

    void peewSound();

    void reloadSound();

    void emptyClipSound();

    void hitSound();

    void main() override;

};

#endif
