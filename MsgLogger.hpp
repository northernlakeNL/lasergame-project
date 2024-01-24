#ifndef MSGLOGGER_HPP
#define MSGLOGGER_HPP

#include "rtos.hpp"
#include "hwlib.hpp"
#include "logger2.hpp"
#include "messages.hpp"
#include <array>


extern Logger* pLogger;

class MsgLogger : public rtos::task<>, public Messages {
private:
    int prio;
    rtos::channel< unsigned int, 100 > messageChannel;
    rtos::channel< uint32_t, 100> receiveChannel;
    uint32_t getMessage = 0;
    std::array<int, 6> gameInfo;
    bool hit = 0;

public:
    MsgLogger(int prio);

    void messageReceived(uint32_t msg, unsigned int nofBytes) override;

    bool isHit() override;

    void resetHit() override;

    uint32_t messageRead() override;

    void main() override;
};

#endif
