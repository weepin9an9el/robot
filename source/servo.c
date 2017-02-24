/*************************************************************************************************************************************
		MODIFIED SERVOS -- NEED TO FIND CENTER AND DETERMINE DIRECTION OF ROTATION
		I DID THIS THROUGH TRIAL AND ERROR, PLAYING WITH THE OCR1x NUMBERS, SPLITTING
		THE DELTA IN HALF BETWEEN THEORETICAL CENTER (1.5 mS) WHICH AT OUR COUNT AND 
		FREQUENCY IS 375 AND THER PREVIOUS NUMBER UNTIL IT STOPPED ROTATING.  SUBTRACTING
		ONE FROM THIS NUMBER CAUSED THE ROBOT TO GO BACKWARDS AS SLOW AS POSSIBLE
		AND ADDING ONE TO THIS NUMBER CAUSED THE ROBOT TO GO FORWARDS AS SLOW AS 
		POSSIBLE, WHICH IS ULTIMATELY WHAT WE WANT.

Facing the front of the robot, center positions of the modified servos are:
left servo: 386  
right servo: 385

Number below this center value, the robot will go backwards
Number above this center value, the robot will go forwards
***************************************************************************************************************************************/

void initServo(void)
{
//WGM13:0 = 1110 = 14 => Operate in mode 14 
//Mode 14 is fast PWM with the TOP value = ICR1

//COM1A and COM1B = 10 => non-inverting mode
//clear OC1A/B on match and set on bottom

//CS12:0 = 011 => sets a prescaler of 64

//Per the datasheet => frequency = fclk/[N(1+TOP)]
//f=16000000/[64(1+4999)]
//f=16000000/[(64)(5000)]
//f=16000000/320000
//f=50

TCCR1A |= (1<<COM1A1) | (1<<COM1B1) | (1<<WGM11);
TCCR1B |= (1<<WGM13) | (1<<WGM12) | (1<<CS11) | (1<<CS10);

ICR1=4999;   //TOP value

DDRB |= (1<<PB1) | (1<<PB2); //portB, pins 1 and 2 are outputs for servo PWM

}


