#ifndef IR_EMITTER_HPP
#define IR_EMITTER_HPP
#include "hwlib.hpp"
#include <array>
#include "rtos.hpp"
#include "IR_Control.hpp"
template<typename S>
class IR_emitter : public rtos::task<>, public IR_Control {
private:
    hwlib::target::d2_36kHz& pin;
    hwlib::target::pin_in & button;
    bool pressed = false;



public:
    IR_emitter(hwlib::target::d2_36kHz& pin, hwlib::target::pin_in & button):
      task(1, "IR_transmitter"),
      pin(pin),
      button(button)

      {}
  
  void send(std::array<int , S> arr) override{
    if(arr != NULL){
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
  }
  
  void main() override {
    for(;;){
      if(button.read() && pressed){
        pressed = true;
        emitter.send(shoot);
      }
      
      else if((!sw0.read() && pressed)  && (!sw1.read()&& pressed)) {
          pressed = false;
      }
      hwlib::wait_ms(100);
    }
  }
};
