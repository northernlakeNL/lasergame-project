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

class NecReciever : public rtos::task<>, public i_necreceiver {
private:
    Messages& messages;
    rtos::channel<unsigned int, 100> signalChannel;
    rtos::channel<unsigned int, 100> pauseChannel;
    unsigned int n = 0;
    uint32_t m = 0;
    int t_signalUs;
    int t_pauzeUs;
    enum States {
        IDLE_SIGNAL,
        IDLE_PAUSE,
        IDLE_BITPASS
    };
    uint32_t msg = 0;
    unsigned int nofBytes = 0;


    States currentState = IDLE_SIGNAL;

public:
    NecReciever(Messages& messages);
    void pauseDetected(int t_us) override;
    void signalDetected(int t_us) override;
    void extractMessage(uint32_t& msg, unsigned int& nofBytes, uint32_t m, unsigned int n);
    void main() override;
    
};

#endif 