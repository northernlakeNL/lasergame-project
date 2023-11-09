#include "GameControl.hpp"

    GameControl::GameControl(Display& display,Beeper& beeper, ButtonListener & shootbutton, ButtonListener& reload_button, IR_emitter& emitter, Messages& messageLogger, int prio);
        task(prio, "GameControlTask"),
        display(display),
        beeper(beeper),
        shootbutton(shootbutton),
        reload_button(reload_button),
        emitter(emitter),
        messageLogger(messageLogger),
        GameClock(this,1000000,"GameClock"),
        keyChannel(this, "keyChannel")
    {}

void GameControl::bitSplitter(uint32_t binaryValue){

    for (unsigned int i = 0; i < 6; i++) {
        unsigned int part = (binaryValue) & 0xF;
        binaryValue >>= 4;
        gameInfo[i]= part;
        // hwlib::cout << ": " << part << hwlib::endl;
        pLogger->logInt(part);
        
    }
    
    // return(gameInfo);
}


void GameControl::main() {
    game_state = GameState::IDLE;
    for(;;) {
        switch(game_state){
            case GameState::IDLE:
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::IDLE); //select menu variabele andere enum
                last_key = keyChannel.read();
                if (last_key == 'A'){
                    game_state = GameState::SETTINGS;
                    break;
                }
                break;
            case GameState::SETTINGS:
                hwlib::wait_ms(100);
                display.updateDisplay(DisplayMenuState::MENU);
                last_key = keyChannel.read();
                if (last_key == '1'){ // aantal spelers
                    hwlib::wait_ms(100);
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
                    hwlib::wait_ms(100);
                    display.updateDisplay(DisplayMenuState::PLAY_TIME);
                    last_key = keyChannel.read();
                    if (last_key == '1'){
                        play_time = 5 * 60;
                    }
                    else if (last_key == '2'){
                        play_time = 10 * 60;
                    }
                    else if (last_key == '3'){
                        play_time = 15 * 60;
                    }
                    break;
                }
                if (last_key == '3'){ // levens
                    hwlib::wait_ms(100);
                    display.updateDisplay(DisplayMenuState::LIVES);
                    last_key = keyChannel.read();
                    lives = last_key - '0';
                    break;
                }
                if (last_key == '4'){
                    hwlib::wait_ms(100);
                    display.updateDisplay(DisplayMenuState::BULLETS);
                    last_key = keyChannel.read();
                    bullets = last_key - '0';
                    break;
                }
                if (last_key == 'C'){
                    hwlib::wait_ms(100);
                    display.updateDisplay(DisplayMenuState::DONE);
                    game_state = GameState::SEND;
                    break;
                }
                break;
            case GameState::SEND:
                // zet neer (IR Data sturen)
                // for(player_id = 2; player_id < player_count; ++player_id){
                //     bitshift player_id NIET player_count
                // }
                // IR SEND ^
                hwlib::wait_ms(100);
                last_key = keyChannel.read();
                if(last_key == 'A'){
                    game_state = GameState::GAME;
                }
                else if (last_key == 'D'){
                    game_state = GameState::SETTINGS;
                }
                break;
            case GameState::GAME:
                hwlib::wait_ms(50);
                if (shootbutton.readButton() && !pressed){
                    pressed = true;
                    hwlib::wait_ms(10);
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
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::FINISH);
                break;
        }
    }
}

void GameControl::write(char key){
    keyChannel.write(key);
}