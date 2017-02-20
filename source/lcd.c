void pulseEn(void)
{
//enable pin is active low
PORTD &= ~(1<<pinEN); //activate enable pin, making output bits active at LCD
_delay_ms(1);
PORTD |= (1<<pinEN); //set enable pin high and wait for next falling edge trigger
_delay_ms(1);
PORTD = 0X00;
}


/*void goTo(void)
{
sndCmd();
}*/

void sndCmd(uint8_t c)
{
PORTD &= ~(1<<pinRS);
PORTD |= (c>>4) & 0x0F;
pulseEn();

PORTD &= ~(1<<pinRS);
PORTD |= c & 0x0F;
pulseEn(); 
}


void snd4Cmd(char c)
{
PORTD &= ~(1<<pinRS);
PORTD |= c;
pulseEn();
}

void sndDat(uint8_t c)
{
PORTD |= (1<<pinRS); //data, so set pinRS high
PORTD |= (c>>4) & 0x0F;
pulseEn();

PORTD |= (1<<pinRS);
PORTD |= c & 0x0F;
pulseEn();
}

void initLCD(void)
{
DDRD=0XFF; //all pins outputs
PORTD = 0X00; //clear port to start clean - erase any data that might be in the chip for sanity!!!
PORTD |= (1<<pinEN); //start with enable pin high

_delay_ms(100); //waiting for powerup

snd4Cmd(0b0011); //reset 1
_delay_ms(50);

snd4Cmd(0b0011); //reset 2
_delay_ms(10);

snd4Cmd(0b0011); //reset 3
_delay_ms(10);

snd4Cmd(0b0010); //decimal "2" - 4 bit mode

sndCmd(0x28);  //function set - DL=0 [4 bits], N=1 [2 lines], F=0 [5x7]
sndCmd(0x0F);  //set display - D=1 [display on], C=1 [cursor on], B=1 [cursor blinking]
sndCmd(0x01);  //clear LCD and reset character address
sndCmd(0x06);  //entry mode - I/D=1 [increment], S=0 [no shift]
}


void writeString(const char *c)
{
	while (*c)
	{
		sndDat(*c);
		*c++;
	}
}




