#include "Beeper.hpp"
// #include "plogger2.hpp"

// extern 
Beeper::Beeper(hwlib::pin_out &lsp, int prio):
    task(prio, "Beeper"),
    lsp(lsp), 
    shootSoundFlag(this, "shootSoundFlag"),
    reloadSoundFlag(this, "reloadSoundFlag")
{}

// void Beeper::await(long long unsigned int t) {
//     hwlib::wait_us(t - hwlib::now_us());
// }

void Beeper::beep(int f, int d, int fd) {
    auto t = hwlib::now_us();
    auto end = t + d;
    while (end > hwlib::now_us()) {
        auto p = 500'000 / f;
        f = f * fd / 1000;
        lsp.write(1);
        lsp.flush();
        hwlib::wait_us(p);
        lsp.write(0);
        lsp.flush();
        hwlib::wait_us(p);
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
    beep(500, 200000);
    hwlib::wait_ms(100);
    beep(600, 200000);
    hwlib::wait_ms(150);
    beep(400, 250000); 
    hwlib::wait_ms(200); 
    beep(800, 100000);
    hwlib::wait_ms(100);
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
