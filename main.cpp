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
   auto reload_pin = target::pin_in(target::pins::d26);
   auto shoot_pin = target::pin_in(target::pins::d6);
   auto lsp = target::pin_out(target::pins::d7);
   auto ir_detector_pin = hwlib::target::pin_in( hwlib::target::pins::d5);

   // switch which enables the 36 kHz output
   auto emitterPin = hwlib::target::d2_36kHz();
   Beeper beeper(lsp, 8);
   Button shoot_button(shoot_pin, "ShootButtonFlag", 5);
   Button reload_button(reload_pin, "ReloadButtonFlag", 6);
   IR_emitter emitter(emitterPin, shoot_pin);
   IR_receiver receiver(ir_detector_pin);
   MsgLogger messageLogger;
   NecReciever nec(messageLogger);
   SignalPauseDetector detector(receiver, nec);

   GameControl game_control(beeper, shoot_button, reload_button, emitter, 4);
  

 


  
   rtos::run();
   return 0;
}



