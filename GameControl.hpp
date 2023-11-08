#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Settings.hpp"
#include "Display.hpp"
#include "EnumClass.hpp"
// #include "beeper.hpp"
// #include "ButtonListener.hpp"

class GameControl: public rtos::task<>, public KeypadListener{
private:
    GameState game_state;
    Settings& settings;
    char last_key = ' ';
    int player_count = 0;
    int bullets = 0;
    int lives = 0;
    int play_time = 0;
    rtos::channel<char,2> charChannel;
    void main() override;

    // beeper& beeper;
    // ButtonListener& buttonListener;
    // ButtonListener& buttonListener;

public:
    // GameControl(beeper& beeper, ButtonListener& buttonListener, ButtonListener& buttonListener);
    // void setShootFlag();
    // void setReloadFlag();
    GameControl(Settings& settings):
        task(1, "GameControlTask"),
        settings(settings),
        charChannel(this, "charChannel")
        {}
    void setSettingsFlag();
    void writeChannel(char last_key) override;
};

#endif // GAMECONTROL_HPP