/**************************************
A most inefficient Trinket led blinker!
2014-12-30 - Bjorn Burton
Just for fun.
**************************************/

# define F_CPU 8000000UL    // AVR clock frequency in Hz, used by util/delay.h

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
# define Y_STEPS 100.0

/* y position */
# define X_LIMIT_RIGHT 100.0
# define X_LIMIT_LEFT 0.0
# define X_STEPS  (X_LIMIT_RIGHT - X_LIMIT_LEFT)
# define RIGHT 1
# define LEFT -1

/* Misc */
# define SCALE 100 // used instead of floating point numbers

/* Function Declatations */
void delay(unsigned intervals);
void ledcntl(char state);


/**************************************************************
The plan is to pulsate an LED in a sine wave. Zero is no light,
with min and max at full light. The negative is the same so
this only rotates pi radians and then goes back.
Minimal writes to the port is desired so just flip on, then off.
I'm using a sine function to determine the duration.
This is duty-cycle control; at pi/2 the output is 100%, while
at 0 an pi it is 0%. Being duty-cycle, follows power, rather
than current.  
***************************************************************/

int main()
 {
  unsigned x_position = X_LIMIT_LEFT;
  int x_direction = RIGHT;
  int amplitude;
  float angle;
   
  {  // set the direction to output for the LED
   DDRB |= (1<<LED_RED_DD);
  }

  for (;;) // forever; two loops per cycle
      {
       angle = (M_PI * x_position) / X_STEPS;
       amplitude = Y_STEPS * sin(angle);
       
       ledcntl(ON);
       delay(amplitude); // on for the duration
        
       ledcntl(OFF);
       delay(Y_STEPS - amplitude); // off for the remainder
        

       x_position += x_direction;
       
       if(x_position == X_LIMIT_RIGHT)
          x_direction = LEFT;
          
       if(x_position == X_LIMIT_LEFT)
          x_direction = RIGHT;
      }

}

/* run-time variable delay in 100 us intervals */
void delay(unsigned intervals)
{
 do  _delay_us(100);
     while(--intervals > 0);
}


/* simple led control */
void ledcntl(char state)
{
  PORTB =  state ? PORTB | (1<<LED_RED) : PORTB ^ (1<<LED_RED);
}

