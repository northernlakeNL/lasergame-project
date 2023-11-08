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
SOURCES := Keypad.cpp Display.cpp Button.cpp GameControl.cpp

# header files in this project
HEADERS := Keypad.hpp Display.hpp Button.hpp Game.hpp GameControl.hpp KeypadListener.hpp

# other places to look for files for this project
SEARCH  := 

# set RELATIVE to the next higher directory and defer to the Makefile.due
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
