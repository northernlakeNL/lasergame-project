#ifndef NECRECIEVER_HPP
#define NECRECIEVER_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "i_necreceiver.hpp"

class NecReciever :public rtos::task<> , public i_necreceiver{
private:
    rtos::channel< unsigned int, 100 > signalChannel;
    rtos::channel< unsigned int, 100 > pauseChannel;
    int n = 0;
    int m = 0;
    int t_signalUs;
    int t_pauzeUs;
    enum States {
        IDLE_SIGNAL,
        IDLE_PAUSE,
        IDLE_BITPASS
    };

    States currentState = IDLE_SIGNAL;
public:
    NecReciever():
    task( "NEC" ),
    signalChannel( this, "signalChannel" ),
    pauseChannel( this, "pauseChannel" )
    {}



    void pauseDetected(int t_us) override {
        pauseChannel.write(t_us);
    }

    void signalDetected(int t_us) override {
        if(t_us > 7000){
            signalChannel.clear();
            pauseChannel.clear();
        }
        signalChannel.write(t_us);
    }


    void extractMessage (uint64& msg, uint& nofBytes, uint64 m, uint n){
        // revert bits:
        msg = 0; mloc=m;
        for (int i=0; i<n; i++){
            msg<<(mloc&1);
            mloc=mloc>>1;
        }
        nofBytes = n/8
    }

    void main() override {
        for(;;){
            switch(currentState){
                case IDLE_SIGNAL:
                    t_signalUs = signalChannel.read();
                    if(t_signalUs > 7000 && t_signalUs < 11000){
                        currentState = IDLE_PAUSE;
                    }
                    break;
                case IDLE_PAUSE:
                    t_pauzeUs = pauseChannel.read();
                    if(t_signalUs > 3000 && t_pauzeUs < 6000){
                        n = 0;
                        m = 0;
                        currentState = IDLE_BITPASS;
                    }
                    else{
                        currentState = IDLE_SIGNAL;
                    }
                    break;
                case IDLE_BITPASS:
                    t_pauzeUs = pauseChannel.read();
                    if((t_pauzeUs > 200 )&& (t_pauzeUs < 2000)){
                        if(t_pauzeUs > 1100){
                            m |= 1;
                            n++;
                            currentState = IDLE_BITPASS;
                        }
                        else{
                            n++;
                            currentState = IDLE_BITPASS;
                        }   
                    }
                    else{
                        // extractMessage(msg, nofBytes, m, n)
                        // messageReciever.messageRecieved(msg, nofBytes)
                        currentState = IDLE_SIGNAL;
                    }
                    break;
            }
        }
    }
};
#endif 