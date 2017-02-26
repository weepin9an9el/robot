#define F_CPU 16000000 //16MHz clock, default

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void main(void)
{
float lresult;
//float rresult;


initADC();
initServo();
//Uncomment the initLCD function below if you want LCD support
//initLCD();
while(1)
{
	lresult = readADC(2); //read from ADC channel 2 for the left channel
//	rresult = readADC(3); //read from ADC channel 3 for the right channel

	if (lresult >= 920) //~4.5 volts -- no object detected so keep moving
		OCR1A = 436;
		else if (lresult >= 700) //~3.5 to 4.5 volts, object is close, so slow down
			OCR1A = 400;
		else	
			OCR1A = 386; //object detected - stop
	
	_delay_ms(500); //wait half a second before taking next reading 
	
}

} //end of program
