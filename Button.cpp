#include "Button.hpp"

// char Button::buttonPressed(){
//     if(PewPress){
//         return 'A';
//     }
//     else if (reloadPress){
//         return 'B';
//     }
//     return 'C';
// }

bool Button::reload(){
    static bool pressed = false;
    if (d50.read() && !pressed){
        pressed = true;
        hwlib::cout << "reload\n";
        return true;
    }
    else if (!d50.read()){
        pressed = false;
    } 
    return false;
}

bool Button::shoot(){
    static bool pressed = false;
    if (d51.read() && !pressed){
        pressed = true;
        hwlib::cout << "pew\n";
        return true;
    }
    else if (!d51.read()){
        pressed = false;
    } 
    return false;
}