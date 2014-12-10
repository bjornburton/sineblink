/**************************************
A most inefficient Trinket led blinker!
2014-12-30 - Bjorn Burton
Just for fun.
**************************************/
// AVR clock frequency in Hz, used by util/delay.h
# define F_CPU 8000000UL

# include <avr/io.h> // need some port access
# include <util/delay.h> // need to delay
# include <stdlib.h>
# include <math.h>

/* LED port */
# define LED_RED PORTB1
# define LED_RED_DD DDB1
# define ON 1
# define OFF 0

/* amplitude */
# define Y_STEPS 100.0F

/* y position */
# define X_LIMIT_RIGHT 100.0F
# define X_LIMIT_LEFT 0.0F
# define X_STEPS  (X_LIMIT_RIGHT - X_LIMIT_LEFT)
# define RIGHT 1
# define LEFT -1

/* Function Declatations */
void delay(unsigned intervals);
void ledcntl(char state);


/**************************************************************
The plan is to pulsate an LED in a sine wave. Zero is no light,
with wave minimum and maximum at full light.
 
Intensity is controled through duty-cycle control. The wave is
sliced into intervals and each interval has a single-cycle; one
on and one off. It appears continous since the slices are
short. The negative portion of the wave make light too. In a
way it is "rectified". It's the same shape and illumination so
we can just rotate pi radians and then go back.

Minimal writes to the port is desired so just flip on, then off.
I'm using a sine function to determine the duration.
This is duty-cycle control; at pi/2 the output is 100%, while
at 0 and pi it is 0%. Being duty-cycle, follows power, rather
than current.  
***************************************************************/

int main()
 {
  unsigned x_position = X_LIMIT_LEFT; // starting on the left
  char x_direction = RIGHT; // moving toward the right
 
    // set the direction to output for the LED
  DDRB |= (1<<LED_RED_DD);
  

  for (;;) // forever - two loops per cycle
      {
       // figure how far into the wave we are
       float wave_portion = x_position/X_STEPS; 

       // sine amplitude is used for illumination duration 
       char amplitude = Y_STEPS * sin(M_PI*wave_portion); 
       
       ledcntl(ON); // flip the led on
       delay(amplitude); // on for the duration of wave amplitude
        
       ledcntl(OFF); // now flip it off
       delay(Y_STEPS - amplitude); // off for the remainder
        
       { // managment of location on wave
        x_position += x_direction;
        if(x_position == X_LIMIT_RIGHT) x_direction = LEFT;
        if(x_position == X_LIMIT_LEFT)  x_direction = RIGHT;
       }

      }

return 0; // it's the right thing to do!
}

/* run-time variable delay in 100 us intervals */
void delay(unsigned intervals)
{
  while(intervals-- > 0)
        _delay_us(100); // _delay_us takes a constant only
}


/* simple led control */
void ledcntl(char state)
{
  PORTB =  state ? PORTB | (1<<LED_RED) : PORTB ^ (1<<LED_RED);
}


