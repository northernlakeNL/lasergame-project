#include "SignalPauseDetector.hpp"

SignalPauseDetector::SignalPauseDetector(IR_receiver &receiver, i_necreceiver &necController, int prio):
    task(prio,"SignalPauseDetector"),
    receiver(receiver),
    necController(necController)
    {}
