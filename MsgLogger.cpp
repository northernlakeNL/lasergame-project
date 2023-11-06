#include "MsgLogger.hpp"

MsgLogger::MsgLogger():
    task("msg_logger"),
    messageChannel(this, "messageChannel"){}

void MsgLogger::messageReceived(uint64_t msg, unsigned int nofBytes) {
    messageChannel.write(msg);
}

void MsgLogger::main() {
    for (;;) {
        getMessage = messageChannel.read();
        pLogger->logInt(getMessage);
    }
}
