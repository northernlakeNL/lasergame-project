#ifndef IR_EMITTER_HPP
#define IR_EMITTER_HPP
#include "hwlib.hpp"
#include <array>
#include "rtos.hpp"
// #include "IR_Control.hpp"

class IR_emitter : public rtos::task<> {
private:
    hwlib::target::d2_36kHz& pin;
    hwlib::target::pin_in & button;
    bool pressed = false;
    std::array<int , 8> arr = {1,1,0,0,0,0,0,0};



public:
    IR_emitter(hwlib::target::d2_36kHz& pin, hwlib::target::pin_in & button):
      task(1, "IR_transmitter"),
      pin(pin),
      button(button)
      {}
  // template<typename S>
  void send(std::array<int , 8> arr){
      hwlib::cout << "hello" << "\n";
      pin.write(1);
      hwlib::wait_ms(9);
      pin.flush();
      pin.write(0);
      hwlib::wait_us(4500);
      for(int i : arr){
      
        if(i) {
          pin.write(1);
          hwlib::wait_us(560);
          pin.write(0);
          hwlib::wait_us(1690);
          pin.write(0);
          pin.flush();
        } 
        else {
          pin.write(1);
        
          hwlib::wait_us(560);
          pin.write(0);
          hwlib::wait_us(560);
          pin.write(0);
          pin.flush();
        }
      }
      pin.write(1);
      hwlib::wait_us(560);
      pin.write(0);
      hwlib::wait_ms(6);
      pin.write(1);
      hwlib::wait_us(560);
      pin.write(0);
    
  }
  
  void main() override {
    for(;;){
      
      if(button.read()){
        hwlib::cout << button.read() << hwlib::endl;
        pressed = true;
        send(  arr);
      }
      
      else if((!button.read() && pressed)) {
          pressed = false;
      }
      hwlib::wait_ms(100);
    }
  }
};

#endif