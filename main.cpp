#include "hwlib.hpp"
#include "rtos.hpp"
#include "Settings.hpp"
#include "Keypad.hpp"
#include "Display.hpp"
#include "GameControl.hpp"

int main(){

   WDT->WDT_MR = WDT_MR_WDDIS;
   
   // wait for the PC console to start
   hwlib::wait_ms( 500 );
   Display display;
   Settings settings(display);
   GameControl game_control(settings);
   Keypad keypad(game_control);

   hwlib::cout << "start\n";

   rtos::run();
   return 0;
}