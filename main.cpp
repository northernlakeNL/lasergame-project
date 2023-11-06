#include "hwlib.hpp"
#include "rtos.hpp"
#include "ShootButton.hpp"
#include "GameControl.hpp"
#include "ReloadButton.hpp"
#include "Beeper.hpp"

int main( void ){
   namespace target = hwlib::target;
   auto reload_pin = target::pin_in(target::pins::d5);
   auto shoot_pin = target::pin_in(target::pins::d6);
   auto lsp = target::pin_out(target::pins::d7);
   Beeper beeper(lsp);
   ReloadButton reload_button(reload_pin);
   ShootButton shoot_button(shoot_pin);
   GameControl game_control(beeper, shoot_button, reload_button);
   rtos::run();
   return 0;
}

