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
# define Y_STEPS 100

/* y position */
# define X_LIMIT_RIGHT 100
# define X_LIMIT_LEFT 0
# define X_STEPS  (X_LIMIT_RIGHT - X_LIMIT_LEFT)
# define RIGHT 1
# define LEFT -1


/**************************************************************
The plan is to pulsate an LED in a sine wave.
Minimal writes to the port is desired so just flip on, then off.
Using a sine function to determine the duration.
***************************************************************/

int main()
 {
  int x_position = X_LIMIT_LEFT;
  int x_direction = RIGHT;
  int amplitude;
  float angle;
   
  {  // set the port y_directions
   DDRB |= (1<<LED_RED_DD);
  }

  for (;;) // forever
      {
       angle = (M_PI * x_position) / X_STEPS;
       amplitude = Y_STEPS * sin(angle);
       
       ledcntl(ON);
       delay(amplitude);
        
       ledcntl(OFF);
       delay(Y_STEPS - amplitude);
        

       x_position += x_direction;
       
       if(x_position == X_LIMIT_RIGHT)
          x_direction = LEFT;
          
       if(x_position == X_LIMIT_LEFT)
          x_direction = RIGHT;
      }

}

/* run-time variable delay in 100 us intervals */
void delay(int intervals)
{
 for(int count=intervals;count>0;count--)
     _delay_us(100); // takes a constant
}

/ * simple led control */
void ledcntl(int state)
{
  PORTB =  state ? PORTB | (1<<LED_RED) : PORTB ^ (1<<LED_RED);
}

