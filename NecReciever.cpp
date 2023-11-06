#include "NecReciever.hpp"

NecReciever::NecReciever(Messages& messages)
    : task("NEC"), messages(messages), signalChannel(this, "signalChannel"), pauseChannel(this, "pauseChannel") {}

void NecReciever::pauseDetected(int t_us) {
    pauseChannel.write(t_us);
}

void NecReciever::signalDetected(int t_us) {
    if (t_us > 7000) {
        signalChannel.clear();
        pauseChannel.clear();
    }
    signalChannel.write(t_us);
}

void NecReciever::extractMessage(uint8_t& msg, unsigned int& nofBytes, uint8_t m, unsigned int n) {
    // Revert bits:
    msg = 0;
    uint8_t mloc = m;

    for (unsigned int i = 0; i < n; i++) {
        msg |= ((mloc >> i) & 1) << (7 - i);
    }
    nofBytes = n / 8;
}

void NecReciever::main() {
    for (;;) {
        switch (currentState) {
            case IDLE_SIGNAL:
                t_signalUs = signalChannel.read();
                if (t_signalUs > 7000 && t_signalUs < 11000) {
                    currentState = IDLE_PAUSE;
                }
                break;
            case IDLE_PAUSE:
                t_pauzeUs = pauseChannel.read();
                if (t_signalUs > 3000 && t_pauzeUs < 6000) {
                    n = 0;
                    m = 0;
                    currentState = IDLE_BITPASS;
                } else {
                    currentState = IDLE_SIGNAL;
                }
                break;
            case IDLE_BITPASS:
                t_pauzeUs = pauseChannel.read();
                if ((t_pauzeUs > 200) && (t_pauzeUs < 2000)) {
                    m = m << 1;
                    if (t_pauzeUs > 1100) {
                        m |= 1;
                    }
                    n++;
                } else {
                    pLogger->logInt(n);
                    pLogger->logInt(m);
                    extractMessage(msg, nofBytes, m, n);
                    messages.messageReceived(msg, nofBytes);
                    currentState = IDLE_SIGNAL;
                }
                break;
            default:
                hwlib::cout << "not going in the right route" << hwlib::endl;
                break;
        }
    }
}
