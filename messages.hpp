#ifndef MESSAGES_HPP
#define MESSAGES_HPP

class Messages{

public:
    virtual void messageReceived(uint32_t, unsigned int)  = 0;
    
};

#endif