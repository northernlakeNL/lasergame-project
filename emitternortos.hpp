#include "hwlib.hpp"
// #include "rtos.hpp"

class IR_emitter {
private:
    hwlib::target::d2_36kHz& pin;



public:
    IR_emitter(hwlib::target::d2_36kHz& pin)
        :pin(pin) {}

  void send(bool value) {
      if(value) {
        pin.write(1);
        hwlib::wait_us(3200);
        pin.write(0);
        hwlib::wait_us(1600);
        //   pin.flush();
        pin.write(1);
        hwlib::wait_us(100);
        pin.write(0);
      } 
      else {
          pin.write(1);
          pin.flush();
          hwlib::wait_us(1600);
          pin.write(0);
          pin.flush();
          hwlib::wait_us(3200);
           pin.write(1);
          hwlib::wait_us(100);
          pin.write(0);
     }
  }
};