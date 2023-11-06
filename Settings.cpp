#include "Settings.hpp"

void Settings::main(){
    hwlib::cout<<"settings main\n";
    gameSettings = MenuState::IDLE;
    for(;;){
        switch (gameSettings){
            case MenuState::IDLE:
                hwlib::wait_ms(50);
                hwlib::cout << "settings\n";
                wait(settings_flag);
                settings_flag.print(hwlib::cout,true);
                display.setDisplayState(DisplayState::IDLE);
                display.setMenuFlag(MenuState::IDLE);
                settings_flag.clear();
                break;
            case MenuState::MENU:
                hwlib::wait_ms(50);
                hwlib::cout << "MenuState menu\n";
                settings_flag.print(hwlib::cout, true);
                wait(settings_flag);
                hwlib::cout << "passed flag\n";
                display.setDisplayState(DisplayState::SETTINGS);
                display.setMenuFlag(MenuState::MENU);
                hwlib::cout << "Menu flag done\n";
                settings_flag.clear();
                break;
            case MenuState::PLAYER_COUNT:
                hwlib::wait_ms(50);
                wait(settings_flag);
                display.setDisplayState(DisplayState::SETTINGS);
                display.setMenuFlag(MenuState::PLAYER_COUNT);
                break;
            case MenuState::LIVES:
                hwlib::wait_ms(50);
                wait(settings_flag);
                display.setDisplayState(DisplayState::SETTINGS);
                display.setMenuFlag(MenuState::LIVES);
                break;
            case MenuState::BULLETS:
                hwlib::wait_ms(50);
                wait(settings_flag);
                display.setDisplayState(DisplayState::SETTINGS);
                display.setMenuFlag(MenuState::BULLETS);
                break;
            case MenuState::PLAY_TIME:
                hwlib::wait_ms(50);
                wait(settings_flag);
                display.setDisplayState(DisplayState::SETTINGS);
                display.setMenuFlag(MenuState::PLAY_TIME);
            default:
                hwlib::wait_ms(50);
                hwlib::cout << "ERROR: Default Case settings";
                break;
        }
        hwlib::cout << "settings wait\n";
        hwlib::wait_ms(100);
    }
}

void Settings::setCase(MenuState state){
    gameSettings = state;
}


void Settings::start(){
    main();
}

void Settings::setSettingsFlag(){
    settings_flag.set();
}