#include "rtos.hpp"
#include "Display.hpp"

class GameClock: public rtos::task<>{
    private:
        rtos::clock time;
        int countdown;
        void main() override{
            for (;;){

                }
            }
    public:
    GameClock(int countdown):
        task(5, "Timer"),
        countdown(countdown)
    {}

    int preGameTimer();
    int GameTimer(int gametime);


};