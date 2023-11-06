#include "Beeper.hpp"

Beeper::Beeper(hwlib::pin_out &lsp, int prio):
    task(prio, "Beeper"),
    lsp(lsp), 
    shootSoundFlag(this, "shootSoundFlag"),
    reloadSoundFlag(this, "reloadSoundFlag")
{}

void Beeper::await(long long unsigned int t) {
    // hwlib::wait_us(t - hwlib::now_us());
    while( t > hwlib::now_us() ){}
}

void Beeper::beep(int f, int d, int fd) {
    auto t = hwlib::now_us();
    auto end = t + d;
    while (end > hwlib::now_us()) {
        auto p = 500'000 / f;
        f = f * fd / 1000;
        lsp.write(1);
        lsp.flush();
        await(t += p);
        lsp.write(0);
        lsp.flush();
        await(t += p);
    }
}

void Beeper::setShootSound() {
    shootSoundFlag.set();
    currentState = SHOOT;
}

void Beeper::setReloadSound() {
    reloadSoundFlag.set();
    currentState = RELOAD;
}

void Beeper::peewSound() {
    beep(20'000, 200'000, 990);      
}

void Beeper::reloadSound() {
    for (int i=1000; i<2000; i=i*1.02) { 
      beep(i,10'000); 
    } 
    for (int i=2000; i>1000; i=i*.98) {
      beep(i,10'000);
    }
}


void Beeper::main() {
    for(;;){
        switch(currentState){
        case IDLE:
            hwlib::wait_ms(50);
            break;
        case SHOOT: 
            hwlib::wait_ms(50);
            wait(shootSoundFlag);
            peewSound();
            currentState = IDLE;
            break;
        case RELOAD:
            hwlib::wait_ms(50);
            wait(reloadSoundFlag);
            reloadSound();
            currentState = IDLE;
            break;
        default:
            hwlib::cout << "no worky beeper main\n";
        }
    }
}