#include "rtos.hpp"
#include "Display.hpp"

class GameClock: public rtos::task<>{
    private:
        rtos::clock time;
        int start_time;
        void main() override{for (;;){}}
    public:
    GameClock(int start_time):
        task(5, "Timer"),
        time(this, (start_time*rtos::ms), "game time")
    {}
    int GameTimer();
};