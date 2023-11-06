#include "GameControl.hpp"

// GameControl::GameControl(Beeper& beeper, ButtonListener& shootbutton, ButtonListener& reload_button) :
// GameControl::GameControl(Settings& settings, Display& display):
// task(1, "GameControlTask"),
// settings(settings),
// display(display)
// beeper(beeper),
// shootbutton(shootbutton),
// reload_button(reload_button),
// shootFlag(this, "shootFlag"),
// reloadFlag(this, "reloadFlag")
// {}

// void GameControl::setShootFlag() {
//     shootFlag.set();
// }

// void GameControl::setReloadFlag() {
//     reloadFlag.set();
// }

void GameControl::main() {
    game_state = GameState::IDLE;
    for(;;) {
        switch(game_state){
            case GameState::IDLE:
                hwlib::wait_ms(50);
                hwlib::cout <<"GameControl\n";
                settings.setCase(MenuState::IDLE);
                settings.setSettingsFlag();
                hwlib::wait_ms(500);
                hwlib::cout << "RETURN OF THE IDLE\n";
                last_key = charChannel.read();
                if (last_key == 'A'){
                    charChannel.clear();
                    game_state = GameState::SETTINGS;
                    break;
                }
                break;
            case GameState::SETTINGS:
                hwlib::wait_ms(50);
                hwlib::cout <<"SettingsControl\n";
                settings.setCase(MenuState::MENU);
                settings.setSettingsFlag();
                hwlib::wait_ms(500);
                hwlib::cout << "RETURN OF THE SETTING\n";
                last_key = charChannel.read();
                if (last_key == '1'){
                    charChannel.clear();
                    game_state = GameState::SETTINGS;
                    break;
                }
                break;
            case GameState::COUNTDOWN: 
                hwlib::wait_ms(50);
                break;
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
