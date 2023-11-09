#include "GameControl.hpp"

GameControl::GameControl(Beeper& beeper, ButtonListener& shootbutton, ButtonListener& reload_button, IR_emitter& emitter, Messages& messageLogger, int prio) :
task(prio, "GameControlTask"),
beeper(beeper),
shootbutton(shootbutton),
reload_button(reload_button),
emitter(emitter),
messageLogger(messageLogger)
{}




void GameControl::bitSplitter(uint32_t binaryValue){

    for (unsigned int i = 0; i < 6; i++) {
        unsigned int part = (binaryValue) & 0xF;
        binaryValue >>= 4;
        gameInfo[i]= part;
        // hwlib::cout << ": " << part << hwlib::endl;
        pLogger->logInt(part);
        
    }
    
    // return(gameInfo);
}

void GameControl::main() {
    for(;;) {
       
        hwlib::wait_ms(1);
        if (shootbutton.readButton() && !pressed){
            pressed = true;
            hwlib::wait_ms(10);
            if (bullets == 0){
                beeper.setEmptyClipSound();
            }
            else{
                bullets -= 1;
                emitter.setButtonFlag();
                beeper.setShootSound();
            }
            
        }
        else if (reload_button.readButton() && !pressed){
            pressed = true;
            beeper.setReloadSound();
            bullets = 5;
        }
        else if ((!shootbutton.readButton() && pressed) && (!reload_button.readButton() && pressed)) {
            pressed = false;
        }
        
        if(messageLogger.isHit()){
            beeper.setHitFlag();
            messageLogger.resetHit();
        }
        
    }
}