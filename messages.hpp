#ifndef MESSAGES_HPP
#define MESSAGES_HPP

class Messages{

public:
    virtual void messageReceived(uint32_t, unsigned int)  = 0;

    virtual uint32_t messageRead() = 0;

    virtual bool isHit() = 0;

    virtual void resetHit() = 0;
    
};

#endif