#! /bin/bash

######################################################
# A simple wrapper to replace hard-coded avrdude
# command-line parameters, from Arduino's IDE, with
# parameters which better suit the host and target. 
# This allows boards which emulate programmers,
# like Trinket and Gemma, to be easily supported.
# It also allows the use of a pre-existing install
# of Avrdude, perhaps of a newer release, to be used
# with it's compatible avrdude.conf file. 
#
# It must sit in place of the avrdude located in
# /usr/share/arduino/hardware/tools/
# Since it must share that directory, the original
# avrdude should be renamed. The AVRDUDE string may
# be pointed to the original, if desired.
#
#
######################################################

# Which target board or device
# (Note: This must be an entry in avrdude.conf)
BOARD="trinket"

# Which programmer to use
# (hint: usbtiny is emulated in Trinket and Gemma)
PROGRAMMER="usbtiny"

# Location of real avrdude (Hint: use no path for default avrdude)
AVRDUDE="avrdude"

# Matching avrdude.conf file.
CONF="/etc/avrdude.conf"

# We assemble all of the parameters
PROGSWFLAGS=" -c $PROGRAMMER -p $BOARD -C $CONF"

# Execute, starting with Arduino's parameters, followed by replacements
$AVRDUDE $* $PROGSWFLAGS

