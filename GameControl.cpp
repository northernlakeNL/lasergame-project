#include "GameControl.hpp"

GameControl::GameControl(Display& display,Beeper& beeper, ButtonListener & shootbutton, ButtonListener& reload_button, IR_emitter& emitter, Messages& messageLogger, int prio):
    task(prio, "GameControlTask"),
    display(display),
    beeper(beeper),
    shootbutton(shootbutton),
    reload_button(reload_button),
    emitter(emitter),
    messageLogger(messageLogger),
    keyChannel(this, "keyChannel"),
    GameClock(this, 1000000,"GameClock")
{}

void GameControl::bitSplitter(uint32_t binaryValue){
    for (unsigned int i = 0; i < 6; i++) {
        unsigned int part = (binaryValue) & 0xF;
        binaryValue >>= 4;
        gameInfo[i]= part;
        pLogger->logInt(part);
    }
}
// player_id, play_time,lives,bullets, score
void GameControl::shiftGameData(){
    data = 0;
    data |= 1;
    data <<= 4;
    data |= player_id;
    data <<= 4;
    data |= timedata;
    data <<= 4;
    data |= lives;
    data <<= 4;
    data |= bullets;
    data <<= 4; //score
}

void GameControl::main() {
    game_state = GameState::IDLE;
    for(;;) {
        switch(game_state){
            case GameState::IDLE:
                display.updateDisplay(DisplayMenuState::IDLE); //select menu variabele andere enum
                last_key = keyChannel.read();
                if (last_key == 'A'){
                    game_state = GameState::SETTINGS;
                    break;
                }
                if(last_key == 'B'){
                    game_state = GameState::RECEIVE;
                    break;
                }
                break;
            case GameState::SETTINGS:
                display.updateDisplay(DisplayMenuState::MENU);
                last_key = keyChannel.read();
                if (last_key == '1'){ // aantal spelers
                    display.updateDisplay(DisplayMenuState::PLAYER_COUNT);
                    last_key = keyChannel.read();
                    player_count = last_key - '0';
                    if (player_count < 2){
                        display.updateDisplay(DisplayMenuState::ERROR);
                        last_key = keyChannel.read();
                        if (last_key == 'A'){
                            game_state = GameState::SETTINGS;
                        }
                    }
                    break;
                }
                if (last_key == '2'){ // speel tijd
                    display.updateDisplay(DisplayMenuState::PLAY_TIME);
                    last_key = keyChannel.read();
                    if (last_key == '1'){
                        play_time = 5 *60;
                        timedata =5;
                    }
                    else if (last_key == '2'){
                        play_time = 10*60;
                        timedata =10;
                    }
                    else if (last_key == '3'){
                        play_time = 15*60;
                        timedata =15;
                    }
                    break;
                }
                if (last_key == '3'){ // levens
                    display.updateDisplay(DisplayMenuState::LIVES);
                    last_key = keyChannel.read();
                    lives = last_key - '0';
                    break;
                }
                if (last_key == '4'){
                    display.updateDisplay(DisplayMenuState::BULLETS);
                    last_key = keyChannel.read();
                    bullets = last_key - '0';
                    current_bullets = last_key - '0';
                    
                    break;
                }
                if (last_key == 'C'){
                    game_state = GameState::SEND;
                    break;
                }
                break;
            case GameState::SEND:
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::DONE);
                while (player_id < player_count){
                    if (shootbutton.readButton() && !pressed) {
                        ++player_id;
                        pressed = true;
                        shiftGameData();
                        beeper.setEmptyClipSound(); 
                        emitter.send(data);
                    }
                    else if (!shootbutton.readButton() && pressed) {
                        pressed = false;
                    }
                    hwlib::wait_ms(50);
                }
                last_key = keyChannel.read();
                if(last_key == 'A'){
                    game_state = GameState::GAME;
                }
                else if (last_key == 'D'){
                    game_state = GameState::SETTINGS;
                }
                break;
            case GameState::RECEIVE:
                hwlib::wait_ms(10);
                display.updateDisplay(DisplayMenuState::RECEIVE);
                // hwlib::wait_ms(20);
                if ( messageLogger.messageRead()!= 0 ){
                    bitSplitter(msg = messageLogger.messageRead());
                    startbit = gameInfo[0];
                    player_id = gameInfo[1];
                    play_time = gameInfo[2];
                    lives = gameInfo[3];
                    bullets = gameInfo[4];
                    current_bullets = gameInfo[4];
                    score = gameInfo[5];
                    beeper.setEmptyClipSound();
                    game_state = GameState::GAME;
                }                
                break;
            case GameState::GAME:
            hwlib::wait_ms(10);
            display.gameInfo(play_time,lives,current_bullets); // play_time is in seconds
                if (shootbutton.readButton() && !pressed){
                    pressed = true;
                    if (current_bullets == 0){
                        beeper.setEmptyClipSound();
                    }
                    else{
                        current_bullets--;
                        shiftGameData();
                        emitter.send(data);
                        beeper.setShootSound();
                    }
                }
                else if (reload_button.readButton() && !pressed){
                    pressed = true;
                    current_bullets = bullets;
                    beeper.setReloadSound();
                }
                else if ((!shootbutton.readButton() && pressed) && (!reload_button.readButton() && pressed)) {
                    pressed = false;
                }
                if(messageLogger.isHit()){
                    lives -=1;
                    beeper.setHitFlag();
                    messageLogger.resetHit();
                }
                GameClock.clear();
                while(play_time >0){
                    wait(GameClock);
                    play_time--;
                    hwlib::wait_ms(50);
                    display.gameInfo(play_time,lives,current_bullets); // play_time is in seconds
                    if(play_time <= 0 || lives <= 0){
                        game_state = GameState::FINISH;
                        break;
                    }
                    break;
                }
                break;
            case GameState::FINISH:
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::FINISH);
                last_key = keyChannel.read();
                if (last_key == 'A'){
                    game_state = GameState::IDLE;
                    break;
                }
                break;
        } //end switch state
    } //end for loop
} //end main

void GameControl::write(char key){
    keyChannel.write(key);
}