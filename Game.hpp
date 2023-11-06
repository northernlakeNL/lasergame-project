#include "rtos.hpp"
#include "Button.hpp"

class Game: public rtos::task<>{
    private:
        int play_time;
        rtos::clock time;
        int playerID;
        int lives_max;
        int bullets_max;
        int bullets;
        void main() override{for (;;){}}
    public:
    Game(int play_time, int playerID, int lives_max, int buttons_max):
        task(1, "Gameplay"),
        time(this, (play_time*rtos::ms), "time"),
        bullets(bullets_max){}
        // gamePlay(){}
    void gamePlay();
};