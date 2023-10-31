#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP
#include "hwlib.hpp"
#include "rtos.hpp"

#include <optional>

class IR_receiver {
private:
    hwlib::target::pin_in& pin;
    
public:
    IR_receiver(hwlib::target::pin_in& pin):
    pin(pin) 
    {}

    bool read(){
        return pin.read();
    }
};
#endif 





//    int receive() {
//         auto start = hwlib::now_us();
//         while(pin.read()) {
//             if(hwlib::now_us() - start > 5000) { // Timeout after 5 milliseconds
//                 return -1;
//             }
//         }
//         start = hwlib::now_us();
//         while(!pin.read()) {
//             if(hwlib::now_us() - start > 5000) { // Timeout after 5 milliseconds
//                 return -1;
//             }
//         }

//         start = hwlib::now_us();
//         while(pin.read()) {}
//         auto high_duration = hwlib::now_us() - start;
//         hwlib::cout << high_duration << "\n";

//         start = hwlib::now_us();
//         while(!pin.read()) {}
//         auto low_duration = hwlib::now_us() - start;

        
//         return high_duration > low_duration;
//     }

//     void main() override {
        
//         for(;;){
//             int value = receive();
//             if (value != -1) {
//                 hwlib::cout << "Received value: " << value << "\n";
//             }
//         }
//     }