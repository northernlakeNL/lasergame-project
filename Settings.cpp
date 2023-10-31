#include "Settings.hpp"


std::array<int, 4> Settings::gameSettings(){
    Display display;
    int state = 0;
    std::array<int, 4> settings = display.configure(state);
    return settings;
}
