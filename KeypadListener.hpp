#ifndef KEYPADLISTENER_HPP
#define KEYPADLISTENER_HPP

class KeypadListener{
    public:
    KeypadListener(){}
    virtual void writeChannel(char last_key) = 0;
};

#endif // KEYPADLISTENER_HPP