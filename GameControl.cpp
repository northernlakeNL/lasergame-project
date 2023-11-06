#include "GameControl.hpp"
#include "logger2.hpp"

extern Logger* pLogger;

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
        if (shootbutton.readButton())
        {
            hwlib::cout << "kaas\n";
            beeper.setShootSound();
        }
        if (reload_button.readButton())
        {
            hwlib::cout<< "spekkoek\n";
            beeper.setReloadSound();
        }
    }
}