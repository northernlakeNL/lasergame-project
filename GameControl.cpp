#include "GameControl.hpp"

GameControl::GameControl(Beeper& beeper, ButtonListener& shootbutton, ButtonListener& reload_button, IR_emitter& emitter, int prio) :
task(prio, "GameControlTask"),
beeper(beeper),
shootbutton(shootbutton),
reload_button(reload_button),
emitter(emitter)
{}

void GameControl::main() {
    for(;;) {
        hwlib::wait_ms(1);
        if (shootbutton.readButton() && !pressed)
        {   pressed = true;
            hwlib::wait_ms(100);
            emitter.setButtonFlag();
            beeper.setShootSound();
        }
        else if ((!shootbutton.readButton() && pressed)) {
            pressed = false;
        }
        if (reload_button.readButton())
        {
            // beeper.setReloadSound();
        }
    }
}