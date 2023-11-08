#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Display.hpp"
#include "EnumClass.hpp"
#include "KeypadListener.hpp"
// #include "beeper.hpp"
// #include "ButtonListener.hpp"

class GameControl: public rtos::task<>, public KeypadListener {
private:
    GameState game_state;
    Display& display;
    rtos::channel<char,2> charChannel;
    rtos::clock GameClock;
    char last_key = ' ';
    int player_count = 0;
    int bullets = 0;
    int lives = 0;
    int play_time = 0;
    int clock_counter = 0;
    void main() override;
    // beeper& beeper;
    // ButtonListener& buttonListener;
    // ButtonListener& buttonListener;

public:
    // GameControl(beeper& beeper, ButtonListener& buttonListener, ButtonListener& buttonListener);
    // void setShootFlag();
    // void setReloadFlag();
    GameControl(Display& display):
        task(1, "GameControlTask"),
        display(display),
        charChannel(this, "charChannel"),
        GameClock(this,1000000,"GameClock")
        {}
    void writeChannel(char last_key) override;
};

#endif // GAMECONTROL_HPP