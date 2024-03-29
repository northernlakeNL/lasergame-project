#ifndef SIGNALPAUSEDETECTOR_HPP
#define SIGNALPAUSEDETECTOR_HPP
#include "hwlib.hpp"
#include "rtos.hpp"
#include "IR_Receiver.hpp"
#include "I_necreceiver.hpp"
#include "logger2.hpp"
extern Logger* pLogger;
class SignalPauseDetector: public rtos::task<> {
private:
    
    IR_receiver & receiver;
    i_necreceiver & necController;
    int prio;
    unsigned int t_signalUs = 0;
    unsigned int t_pauzeUs = 0;
    enum State {
        WAIT_PAUSE,
        WAIT_SIGNAL
    };
    State currentState = WAIT_PAUSE;

    void main(){
        t_signalUs = 0;
        for(;;){
            switch(currentState){
                case WAIT_PAUSE:
                    hwlib::wait_us(100);
                    if(this->receiver.read() == 0){
                        t_signalUs += 100;
                        // hwlib::cout<<"STUCK"<< hwlib::endl;
                    }
                    else{
                    necController.signalDetected(t_signalUs);
                    t_pauzeUs = 0;
                    currentState = WAIT_SIGNAL;
                    }
                    break;
                    
                case WAIT_SIGNAL:
                hwlib::wait_us(100);
                if(this->receiver.read() != 0){
                    t_pauzeUs += 100;
                    // hwlib::cout<<t_pauzeUs<< hwlib::endl;
                    // pLogger->logText("t_pauzeUs");
                    // pLogger->logInt(int(t_pauzeUs));
                    if(t_pauzeUs > 6000){
                        necController.pauseDetected(t_pauzeUs);
                        // hwlib::cout<<"hoi"<< hwlib::endl;
                        t_pauzeUs = 0;
                    }
                }
                else{
                    necController.pauseDetected(t_pauzeUs);
                    t_signalUs = 0;
                    currentState = WAIT_PAUSE;
                }
                break;
            }
        }
    }
public:
    SignalPauseDetector(IR_receiver &receiver, i_necreceiver &necController, int prio);
};
#endif 