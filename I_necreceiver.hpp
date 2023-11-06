#ifndef I_NECRECEIVER_HPP
#define I_NECRECEIVER_HPP


class i_necreceiver{

public:
    virtual void pauseDetected(int)  = 0;
    virtual void signalDetected(int)  = 0;
};

#endif
