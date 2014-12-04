sineblink
=========

Inefficient blinker for Adafruit Trinket

Pulsates the red LED in a sine wave. Zero is no light, with min and max at full light.
The negative portion of the cycle is the same so we can just rotate pi radians and then go backward.
Minimal writes to the port is desired so just flip on, then off.
I'm using a sine function to determine the duration, which is massive.
This is duty-cycle control; at pi/2 the output is 100%, while at 0 and pi it is 0%.
Being duty-cycle, follows power, rather than current (or voltage).  
