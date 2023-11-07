#ifndef MSGLOGGER_HPP
#define MSGLOGGER_HPP

#include "rtos.hpp"
#include "hwlib.hpp"
#include "logger2.hpp"
#include "messages.hpp"

extern Logger* pLogger;

class MsgLogger : public rtos::task<>, public Messages {
private:
    rtos::channel< unsigned int, 100 > messageChannel;
    uint32_t getMessage = 0;

public:
    MsgLogger();

    void messageReceived(uint32_t msg, unsigned int nofBytes) override;

    void main() override;
};

#endif
