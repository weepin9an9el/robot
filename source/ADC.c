#include <avr/io.h>
#include <stdio.h>

void initADC(void) //function to initialize the ADC registers
{
/*-------------------------------SETUP THE ADMUX REGISTER----------------------------------*/
//We want to use a reference voltage tied to AVCC -> which we will just jumper to VCC (5.0V)
//for now.  Could make this reference voltage smaller in order to get better resolution per step.
//To use AVCC, REFS0 needs to be set with REFS1 cleared.

ADMUX |= (1<<REFS0); 

/*--------------------------------END OF ADMUX SETUP---------------------------------------*/

/*-------------------------------SETUP THE ADCSRA REGISTER----------------------------------*/
//Need to set the clock prescaler.  The ADC clock needs a frequency between 50 kHZ and 200 kHz.  Since our CPU frequency is 
//16 Mhz, we need a scaler between 80 (16M/200k) and 320(16M/50k).  The only option we have is 128, which
//is set by setting all three prescaler bits.
ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);

//Now, we want to enable the ADC, so we need to set the ADEN bit in the register.
ADCSRA |= (1<<ADEN); 
/*------------------------------------END OF ADCSRA SETUP---------------------------------------*/
} //end initADC function


uint16_t readADC(int channel)
{
//first, I need to set the ADMUX register to read from the appropriate ADC channel.  
//I have only wired up channels 2 and 3, so our MUX bits will be 
//(MUX3..0 = 0010) -> channel 2	
//(MUX3..0 = 0011) -> channel 3	

ADMUX |= (1<<MUX1);  //this bit is set regardless of reading from channel 2 or 3

if (channel==3)
	ADMUX |= (1<<MUX0); //need to set this bit to read channel 3, in addition to MUX 1 (MUX3..0=0011)
else
	ADMUX &= ~(1<<MUX0); //clear MUX 0 to read from channel 2

ADCSRA |= (1<<ADSC); //start conversion

while (!(ADCSRA & (1<<ADIF))); //do nothing till conversion is complete (ADIF becomes 1)

//ADCSRA |= (1<<ADIF); //clear ADIF by writing a 1

return (ADC);  //result is a 10 bit value contained in register ADC

}





