#define F_CPU 16000000 //16MHz clock, default

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void main(void)
{
int lresult;
int rresult;

initADC();
initServo();
//Uncomment the initLCD function below if you want LCD support
//initLCD();
while(1)
{
	lresult = readADC(2); //read from ADC channel 2 for the left channel
	rresult = readADC(3); //read from ADC channel 3 for the right channel

	if (lresult >= 900) //no object on the left side
	{
		if (rresult >=900) //no object on the right side, keep moving forward
		{	
			OCR1A=436;
			OCR1B=436;
		}
		else				//object detected on right side so stop right wheel turn hard left
		{	
			OCR1A=436;
			OCR1B=386;
		}	
	}
	
	else 				//object on the left side
	{
		if (rresult >=900) //no object on the right side, stop left wheel turn hard right
		{	
			OCR1A=386;
			OCR1B=436;
		}
		else				//object on both sides; stop until a path clears
		{	
			OCR1A=386;
			OCR1B=386;
		}	
	}
	
		
	_delay_ms(500); //wait half a second before taking next reading 
	
} //end of while(1) loop

} //end of program
