#include "GameControl.hpp"
#include "Beeper.hpp"
#include "hwlib.hpp"
#include "Button.hpp"
#include "rtos.hpp"
#include "logger2.hpp"

Logger *pLogger = nullptr;

int main( void ){

   auto dumpLogButtonPin= hwlib::target::pin_in( hwlib::target::pins::d4 );
   Logger logger(0,dumpLogButtonPin);
   pLogger = &logger;
   namespace target = hwlib::target;
   auto reload_pin = target::pin_in(target::pins::d5);
   auto shoot_pin = target::pin_in(target::pins::d6);
   auto lsp = target::pin_out(target::pins::d7);
   Beeper beeper(lsp, 4);
   Button shoot_button(shoot_pin, "ShootButton", 2);
   Button reload_button(reload_pin, "ReloadButton", 3);
   GameControl game_control(beeper, shoot_button, reload_button, 1);
   rtos::run();
   return 0;
}

