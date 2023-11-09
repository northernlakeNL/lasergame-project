#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP

#include "hwlib.hpp"
#include "rtos.hpp"
#include "Beeper.hpp"
#include "Display.hpp"
#include "EnumClass.hpp"
#include "KeypadListener.hpp"
#include "ButtonListener.hpp"
#include "IR_Emitter.hpp"
#include "messages.hpp"
#include "logger2.hpp"
#include<array>

extern Logger* pLogger;


class GameControl: public rtos::task<>, public KeypadListener {
private:
    GameState game_state;
    Display& display;
    Beeper& beeper;
    ButtonListener& shootbutton;
    ButtonListener& reload_button;
    IR_emitter& emitter;
    Messages& messageLogger;
    rtos::channel<char,2> keyChannel;
    rtos::clock GameClock;
    char last_key = ' ';
    int player_count = 0;
    int player_id = 1;
    int bullets = 0;
    int lives = 0;
    int play_time = 0;
    int clock_counter = 0;
    int player_number = 0;
    int score = 0;
    int prio;
    bool pressed = false;
    std::array<int, 6> gameInfo;
    uint32_t data = 0;



public:
    GameControl(Display& display,Beeper& beeper, ButtonListener & shootbutton, ButtonListener& reload_button, IR_emitter& emitter, Messages& messageLogger, int prio);
    void main() override;
    void bitSplitter(uint32_t binaryValue);
    void shiftGameData();
    void write(char last_key) override;
};

#endif // GAMECONTROL_HPP
