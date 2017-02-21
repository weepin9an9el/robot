#define pinRS PD6
#define pinEN PD7

void initLCD(void);
void pulseEn(void);

//void goTo(int x, int y);

//void clr(void);

//void goHome(void);

void snd4Cmd(char c);
void SndCmd(uint8_t c);
void sndDat(uint8_t c);
void writeString(const char *c);
void goTo(void);
