#define F_CPU 16000000 //16MHz clock, default

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void main(void)
{
float lresult;
//float rresult;

initLCD();
initADC();
initServo();

while(1)
{
	lresult = readADC(1)*0.00488; //back calculate the left sensor voltage by using the ADC result formula [4.8mV per step]
//	rresult = readright()*0.00488; //back calculate the right sensor voltage by using the ADC result formula [4.8mV per step]

	if (lresult >= 920) //~4.5 volts -- no object detected so keep moving
		OCR1A = 436;
		else if (lresult >= 700) //~3.5 to 4.5 volts, object is close, so slow down
			OCR1A = 400;
		else	
			OCR1A = 386; //object detected - stop
	
	_delay_ms(500); //wait half a second before taking next reading 
	
}

} //end of program
