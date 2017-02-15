#include "ADC.h"

void initADC(void)
{
ADMUX = (1<<REFS0); //reference voltage set to AVCC - which is jumpered to VCC
ADCSRA |= (1<<ADEN) | (1<<ADPS1) | (1<<ADPS0); //enable ADC and set clock prescaler to 8 [1,000,000/8 = 125,000]
}

uint16_t readADC(void)
{

ADCSRA |= (1<<ADSC);

while (!(ADCSRA & (1<<ADIF))); //do nothing till conversion is complete (ADIF becomes 0)
ADCSRA |= (1<<ADIF); //clear ADIF by writing a 1

return (ADC);

}





