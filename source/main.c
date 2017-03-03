#define F_CPU 16000000 //16MHz clock, default

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

volatile uint8_t tot_overflows;

void initTimerzero(void)
{
		
	//Need to set the prescaler using the clock select bits in TCCR0B register.. we will use a prescaler of 1024 since our clock speed is so high
	TCCR0B |= (1<<CS02) | (1<<CS00); //set the prescaler to 1024
	
	TIMSK0 |= (1<<TOIE0); //Set the Timer/counter interrupt mask bit such that we enable the overflow interrupt
	
	//We need to set OCRnx to to the value we want to count to (TOP) based on the below formula
	//OCRnx = [(clock_speed / prescaler_value) * Desired_time_in_seconds] - 1
	//OCRnx = [(16000000 / 1024) * 1] - 1 = 15,624
	//However, this number needs to be less than 255 since this timer is only 8 bits
	//15,624/255 = 61 --->  Need to count the overflow 61 times, then count the remainder to hit 1 second
	//15,624-(61*255) = 69
	//So, count 61 full overflows then count to 69 on the next overflow, all at a prescaler of 1024 to hit 1 second.
	
	//Finally, initialize tot_overflows to zero 
	
	tot_overflows = 0;
	
}

void main(void)
{
cli(); //disable interrupts while we get everything set up

int lresult;
int rresult;
int i;

initADC();
initServo();
initTimerzero();
//Uncomment the initLCD function below if you want LCD support
//initLCD();

sei(); //enable global interrupts now that everything is intialized

while(1)
{
	if (tot_overflows <62)
	{
		OCR1A=386;
		OCR1B=386;
	}
	else{
	lresult = readADC(2); //read from ADC channel 2 for the left channel
	rresult = readADC(3); //read from ADC channel 3 for the right channel
	
	if (lresult >= 950) //no object on the left side
	{
		if (rresult >= 950) //no object on the right side, keep moving forward
		{	
			
				OCR1A=436;
				OCR1B=436;
				_delay_ms(1000);
			
		}
		else				//object detected on right side so stop right wheel turn hard left
		{	
			
				OCR1A=436;
				OCR1B=386;
				_delay_ms(1000);
			
		}	
	}
	
	else 				//object on the left side
	{
		if (rresult >=950) //no object on the right side, stop left wheel turn hard right
		{	
			
				OCR1A=386;
				OCR1B=436;
				_delay_ms(1000);
			
		}
		else				//object on both sides; stop until a path clears
		{	
			
				OCR1A=386;
				OCR1B=386;
				_delay_ms(1000);
			
		}	
	}
		tot_overflows = 0;
	}// end of "tot_overflows <62" else statement	
 
	
} //end of while(1) loop

} //end of program

ISR(TIMER0_OVF_vect) //timer0 overflow interrupt
{
	//keep track of overflows
	tot_overflows++;
	
}
