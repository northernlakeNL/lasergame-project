#ifndef NECRECIEVER_HPP
#define NECRECIEVER_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "i_necreceiver.hpp"
#include "messages.hpp"
#include <bitset>
#include <string>
#include "logger2.hpp"
extern Logger* pLogger;
class NecReciever :public rtos::task<> , public i_necreceiver{
private:
    Messages & messages;
    rtos::channel< unsigned int, 100 > signalChannel;
    rtos::channel< unsigned int, 100 > pauseChannel;
    unsigned int n = 0;
    uint8_t m = 0;
    int t_signalUs;
    int t_pauzeUs;
    enum States {
        IDLE_SIGNAL,
        IDLE_PAUSE,
        IDLE_BITPASS
    };
    uint8_t msg = 0;
    unsigned int nofBytes = 0;

    States currentState = IDLE_SIGNAL;
public:
    NecReciever(Messages & messages):
    task( "NEC" ),
    messages(messages),
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


    void extractMessage (uint8_t& msg, unsigned int& nofBytes, uint8_t m, unsigned int n){
        // revert bits:
        msg = 0; 
        uint8_t mloc = m;

        for (unsigned int i = 0; i <= n ; i++) {
            msg |= ((mloc >> i) & 1) << (7 - i);
        }
        nofBytes = n/8;
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
                        }
                        m = m << 1;
                        n++; 
                    }
                    else{
                        extractMessage(msg, nofBytes, m, n);
                        messages.messageRecieved(msg, nofBytes);
                        currentState = IDLE_SIGNAL;
                    }
                    break;
                default:
                    hwlib::cout<< "not going in right route" << hwlib::endl;
                    break;
            }
        }
    }
};
#endif 