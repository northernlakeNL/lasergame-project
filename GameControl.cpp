#include "GameControl.hpp"

GameControl::GameControl(Beeper& beeper, ButtonListener& shootbutton, ButtonListener& reload_button, int prio) :
task(prio, "GameControlTask"),
beeper(beeper),
shootbutton(shootbutton),
reload_button(reload_button),
shootFlag(this, "shootFlag"),
reloadFlag(this, "reloadFlag")
{}

void GameControl::setShootFlag() {
    shootFlag.set();
}

void GameControl::setReloadFlag() {
    reloadFlag.set();
}

void GameControl::main() {
    for(;;) {
        hwlib::wait_ms(50);
        if (shootbutton.readButton())
        {
            beeper.setShootSound();
        }
        if (reload_button.readButton())
        {
            beeper.setReloadSound();
        }
    }
}