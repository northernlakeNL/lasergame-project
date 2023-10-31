#include "Keypad.hpp"

char Keypad::keypadRead(){	
   hwlib::wait_ms( 500 );

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

   return keypad.getc();
}
