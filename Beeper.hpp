#ifndef BEEPER_HPP
#define BEEPER_HPP

#include "hwlib.hpp"
#include "rtos.hpp"



class Beeper : public rtos::task<> {
private:
    hwlib::pin_out &lsp;
    rtos::flag shootSoundFlag;
    rtos::flag reloadSoundFlag;
    void await(long long unsigned int t);
    void beep(int f, int d, int fd = 1000);
    
    

public:
    Beeper(hwlib::pin_out &lsp);

    void setShootSound();

    void setReloadSound();

    void peewSound();

    void reloadSound();

    void main() override;

};

#endif
