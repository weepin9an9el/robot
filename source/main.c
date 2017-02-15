#define F_CPU 1000000 //1MHz clock, default

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

void main(void)
{
char lbuffer[16], rbuffer[16];
float lresult, rresult;

initLCD();
initADC();
initServo();

sndCmd(0x80); //go to first column, row 0
writeString("LtSens = ");
//sndCmd(0xA8); //go to first column, row 1
//writeString("RtSens = ");

while(1)
{
	lresult = readADC()*0.00488; //back calculate the left sensor voltage by using the ADC result formula [4.8mV per step]
//	rresult = readright()*0.00488; //back calculate the right sensor voltage by using the ADC result formula [4.8mV per step]

	sprintf(lbuffer, "%0.3f", lresult);
//	sprintf(rbuffer, "%0.3f", rresult);
	
	sndCmd(0x89); //go to position 10, row 1
	writeString(lbuffer);
	
	_delay_ms(500); //wait half a second for readability
	
}

} //end of program
