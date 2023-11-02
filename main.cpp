#include "hwlib.hpp"
#include "rtos.hpp"
#include "SignalPauseDetector.hpp"
#include "IR_Receiver.hpp"
#include "IR_Emitter.hpp"
#include "NecReciever.hpp"
#include "MsgLogger.hpp"
#include "logger2.hpp"
#include <array>

Logger *pLogger = nullptr;
int main() {
   auto dumpLogButtonPin= hwlib::target::pin_in( hwlib::target::pins::d42 );
   Logger logger(0,dumpLogButtonPin);
   pLogger = &logger;

   auto ir_detector_pin = hwlib::target::pin_in( hwlib::target::pins::d5);

   auto emitterPin = hwlib::target::d2_36kHz();
   // red output LED
   
   // switch which enables the 36 kHz output
   auto ld0 = hwlib::target::pin_out(hwlib::target::pins::d6);
   auto ld1 = hwlib::target::pin_out(hwlib::target::pins::d7);
   
   IR_receiver receiver(ir_detector_pin);
   // IR_emitter emitter(emitterPin);

   MsgLogger messageLogger;
   NecReciever nec(messageLogger);
   SignalPauseDetector detector(receiver, nec);

   
   rtos::run();
   return 0;
}