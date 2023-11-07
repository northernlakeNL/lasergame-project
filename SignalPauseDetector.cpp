#include "SignalPauseDetector.hpp"

SignalPauseDetector::SignalPauseDetector(IR_receiver &receiver, i_necreceiver &necController):
    task("SignalPauseDetector"),
    receiver(receiver),
    necController(necController)
    {}
