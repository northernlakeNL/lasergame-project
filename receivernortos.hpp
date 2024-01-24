#include "hwlib.hpp"
#include "rtos.hpp"
#include "emitternortos.hpp"
#include <optional>

class IR_receiver{
private:
    hwlib::target::pin_in& pin;

 
    

public:
    IR_receiver(hwlib::target::pin_in& pin) 
        : pin(pin){}


    int receive() {
        // hwlib::cout << pin.read()<< hwlib::endl;
        auto start = hwlib::now_us();
        while(pin.read()) {
            if(hwlib::now_us() - start > 5000){ // Timeout after 5 milliseconds
                // hwlib::cout << "error"<< hwlib::endl;
                return -1;
            }
            if(!pin.read()){
                break;
            }
        }
        // start = hwlib::now_us();
        // while(!pin.read()) {
        //     if(hwlib::now_us() - start > 9000) { // Timeout after 5 milliseconds
        //         // hwlib::cout << "error"<< hwlib::endl;
        //         return -1;
        //     }
        // }
        start = hwlib::now_us();
        while(!pin.read() ) {}
        auto high_duration = hwlib::now_us() - start;
        // hwlib::cout << high_duration << "\n";

        start = hwlib::now_us();
        while(pin.read()) {}
        auto low_duration = hwlib::now_us() - start;
        // hwlib::cout << low_duration << "\n";


        return high_duration > low_duration;
    }


};