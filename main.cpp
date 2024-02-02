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
#include "Keypad.hpp"
#include "Display.hpp"

Logger *pLogger = nullptr;

int main( void ){
   WDT->WDT_MR = WDT_MR_WDDIS;

   Display display(10);
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

   Beeper beeper(lsp, 9);
   Button shoot_button(shoot_pin, "ShootButtonFlag", 6);
   Button reload_button(reload_pin, "ReloadButtonFlag", 7);
   IR_emitter emitter(emitterPin, shoot_pin, 3);
   IR_receiver receiver(ir_detector_pin);
   MsgLogger messageLogger(8);
   NecReciever nec(messageLogger, 1);
   SignalPauseDetector detector(receiver, nec, 2);
   GameControl game_control(display, beeper, shoot_button, reload_button, emitter, messageLogger, 4);
   Keypad keypad(game_control);
  
   rtos::run();
   return 0;
}