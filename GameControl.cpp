#include "GameControl.hpp"

GameControl::GameControl(Beeper& beeper, ButtonListener& shootbutton, ButtonListener& reload_button) :
task(1, "GameControlTask"),
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
        hwlib::cout << "jemoeder"; 
        hwlib::cout << shootbutton.readButton();
        hwlib::cout << reload_button.readButton();
        
    }
}