#
MCU:=atmega328
PROGRAMMER:=linuxspi
COMS:=/dev/spidev0.0

CC:=avr-gcc
OC:=avr-objcopy
DUDE:=avrdude

#Add support for floating points 
#Also need the math library (-lm)
PRINTF_LIB_FLOAT:= -Wl,-u,vfprintf -lm -lprintf_flt

#PRINTF_LIB_FLOAT:= 

CC_FLAGS += -c -Os
OC_FLAGS += -O ihex
LD_FLAGS += $(PRINTF_LIB_FLOAT)

#use wildcard expression to include all .c files as part of SRC variable
#SRCS := $(wildcard *.c)
#OBJS := $(SRCS:.c=.o)

.PHONY: all clean

all: main.hex

main.hex: main.elf
	$(OC) -j .text -j .data $(OC_FLAGS) $< $@

#Use the below main.elf if you don't want lcd support
main.elf: main.o ADC.o servo.o
	$(CC) -mmcu=$(MCU) $(LD_FLAGS) -o $@ main.o ADC.o servo.o

#Use the below main.elf if want lcd support
#Also, will need to uncomment the lcd.o recipe below	
#main.elf: main.o ADC.o lcd.o servo.o
#	$(CC) -mmcu=$(MCU) $(LD_FLAGS) -o $@ main.o ADC.o lcd.o servo.o

main.o: main.c
	$(CC) $(CC_FLAGS) -mmcu=$(MCU) -o $@ $<

servo.o: servo.c
	$(CC) $(CC_FLAGS) -mmcu=$(MCU) -o $@ $<

ADC.o: ADC.c
	$(CC) $(CC_FLAGS) -mmcu=$(MCU) -o $@ $<

#lcd.o: lcd.c
#	$(CC) $(CC_FLAGS) -mmcu=$(MCU) -o $@ $<

#all: lcd.hex
#lcd.o: lcd.c
#	$(CC) $(CC_FLAGS) -mmcu=$(MCU) -o $@ lcd.c
#lcd.elf: lcd.o
#	$(CC) -mmcu=$(MCU) $(LD_FLAGS) -o $@ $< 
#lcd.hex: lcd.elf
#	$(OC) -j .text -j .data $(OC_FLAGS) $< $@
prog: main.hex
	$(DUDE) -p $(MCU) -P $(COMS) -c $(PROGRAMMER) -e -U flash:w:$<
clean:
	rm *.o *.elf *.hex
