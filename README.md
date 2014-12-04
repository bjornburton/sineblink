sineblink
=========

Inefficient blinker for Adafruit's Trinket.
In no way is this useful!

It's in C99 and so will compile using the gnu compiler, but also the
Arduino IDE.

It pulsates the red LED in a sine wave. Zero is no light, with min and max
at full light.
The negative portion of the cycle is the same so we can just rotate pi
radians and then go backward.
Minimal writes to the port is desired so just flip on, then off.
I'm using a sine function to determine the duration, which is massive.
This is duty-cycle control; at pi/2 the output is 100%, while at 0 and
pi it is 0%.
Being duty-cycle, follows power, rather than current (or voltage).

It could be rewriten to just move pi/2.
Also a trig lookup table could be used.  
