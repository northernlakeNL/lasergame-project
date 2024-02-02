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
#include <array>
#include <map>
#include <string>

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
    int startbit = 0;
    int player_count = 1;
    int enemy_id = 0;
    int bullets = 0;
    int player_number = 0;
    int lives = 0;
    int play_time = 0;
    int timedata = 0;
    int clock_counter = 0;
    int current_bullets = 0;
    int score = 0;
    int player_id = 1;
    int send_id = 1;
    int prio;
    bool pressed = false;
    int winner_id = 0; 
    int winner_score = 0;
    uint32_t msg = 0 ;
    std::array<int, 6> gameInfo;
    uint32_t data = 0;
    uint32_t ID = 0;
    int FinalScore[8] = {0,0,0,0,0,0,0,0};
    int filled = 1;
    int new_score = 0;


public:
    GameControl(Display& display,Beeper& beeper, ButtonListener & shootbutton, ButtonListener& reload_button, IR_emitter& emitter, Messages& messageLogger, int prio);
    void main() override;
    void bitSplitter(uint32_t binaryValue);
    void shiftGameData();
    void write(char last_key) override;
};

#endif // GAMECONTROL_HPP