#ifndef KEYPAD_HPP
#define KEYPAD_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "KeypadListener.hpp"

#pragma once

class Keypad:public rtos::task<> {
    private:
    // rtos::channel<char,2> charChannel;
    KeypadListener& listener;
    void main() override{
        auto row0 = hwlib::target::pin_oc( hwlib::target::pins::a3 );
        auto row1 = hwlib::target::pin_oc( hwlib::target::pins::a1 );
        auto row2 = hwlib::target::pin_oc( hwlib::target::pins::a2 );
        auto row3 = hwlib::target::pin_oc( hwlib::target::pins::a0 );

        auto collumn0  = hwlib::target::pin_in( hwlib::target::pins::a7 );
        auto collumn1  = hwlib::target::pin_in( hwlib::target::pins::a6 );
        auto collumn2  = hwlib::target::pin_in( hwlib::target::pins::a5 );
        auto collumn3  = hwlib::target::pin_in( hwlib::target::pins::a4 );
        
        auto row_port = hwlib::port_oc_from( row0, row1, row2, row3 );
        auto collumn_port  = hwlib::port_in_from( collumn0,  collumn1,  collumn2,  collumn3  );
        auto matrix   = hwlib::matrix_of_switches( row_port, collumn_port );
        auto keypad   = hwlib::keypad< 16 >( matrix, "123A456B789C*0#D" );
        for(;;){
            hwlib::wait_ms(50);
            char key = keypad.getc(); 
            listener.write( key );
        }
    }
    public:
    Keypad(KeypadListener& listener):
        listener(listener)
        {}



    
};

#endif // KEYPAD_HPP