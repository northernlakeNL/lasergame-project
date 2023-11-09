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
        data |= play_time;
        data <<= 4;
        data |= lives;
        data <<= 4;
        data |= bullets;
        data <<= 4;
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
                else if(last_key == 'B'){
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
                        play_time = 5 ;
                    }
                    else if (last_key == '2'){
                        play_time = 10;
                    }
                    else if (last_key == '3'){
                        play_time = 15;
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
                    break;
                }
                if (last_key == 'C'){
                    game_state = GameState::SEND;
                    break;
                }
                break;

            case GameState::SEND:
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
                display.updateDisplay(DisplayMenuState::RECEIVE);
                // messageLogger.messageRead
                break;

            case GameState::GAME:
                if (shootbutton.readButton() && !pressed){
                    pressed = true;
                    if (bullets == 0){
                        beeper.setEmptyClipSound();
                    }
                    else{
                        bullets -= 1;
                        emitter.setButtonFlag();
                        beeper.setShootSound();
                    }
                    
                }
                else if (reload_button.readButton() && !pressed){
                    pressed = true;
                    beeper.setReloadSound();
                    bullets = 5;
                }
                else if ((!shootbutton.readButton() && pressed) && (!reload_button.readButton() && pressed)) {
                    pressed = false;
                }
                
                if(messageLogger.isHit()){
                    beeper.setHitFlag();
                    messageLogger.resetHit();
                }

                // zet in game state //
                GameClock.clear();
                while(play_time >0){
                    
                    wait(GameClock);
                    play_time--;
                    display.gameInfo(play_time,lives,bullets); // play_time is in seconds
                    if(play_time <= 0 ){
                        hwlib::cout << "finish game\n";
                        game_state = GameState::FINISH;
                        break;
                    }
                    break;
                }
                break;
            case GameState::FINISH:
                display.updateDisplay(DisplayMenuState::FINISH);
                break;
        }
    }
}

void GameControl::write(char key){
    keyChannel.write(key);
}