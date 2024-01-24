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

void GameControl::shiftGameData(){
    data = 0;
    data |= 1;
    data <<= 4;
    data |= send_id;
    data <<= 4;
    data |= timedata;
    data <<= 4;
    data |= lives;
    data <<= 4;
    data |= bullets;
    data <<= 4; //score

    // hwlib::cout << data << "\n--------------------------------";
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
                    if (player_count < 2 or player_count > 8){
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
                        play_time = 5*60;
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
                while (send_id < player_count){
                    if (shootbutton.readButton() && !pressed) {
                        send_id++;
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
                    bullets = 0;
                    current_bullets = 0;
                    lives = 0;
                    player_count = 1;
                    play_time = 0;
                    send_id = 1;
                    game_state = GameState::SETTINGS;
                }
                break;
            case GameState::RECEIVE:
                hwlib::wait_ms(10);
                display.updateDisplay(DisplayMenuState::RECEIVE);
                hwlib::wait_ms(500);
                if ( messageLogger.messageRead()!= 0 ){
                    bitSplitter(msg = messageLogger.messageRead());
                    hwlib::wait_ms(20);
                    startbit = gameInfo[5];
                    player_id = gameInfo[4];
                    send_id = gameInfo[4];
                    play_time = gameInfo[3] * 60;
                    lives = gameInfo[2];
                    bullets = gameInfo[1];
                    current_bullets = gameInfo[1];
                    score = gameInfo[0];
                    beeper.setEmptyClipSound();
                    hwlib::wait_ms(50);
                    game_state = GameState::PREGAME;
                }         
                break;
            case GameState::PREGAME:
                hwlib::wait_ms(500);
                display.ReceivedSettings(play_time,lives,current_bullets);
                last_key = keyChannel.read();
                if(last_key == 'A'){
                    game_state = GameState::GAME;
                }
                else if (last_key == 'D'){
                    game_state = GameState::IDLE;
                }
            case GameState::GAME:
                send_id = player_id;
                hwlib::wait_ms(10);
                display.gameInfo(play_time,lives,current_bullets,player_id); // play_time is in seconds
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
                    bitSplitter(msg = messageLogger.messageRead());
                    enemy_id = gameInfo[4];
                    if (player_id != enemy_id){
                        lives -=1;
                        beeper.setHitFlag();
                        messageLogger.resetHit();
                        // display.HitInfo(play_time,lives,current_bullets,enemy_id); // play_time is in seconds
                        // hwlib::wait_ms(10000);
                    }
                }
                GameClock.clear();
                while(play_time*60 > 0){
                    wait(GameClock);
                    play_time--;
                    hwlib::wait_ms(50);
                    score +=0.5; // elke seconde levend is 10 punten
                    display.gameInfo(play_time,lives,current_bullets, player_id); // play_time is in seconds
                    if(play_time <= 0 || lives <= 0){
                        game_state = GameState::FINISH;
                        break;
                    }
                    break;
                }
                break;
            case GameState::FINISH:
                hwlib::wait_ms(50);
                while(play_time*60 > 0){
                    wait(GameClock);
                    play_time--;
                    hwlib::wait_ms(50);
                    display.gameOverScreen(play_time); // play_time is in seconds
                }
                if (play_time <= 0){
                    if (player_id == 1){
                        display.updateDisplay(DisplayMenuState::FINISH_HOST);
                        FinalScore[player_id] = score;
                        if(messageLogger.isHit()){
                            bitSplitter(msg = messageLogger.messageRead());
                            int id = gameInfo[4] -1;
                            FinalScore[id] = gameInfo[0];
                        }
                    }
                    else if (player_id != 1){
                        display.updateDisplay(DisplayMenuState::FINISH_PLAYER);
                        if (shootbutton.readButton() && !pressed){
                            pressed = true;
                            shiftGameData();
                            emitter.send(data);
                        }
                    }
                    last_key = keyChannel.read();
                    if (last_key == 'A'){
                            game_state = GameState::WINNERSCREEN;
                            break;
                        }
                }
                break;
            case GameState::WINNERSCREEN:
                for (int i = 0; i < 7; i++){
                    if (FinalScore[i] > winner_score){
                        winner_score = FinalScore[i];
                        winner_id = i+1;
                    }
                }
                display.WinnerScreen(winner_id, winner_score);
                if (last_key == 'A'){
                        game_state = GameState::IDLE;
                        break;
                    }
        } //end switch state
    } //end for loop
} //end main

void GameControl::write(char key){
    keyChannel.write(key);
}