#include "hwlib.hpp"
#include "rtos.hpp"

#include "receivernortos.hpp"
// #include "emitternortos.hpp"
#include <array>




int main() {

   auto ir = hwlib::target::d2_36kHz();
   //  auto ir_detector_pin = hwlib::target::pin_in( hwlib::target::pins::d5);
   // red output LED
   
   // switch which enables the 36 kHz output
   // auto ld0 = hwlib::target::pin_out(hwlib::target::pins::d6);
   // auto ld1 = hwlib::target::pin_out(hwlib::target::pins::d7);
   

    auto sw1 = hwlib::target::pin_in(hwlib::target::pins::d8);
    auto sw0 = hwlib::target::pin_in(hwlib::target::pins::d9);

    IR_emitter emitter(ir);
   //  IR_receiver receiver(ir_detector_pin);
   
   
   // startup test
   // ld0.write(1);
   // ld0.flush();
   hwlib::wait_ms(1000);
   // ld0.write(0);
   // ld0.flush();
   // ld1.write(1);
   // ld1.flush();
   // hwlib::wait_ms(1000);
   // ld1.write(0);
   // ld1.flush();
   bool pressed = false;
   std::array<bool>shoot {1,1,1,1,0,0};
   

for(;;){

   // hwlib::cout << pressed << "\n";


   for(unsigned int i = 0 ; i < shoot.size())
      if(sw1.read() && !pressed){
      pressed = true;
      emitter.send(true);
   }
   else if(sw0.read() && !pressed){
      pressed = true;
      emitter.send(false);
   }



   // if(sw1.read() && !pressed){
   //    pressed = true;
   //    emitter.send(true);
   // }
   // else if(sw0.read() && !pressed){
   //    pressed = true;
   //    emitter.send(false);
   // }
   
   // else if((!sw0.read() && pressed)  && (!sw1.read()&& pressed)) {
   //    pressed = false;
   // }

   // auto signal = receiver.receive();
   // receiver.receive();
   // hwlib::cout<< signal << "\n";
   // if(signal == 0){
   //    ld0.write(1);
   //    hwlib::wait_ms(1000);
   // }
   // if(signal == 1){
   // ld1.write(1);
   // hwlib::wait_ms(1000);
   // }
   // else{
   //    ld0.write(0);
   //    ld1.write(0);
   // }
   // ld.write(signal);
   // ld.flush();
   

   // hwlib::cout << "ir signal"<<signal << hwlib::endl;
   // if(!signal){
   //    hwlib::wait_ms(1000);
   // }
   
   // hwlib::wait_ms(1);

}

   return 0;
}





// int main() {

//    // auto ir = hwlib::target::d2_36kHz();
//     auto ir_detector_pin = hwlib::target::pin_in( hwlib::target::pins::d5);
//    // red output LED
   
//    // switch which enables the 36 kHz output
//    auto ld0 = hwlib::target::pin_out(hwlib::target::pins::d6);
//    auto ld1 = hwlib::target::pin_out(hwlib::target::pins::d7);
   

//    //  auto sw = hwlib::target::pin_in(hwlib::target::pins::d8);

//    //  IR_emitter emitter(ir);
//     IR_receiver receiver(ir_detector_pin);
   
   
//    // startup test
//    ld0.write(1);
//    ld0.flush();
//    hwlib::wait_ms(1000);
//    ld0.write(0);
//    ld0.flush();
//    ld1.write(1);
//    ld1.flush();
//    hwlib::wait_ms(1000);
//    ld1.write(0);
//    ld1.flush();
//    // bool pressed = false;
   

// for(;;){


//    // if(sw.read() && !pressed){
//       // pressed = true;
//       // emitter.send(true);
//    // }
//    // else if(!sw.read() && pressed) {
//       // pressed = false;
//    // }
//    auto signal = receiver.receive();
//    // receiver.receive();
//    hwlib::cout<< signal << "\n";
//    if(signal == 0){
//       ld0.write(1);
//       hwlib::wait_ms(1000);
//    }
//    if(signal == 1){
//    ld1.write(1);
//    hwlib::wait_ms(1000);
//    }
//    else{
//       ld0.write(0);
//       ld1.write(0);
//    }
//    // ld.write(signal);
//    // ld.flush();
   

//    // hwlib::cout << "ir signal"<<signal << hwlib::endl;
//    // if(!signal){
//    //    hwlib::wait_ms(1000);
//    // }
   
//    // hwlib::wait_ms(1);

// }

//    return 0;
// }