#define F_CPU 16000000 //16MHz clock, default

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void main(void)
{
int lresult;
int rresult;
int i;

initADC();
initServo();
//Uncomment the initLCD function below if you want LCD support
//initLCD();

_delay_ms(500); //just a startup delay

while(1)
{
	lresult = readADC(2); //read from ADC channel 2 for the left channel
	rresult = readADC(3); //read from ADC channel 3 for the right channel
	
	if (lresult >= 900) //no object on the left side
	{
		if (rresult >=900) //no object on the right side, keep moving forward
		{	
			for (i=250; i>0; i--)
			{
				OCR1A=436;
				OCR1B=436;
				_delay_ms(1);
			}
		}
		else				//object detected on right side so stop right wheel turn hard left
		{	
			for (i=250; i>0; i--)
			{
				OCR1A=436;
				OCR1B=386;
				_delay_ms(1);
			}
		}	
	}
	
	else 				//object on the left side
	{
		if (rresult >=900) //no object on the right side, stop left wheel turn hard right
		{	
			for (i=250; i>0; i--)
			{
				OCR1A=386;
				OCR1B=436;
				_delay_ms(1);
			}
		}
		else				//object on both sides; stop until a path clears
		{	
			for (i=250; i>0; i--)
			{
				OCR1A=386;
				OCR1B=386;
				_delay_ms(1);
			}
		}	
	}
	
	_delay_ms(500); //wait half a second before taking next reading 
	
} //end of while(1) loop

} //end of program
