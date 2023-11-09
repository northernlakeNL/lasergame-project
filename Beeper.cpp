#include "Beeper.hpp"

Beeper::Beeper(hwlib::pin_out &lsp, int prio):
    task(prio, "Beeper"),
    lsp(lsp), 
    shootSoundFlag(this, "shootSoundFlag"),
    reloadSoundFlag(this, "reloadSoundFlag"),
    emptyClipFlag(this, "emptyClipFlag"),
    hitFlag(this, "hitFlag")
{}



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

void Beeper::setEmptyClipSound() {
    emptyClipFlag.set();
    currentState = EMPTY_CLIP;
}

void Beeper::setHitFlag(){
    hitFlag.set();
    currentState = HIT;
}

void Beeper::peewSound() {
    beep(20'000, 50'000, 990);      
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

void Beeper::emptyClipSound() {
    beep(20'000, 20'000, 990);
}

void Beeper::hitSound() {
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
            hwlib::wait_ms(10);
            break;
        case SHOOT: 
            wait(shootSoundFlag);
            peewSound();
            currentState = IDLE;
            break;
        case RELOAD:
            wait(reloadSoundFlag);
            reloadSound();
            currentState = IDLE;
            break;
        case EMPTY_CLIP:
            wait(emptyClipFlag);
            emptyClipSound();
            currentState = IDLE;
            break;
        case HIT:
            wait(hitFlag);
            hitSound();
            currentState = IDLE;
            break;        
        default:
            hwlib::cout << "no worky beeper main\n";
        }
    }
}
