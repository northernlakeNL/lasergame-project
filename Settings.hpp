#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include "hwlib.hpp"
#include "Display.hpp"

#pragma once

class Settings{
    private:
    void main();
public:
    std::array<int, 4> gameSettings(); //{player count, play time, lives, bullets(reload is infinite)}
    // int setLives();
};

//    display.gameInfo(10, 10, time);

 
#endif //SETTINGS_HPP