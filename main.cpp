#include "hwlib.hpp"
#include "Settings.hpp"
#include "Button.hpp"
#include "Game.hpp"
#include "GameClock.hpp"

int main(){
   Settings settings;
   Button button;

   std::array<int, 4> setting = settings.gameSettings(); //{player count, play time, lives, bullets(reload is infinite)}
   int play_time = setting[1];
   play_time*=60000;
   int lives_max = setting[2];
   int bullets_max = setting[3];
   int start_time = 20000;

   GameClock gameClock(start_time);
   Game game(play_time, 1, lives_max, bullets_max);
   game.gamePlay();

   return 0;
}
