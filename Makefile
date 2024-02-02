#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source files in this project (main.cpp is automatically assumed)

SOURCES := Button.cpp Beeper.cpp GameControl.cpp SignalPauseDetector.cpp IR_Receiver.cpp NecReciever.cpp MsgLogger.cpp IR_Emitter.cpp Display.cpp 

# header files in this project
HEADERS := Button.hpp Beeper.hpp GameControl.hpp ButtonListener.hpp logger2.hpp SignalPauseDetector.hpp IR_Receiver.hpp I_necreceiver.hpp NecReciever.hpp messages.hpp MsgLogger.hpp IR_Control.hpp IR_Emitter.hpp Keypad.hpp Display.hpp KeypadListener.hpp


# other places to look for files for this project
SEARCH  := 


RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
