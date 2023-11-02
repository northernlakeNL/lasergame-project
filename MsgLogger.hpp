#ifndef MSGLOGGER_HPP
#define MSGLOGGER_HPP
#include "rtos.hpp"
#include "hwlib.hpp"
#include "logger2.hpp"
#include "messages.hpp"

extern Logger* pLogger;

class MsgLogger : public rtos::task<>, public Messages{
private:
rtos::channel< unsigned int, 100 > messageChannel;
uint64_t getMessage = 0;

public:
    MsgLogger():
    task("msg_logger"),
    messageChannel(this, "messageChannel")
    {}

    void messageRecieved(uint64_t msg, unsigned int nofBytes) override{
        messageChannel.write(msg);
    }

    
    void main() override{
        for(;;){
        getMessage = messageChannel.read();
        // pLogger->logInt(getMessage);


        }
    }

};

#endif