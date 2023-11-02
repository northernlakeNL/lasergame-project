#include "hwlib.hpp"
#include "rtos.hpp"

class IR_emitter : public rtos::task<> {
private:
    hwlib::target::d2_36kHz& pin;
    rtos::channel<bool, 10> values;


public:
    IR_emitter(hwlib::target::d2_36kHz& pin)
        : rtos::task<>(1, "IR_transmitter"), pin(pin), values(this, "values") {}

  void send(bool value) {
    values.write(value);
  }

  void main() override {
    for(;;) {
      
        bool value = values.read();
      if(value) {
          pin.write(1);
          pin.flush();
          hwlib::wait_us(560);
          pin.write(0);
          pin.flush();
          hwlib::wait_us(1690);
          pin.write(1);
          
      } 
      else {
          pin.write(1);
          pin.flush();
          hwlib::wait_us(560);
          pin.write(0);
          pin.flush();
          hwlib::wait_us(560);
      }

    }
  }
};