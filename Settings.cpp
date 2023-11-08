#include "Settings.hpp"

void Settings::main(){
    hwlib::cout<<"settings main\n";
    gameSettings = MenuState::IDLE;
    for(;;){
        switch (gameSettings){
            case MenuState::IDLE:
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::IDLE);
                gameSettings = menu_pool.read();
                break;
            case MenuState::MENU:
                menu_pool.clear();
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::MENU);
                gameSettings = menu_pool.read();
                break;
            case MenuState::PLAYER_COUNT:
                menu_pool.clear();
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::PLAYER_COUNT);
                gameSettings = menu_pool.read();
                break;
            case MenuState::LIVES:
                menu_pool.clear();
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::LIVES);
                gameSettings = menu_pool.read();
                break;
            case MenuState::BULLETS:
                menu_pool.clear();
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::BULLETS);
                gameSettings = menu_pool.read();
                break;
            case MenuState::PLAY_TIME:
                menu_pool.clear();
                hwlib::wait_ms(50);
                display.updateDisplay(DisplayMenuState::PLAY_TIME);
                gameSettings = menu_pool.read();
                break;
            default:
                hwlib::wait_ms(50);
                hwlib::cout << "ERROR: Default Case settings";
                break;
        }
        hwlib::wait_ms(100);
    }
}

void Settings::setCase(MenuState state){
    menu_pool.write(state);
}


void Settings::start(){
    main();
}

void Settings::setSettingsFlag(){
    settings_flag.set();
}