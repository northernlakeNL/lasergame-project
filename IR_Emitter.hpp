#include "hwlib.hpp"
#include "rtos.hpp"

class IR_emitter : public rtos::task<> {
private:
    hwlib::target::pin_out& pin;
    rtos::channel<bool, 10> values;


public:
    IR_emitter(hwlib::target::pin_out& pin)
        : rtos::task<>(1, "IR_transmitter"), pin(pin), values(this, "values") {}

  void send(bool value) {
    values.write(value);
  }

  void main() override {
    for(;;) {
      
        bool value = values.read();
      if(value) {
          // pin.write(1);
          // pin.flush();
          // hwlib::wait_us(3200);
          // pin.write(0);
          // pin.flush();
          // hwlib::wait_us(1600);
          pin.write(1);
          hwlib::wait_us(5000);
          pin.flush();
      } 
      else {
        pin.write(0);
        hwlib::wait_us(5000);
        pin.flush()
          // pin.write(1);
          // pin.flush();
          // hwlib::wait_us(1600);
          // pin.write(0);
          // pin.flush();
          // hwlib::wait_us(3200);
      }

    }
  }
};