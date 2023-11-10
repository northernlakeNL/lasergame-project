#include "MsgLogger.hpp"

MsgLogger::MsgLogger(int prio):
    task(prio,"msg_logger"),
    messageChannel(this, "messageChannel"),
    receiveChannel(this, "receiveChannel")
    {}

void MsgLogger::messageReceived(uint32_t msg, unsigned int nofBytes) {
    messageChannel.write(msg);
    // if
    hit = 1;
}

void MsgLogger::main() {
    for (;;) {
        hwlib::wait_ms(50);
        getMessage = messageChannel.read();
        receiveChannel.write(getMessage);
        pLogger->logInt(getMessage);
        // bitSplitter(getMessage);
        
    }
}

uint32_t MsgLogger::messageRead(){
    return getMessage;
}

bool MsgLogger::isHit(){
    // pLogger->logText("is it hit?");
    // pLogger->logInt(hit);

    return hit;
}

void MsgLogger::resetHit(){
    hit = 0;
}

