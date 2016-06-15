TOOLCHAIN=avr-
#indicate toolchain
CC=$(TOOLCHAIN)gcc
#indicate objcopy
OBJC=$(TOOLCHAIN)objcopy
AVRDUDE=avrdude
#reference to toolchain (define c-compiler)
BOARD=atmega328p
F_CPU=16000000UL
DEV=$(wildcard /dev/tty.usbserial-*) 


# Optimization level, can be [0, 1, 2, 3, s]. 
#     0 = turn off optimization. s = optimize for size.
#     (Note: 3 is not always the best optimization level. See avr-libc FAQ.)
OPT = s

CFLAGS=-mmcu=$(BOARD) -DF_CPU=$(F_CPU)
CFLAGS += -std=gnu99
CFLAGS += -Wall
CFLAGS += -O$(OPT)
#CFLAGS += -Ii2cmaster

PROJECT=Pro4_T2_Sensorboard
OBJECTS= SPI.o Tranceiver.o main.o CRC.o uart.o


#General rule to compile c-files to object-files
%.o: %.c
	$(CC) $(CFLAGS) $^ -c -o $@

%.o: %.S
	$(CC) $(CFLAGS) $^ -c -o $@

#Rule to link o-files
$(PROJECT).elf: $(OBJECTS)
	echo $(DEV)
	$(CC) $(CFLAGS) $^ -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,--gc-sections -o $@

%.hex: %.elf
	$(OBJC) -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures $^ $@

.PHONY: flash
flash: $(PROJECT).hex
	$(AVRDUDE) -v -v -v -v -p$(BOARD) -carduino -P$(DEV) -b57600  -Uflash:w:$^:i


.PHONY: clean
clean:
	rm -f *.o *.elf *.hex

