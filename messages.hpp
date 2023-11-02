#ifndef MESSAGES_HPP
#define MESSAGES_HPP

class Messages{

public:
    virtual void messageRecieved(uint64_t, unsigned int)  = 0;
    
};

#endif