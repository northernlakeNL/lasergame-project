#include "SignalPauseDetector.hpp"

SignalPauseDetector::SignalPauseDetector(IR_receiver &receiver, i_necreceiver &necController):
    task(2,"SignalPauseDetector"),
    receiver(receiver),
    necController(necController)
    {}
