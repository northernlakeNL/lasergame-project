#include "GameControl.hpp"
#include "Beeper.hpp"
#include "hwlib.hpp"
#include "Button.hpp"
#include "rtos.hpp"
#include "logger2.hpp"
#include "SignalPauseDetector.hpp"
#include "IR_Receiver.hpp"
#include "IR_Emitter.hpp"
#include "NecReciever.hpp"
#include "MsgLogger.hpp"
#include <array>

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
   Button shoot_button(shoot_pin, "ShootButtonFlag", 2);
   Button reload_button(reload_pin, "ReloadButtonFlag", 3);
   GameControl game_control(beeper, shoot_button, reload_button, 1);
  

   auto ir_detector_pin = hwlib::target::pin_in( hwlib::target::pins::d5);

   // switch which enables the 36 kHz output
   auto emitterPin = hwlib::target::d2_36kHz();
   
   auto ld0 = hwlib::target::pin_out(hwlib::target::pins::d6);
   auto ld1 = hwlib::target::pin_out(hwlib::target::pins::d7);

   auto trigger= hwlib::target::pin_in( hwlib::target::pins::d26 );
   
   IR_receiver receiver(ir_detector_pin);
   IR_emitter emitter(emitterPin, trigger);

   MsgLogger messageLogger;
   NecReciever nec(messageLogger);
   SignalPauseDetector detector(receiver, nec);
  
   rtos::run();
   return 0;
}



