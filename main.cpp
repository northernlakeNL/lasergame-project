#include "hwlib.hpp"
#include "rtos.hpp"
// #include "receivernortos.hpp"
#include "SignalPauseDetector.hpp"
#include "IR_Receiver.hpp"
#include "NecReciever.hpp"
#include <array>


int main() {

   auto ir_detector_pin = hwlib::target::pin_in( hwlib::target::pins::d5);
   // red output LED
   
   // switch which enables the 36 kHz output
   auto ld0 = hwlib::target::pin_out(hwlib::target::pins::d6);
   auto ld1 = hwlib::target::pin_out(hwlib::target::pins::d7);
   
   IR_receiver receiver(ir_detector_pin);
   
   
   // startup test
   // ld0.write(1);
   // ld0.flush();
   // hwlib::wait_ms(1000);
   // ld0.write(0);
   // ld0.flush();
   // ld1.write(1);
   // ld1.flush();
   // hwlib::wait_ms(1000);
   // ld1.write(0);
   // ld1.flush();
   

   // for(;;){
   //    auto signal = receiver.receive();

   //    if(signal == 0){
   //       hwlib::cout<< signal << "\n";
   //       ld0.write(1);
   //    }
   //    if(signal == 1){
   //       hwlib::cout<< signal << "\n";
   //    ld1.write(1);
   //    }
   //    else{
   //       ld0.write(0);
   //       ld1.write(0);
   //    }
   // }
   NecReciever nec;
   SignalPauseDetector detector(receiver, nec);
   
   rtos::run();
   return 0;
}