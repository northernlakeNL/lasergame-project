#include "GameControl.hpp"

void GameControl::main() {
    game_state = GameState::IDLE;
    for(;;) {
        switch(game_state){
            case GameState::IDLE:
                hwlib::wait_ms(50);
                settings.setCase(MenuState::IDLE); //select menu variabele andere enum
                last_key = charChannel.read();
                if (last_key == 'A'){
                    game_state = GameState::SETTINGS;
                    break;
                }
                break;
            case GameState::SETTINGS:
                charChannel.clear();
                hwlib::wait_ms(100);
                settings.setCase(MenuState::MENU);
                last_key = charChannel.read();
                if (last_key == '1'){
                    charChannel.clear();
                    hwlib::wait_ms(100);
                    settings.setCase(MenuState::PLAYER_COUNT);
                    last_key = charChannel.read();
                    player_count = last_key - '0';
                    break;
                }
                if (last_key == '2'){
                    charChannel.clear();
                    hwlib::wait_ms(100);
                    settings.setCase(MenuState::PLAY_TIME);
                    last_key = charChannel.read();
                    if (last_key == '1'){
                        play_time = 5;
                    }
                    else if (last_key == '2'){
                        play_time = 10;
                    }
                    else if (last_key == '3'){
                        play_time = 15;
                    }
                }
                if (last_key == '3'){
                    charChannel.clear();
                    hwlib::wait_ms(100);
                    settings.setCase(MenuState::LIVES);
                    last_key = charChannel.read();
                    lives = last_key - '0';
                    break;
                }
                if (last_key == '4'){
                    charChannel.clear();
                    hwlib::wait_ms(100);
                    settings.setCase(MenuState::BULLETS);
                    last_key = charChannel.read();
                    bullets = last_key = '0';
                    break;
                }
                if (last_key == 'C'){
                    hwlib::cout << player_count << "\n" << bullets << "\n" << lives << "\n" << play_time << "\n"; 
                    charChannel.clear();
                    hwlib::wait_ms(100);
                    //zet neer (IR Data sturen)


                    // zet in game state // 
                    GameClock.clear();
                    for(;;){
                        wait(GameClock);
                        clock_counter++;
                        hwlib::cout << clock_counter << "\n";
                        if(clock_counter >= (play_time * 60) ){
                            hwlib::cout << "finish game\n";
                            // needs to leave stage right here.
                            break;
                        }
                    }
                    // zet in game state // 
                    break;
                }
            case GameState::GAME:
                hwlib::wait_ms(50);
                hwlib::cout << "play game\n";
                break;
            case GameState::FINISH:
                hwlib::wait_ms(50);
                break;
        }
    }
}

void GameControl::writeChannel(char key){
    charChannel.write(key);
}