#include "Game.hpp"

void Game::gamePlay(){ //20 seconds game start
    Button button;
    wait(time);
    while(true){
        if (button.reload()){
            bullets = bullets_max;
        }
        if (button.shoot()){
            hwlib::cout << "trigger pressed \n";
            if (bullets > 0){
                bullets--;
            }
            hwlib::cout << bullets << "\n";
            if (bullets <= 0){
                bullets = 0;
            }
            // display.gameInfo(play_time, lives_max, bullets);
        }
    }
}