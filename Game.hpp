class game : public rtos::task<>{
    enum state_game{PreGame, Playing, Hit, EndGame}
    private:
        state_game     state = PreGame;
        
        rtos::channel    result;
        Life            Life;
        rtos::timer        gameTimer;
        rtos::timer        countdownTimer;
        HitList            HitList;
        
        spel(Life& Life):
        Life(Life)
        {}
    void game_main(){
        for(;;){
            switch(state){
                case PreGame:
                    countdownTimer.start(countdownTime);
                    state = Playing;
                case Playing:
                    gameTimer.start(gameTime);
                    state = Hit;
                case Hit:
                    Life -=1;
                    HitList.append(HitID);
                    if Life != 0:
                        case Playing;
                    if Life = 0:
                        dead();
                case EndGame:
                    case = PreGame;
            }
        }
    };
};
